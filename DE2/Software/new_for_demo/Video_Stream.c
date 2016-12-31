#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <system.h>
#include "sys/alt_dma.h"
#include "alt_types.h"
#include <sys/alt_irq.h>
#include <io.h>
#include "communication.h"
#include "altera_up_avalon_character_lcd.h"

//connect keypad as 4,6,7,2,5,1,3 of keypad to 7,6,5,4,3,2,1 of DE2

volatile int rx_done = 0;

/*
* Callback function that obtains notification that the data
* is received in the DMA transfer.
*/
void done (void* handle, int * data)
{
	rx_done++;
}

//connect keypad as 4,6,7,2,5,1,3 of keypad to 7,6,5,4,3,2,1 of DE2

//Function for clearing current message on LCD and writing message
//put in as input
void lcd_write( char* string );

//Initialize the LCD screen
void lcd_init( void );

//Function to call to skip over main program and just send pictures
//for creating new user profile
void super_mode(void);

//Function to read the current button being pressed, returns -1 if nothing pressed
char readKeypad(void);

//Function to wait until no keys pressed on keypad
void keyRelease(void);

//Reads a 4 digit code from the keypad and returns it as a string (char *)
char * readKeypadCode(void);

//Turns the servo to the locked position
void servoLock(void);

//turns the servo to the unlocked position
void servoUnlock(void);

//Used to control LCD screen.
alt_up_character_lcd_dev * char_lcd_dev;

int main()
{

	lcd_init();

	init_comm();
	servoUnlock();
	servoLock();
	char * pin_num = malloc(4*sizeof(char));
	int response; //The response from the Pi
	int i; //Iterator for various loops
	int wrong_count = 0; //The number of incorrect attempts in a row

	//If system starts with switch 0 up, just send pictures
	if(IORD_ALTERA_AVALON_PIO_DATA(MODE_SWITCH_BASE) & 1){
		printf("Booted in super mode\n");
		lcd_write("Super Mode");
		while(IORD_ALTERA_AVALON_PIO_DATA(MODE_SWITCH_BASE) & 1){
			super_mode();
		}
	}

	printf("Returned to normal program\n");
	while(1){
		//Initally turn off all LEDs
		IOWR_ALTERA_AVALON_PIO_DATA(GREEN_LED_BASE, 0);
		IOWR_ALTERA_AVALON_PIO_DATA(RED_LED_BASE, 0);
		printf("Waiting for user id\n");
		lcd_write("Enter Code");
		pin_num = readKeypadCode();
		send_code(pin_num);

		printf("Waiting for response from Pi\n");

		//If code is accepted
		if (receive_response()){

				//Turn on 2 green LEDs
				IOWR_ALTERA_AVALON_PIO_DATA(GREEN_LED_BASE, 3);

				//Wait for button 3 to be pressed
				printf("Waiting For Button Press\n");
				lcd_write("Take Picture");
				while((IORD_ALTERA_AVALON_PIO_DATA(BUTTON_3_BASE) & 1) == 1);

				//Turn on 1 more Green LED
				IOWR_ALTERA_AVALON_PIO_DATA(GREEN_LED_BASE, 7);

				//START OF DMA CODE (MEMORY TO MEMORY)
				int rc;
				alt_dma_txchan txchan;
				alt_dma_rxchan rxchan;

				char * buffer = malloc(153600);

				assert(buffer);

				//Initialize source and destination
				void* tx_data = (void*) FRAME_SAVE_DMA_READ_MASTER_PIXEL_BUFFER_BASE; // pointer to data to send
				void* rx_buffer = (void*) buffer; // pointer to rx buffer

				// Create transmit channel
				if ((txchan = alt_dma_txchan_open(FRAME_SAVE_DMA_NAME)) == NULL)
				{
				  printf ("Failed to open transmit channel\n");
				  exit (1);
				}
				// create receive channel
				if ((rxchan = alt_dma_rxchan_open(FRAME_SAVE_DMA_NAME)) == NULL)
				{
				  printf ("Failed to open receive channel\n");
				  exit (1);
				}

				//Specify the size
				alt_dma_rxchan_ioctl(rxchan, ALT_DMA_SET_MODE_8, NULL);
				alt_dma_txchan_ioctl(txchan, ALT_DMA_SET_MODE_8, NULL);


				//Create receive Request
				if ((rc = alt_dma_rxchan_prepare (rxchan,
					  rx_buffer,
					  153600,
					  done,
					  NULL)) < 0)
				{
				  printf ("Failed to request read: %i\n", rc);
				  exit (1);
				}

				// Create send request
				if ((rc = alt_dma_txchan_send (txchan,
					  tx_data,
					  153600,
					  NULL,
					  NULL)) < 0)
				{
				  printf ("Failed to request send: %i\n", rc);
				  exit (1);
				}


				printf("Transfering...\n");
				// wait for transfer to complete
				while (!rx_done);

				//Close the send and recieve channels
				alt_dma_rxchan_close(rxchan);
				alt_dma_txchan_close(txchan);

				printf ("Transfer successful!\n");

				//END OF DMA CODE

				//Send buffer data to the Raspberry Pi
				send_buffer( buffer );
				free(buffer);

				//Turn on one more green LED
				lcd_write("Waiting...");
				IOWR_ALTERA_AVALON_PIO_DATA(GREEN_LED_BASE, 15);

				//Wait for button 3 to be released (if still pressed)
				while ((IORD_ALTERA_AVALON_PIO_DATA(BUTTON_3_BASE) & 1) == 0);

				if(receive_response()){
					wrong_count = 0;
					lcd_write("Welcome Home");
					servoUnlock();
					for (i = 0; i < 10; i++){
						IOWR_ALTERA_AVALON_PIO_DATA(GREEN_LED_BASE, 0xff);
						usleep(500000);
						IOWR_ALTERA_AVALON_PIO_DATA(GREEN_LED_BASE, 0);
						usleep(500000);
					}
					lcd_write("Locking...");
					servoLock();
				}
				//If face was not accepted
				else if (wrong_count < 2)
				{
					IOWR_ALTERA_AVALON_PIO_DATA(GREEN_LED_BASE, 0);
					lcd_write("Incorrect Face");
					wrong_count++;
					for (i = 0; i < 3; i++){
						usleep(250000);
						IOWR_ALTERA_AVALON_PIO_DATA(RED_LED_BASE, 0x3ffff);
						usleep(250000);
						IOWR_ALTERA_AVALON_PIO_DATA(RED_LED_BASE, 0);
					}
				}
				//If face was not accepted and 3 wrong attempts in a row
				else {
					IOWR_ALTERA_AVALON_PIO_DATA(GREEN_LED_BASE, 0);
					wrong_count = 0;
					char * lock_string = malloc(20 * sizeof(char));
					for (i = 15; i > 0; i--){
						sprintf(lock_string, "Locked for %d s", i);
						lcd_write(lock_string);
						usleep(50000);
						IOWR_ALTERA_AVALON_PIO_DATA(RED_LED_BASE, 0x3ffff);
						usleep(50000);
						IOWR_ALTERA_AVALON_PIO_DATA(RED_LED_BASE, 0);
					}
					free(lock_string);
				}
		}
		//If keypad code was not accepted
		else if (wrong_count < 2)
		{
			IOWR_ALTERA_AVALON_PIO_DATA(GREEN_LED_BASE, 0);
			lcd_write("Incorrect Code");
			wrong_count++;
			for (i = 0; i < 3; i++){
				usleep(250000);
				IOWR_ALTERA_AVALON_PIO_DATA(RED_LED_BASE, 0x3ffff);
				usleep(250000);
				IOWR_ALTERA_AVALON_PIO_DATA(RED_LED_BASE, 0);
			}
		}
		//If code was not accepted and 3 wrong attempts in a row
		else {
			IOWR_ALTERA_AVALON_PIO_DATA(GREEN_LED_BASE, 0);
			wrong_count = 0;
			char * lock_string = malloc(20 * sizeof(char));
			for (i = 15; i > 0; i--){
				sprintf(lock_string, "Locked for %d s", i);
				lcd_write(lock_string);
				usleep(500000);
				IOWR_ALTERA_AVALON_PIO_DATA(RED_LED_BASE, 0x3ffff);
				usleep(500000);
				IOWR_ALTERA_AVALON_PIO_DATA(RED_LED_BASE, 0);
			}
			free(lock_string);
		}

  } //end of while loop

  return 0;
}

void super_mode(void){
	//Wait for button 3 to be pressed
	printf("Waiting For Button Press\n");
	//Stop polling once the switch is pushed down
	while((IORD_ALTERA_AVALON_PIO_DATA(BUTTON_3_BASE) & 1) == 1){
		if(!(IORD_ALTERA_AVALON_PIO_DATA(MODE_SWITCH_BASE) & 1))
			return;
	}

	//START OF DMA CODE (MEMORY TO MEMORY)
	int rc;
	alt_dma_txchan txchan;
	alt_dma_rxchan rxchan;

	char * buffer = malloc(153600);

	assert(buffer);

	//Initialize source and destination
	void* tx_data = (void*) FRAME_SAVE_DMA_READ_MASTER_PIXEL_BUFFER_BASE; // pointer to data to send
	void* rx_buffer = (void*) buffer; // pointer to rx buffer

	// Create transmit channel
	if ((txchan = alt_dma_txchan_open(FRAME_SAVE_DMA_NAME)) == NULL)
	{
	  printf ("Failed to open transmit channel\n");
	  exit (1);
	}
	// create receive channel
	if ((rxchan = alt_dma_rxchan_open(FRAME_SAVE_DMA_NAME)) == NULL)
	{
	  printf ("Failed to open receive channel\n");
	  exit (1);
	}

	//Specify the size
	alt_dma_rxchan_ioctl(rxchan, ALT_DMA_SET_MODE_8, NULL);
	alt_dma_txchan_ioctl(txchan, ALT_DMA_SET_MODE_8, NULL);


	//Create receive Request
	if ((rc = alt_dma_rxchan_prepare (rxchan,
		  rx_buffer,
		  153600,
		  done,
		  NULL)) < 0)
	{
	  printf ("Failed to request read: %i\n", rc);
	  exit (1);
	}

	// Create send request
	if ((rc = alt_dma_txchan_send (txchan,
		  tx_data,
		  153600,
		  NULL,
		  NULL)) < 0)
	{
	  printf ("Failed to request send: %i\n", rc);
	  exit (1);
	}


	printf("Transfering...\n");
	// wait for transfer to complete
	while (!rx_done);

	//Close the send and recieve channels
	alt_dma_rxchan_close(rxchan);
	alt_dma_txchan_close(txchan);

	printf ("Transfer successful!\n");

	//END OF DMA CODE

	//Send buffer data to the Raspberry Pi
	send_buffer( buffer );
	free(buffer);

	//Wait for button 3 to be released (if still pressed)
	while ((IORD_ALTERA_AVALON_PIO_DATA(BUTTON_3_BASE) & 1) == 0);
}

char readKeypad(void){
	char key = -1;

	//Left Column top to bottom
	IOWR_ALTERA_AVALON_PIO_DATA(KEYPAD_COLS_BASE, 1);
	usleep(20);
	if (IORD_ALTERA_AVALON_PIO_DATA(KEYPAD_ROWS_BASE) & 1)
		key = 1; //1
	else if (IORD_ALTERA_AVALON_PIO_DATA(KEYPAD_ROWS_BASE) & 2)
		key = 4;
	else if (IORD_ALTERA_AVALON_PIO_DATA(KEYPAD_ROWS_BASE) & 4)
		key = 7;
	else if (IORD_ALTERA_AVALON_PIO_DATA(KEYPAD_ROWS_BASE) & 8)
		key = 10; //STAR

	//Middle Column top to bottom
	IOWR_ALTERA_AVALON_PIO_DATA(KEYPAD_COLS_BASE, 2);
	usleep(20);
	if (IORD_ALTERA_AVALON_PIO_DATA(KEYPAD_ROWS_BASE) & 1)
		key = 2; //2
	else if (IORD_ALTERA_AVALON_PIO_DATA(KEYPAD_ROWS_BASE) & 2)
		key = 5;
	else if (IORD_ALTERA_AVALON_PIO_DATA(KEYPAD_ROWS_BASE) & 4)
		key = 8;
	else if (IORD_ALTERA_AVALON_PIO_DATA(KEYPAD_ROWS_BASE) & 8)
		key = 0;

	//Right Column top to bottom
	IOWR_ALTERA_AVALON_PIO_DATA(KEYPAD_COLS_BASE, 4);
	usleep(20);
	if (IORD_ALTERA_AVALON_PIO_DATA(KEYPAD_ROWS_BASE) & 1)
		key = 3; //3
	else if (IORD_ALTERA_AVALON_PIO_DATA(KEYPAD_ROWS_BASE) & 2)
		key = 6;
	else if (IORD_ALTERA_AVALON_PIO_DATA(KEYPAD_ROWS_BASE) & 4)
		key = 9;
	else if (IORD_ALTERA_AVALON_PIO_DATA(KEYPAD_ROWS_BASE) & 8)
		key = 11; //POUND

	usleep(100000);

	return key;
}

void keyRelease(void){
	int pressed = 1;

	while(pressed == 1){
		pressed = 0;

		//Left Column top to bottom
		IOWR_ALTERA_AVALON_PIO_DATA(KEYPAD_COLS_BASE, 1);
		if (IORD_ALTERA_AVALON_PIO_DATA(KEYPAD_ROWS_BASE) & 1)
			pressed = 1;
		else if (IORD_ALTERA_AVALON_PIO_DATA(KEYPAD_ROWS_BASE) & 2)
			pressed = 1;
		else if (IORD_ALTERA_AVALON_PIO_DATA(KEYPAD_ROWS_BASE) & 4)
			pressed = 1;
		else if (IORD_ALTERA_AVALON_PIO_DATA(KEYPAD_ROWS_BASE) & 8)
			pressed = 1; //STAR

		//Middle Column top to bottom
		IOWR_ALTERA_AVALON_PIO_DATA(KEYPAD_COLS_BASE, 2);
		if (IORD_ALTERA_AVALON_PIO_DATA(KEYPAD_ROWS_BASE) & 1)
			pressed = 1;
		else if (IORD_ALTERA_AVALON_PIO_DATA(KEYPAD_ROWS_BASE) & 2)
			pressed = 1;
		else if (IORD_ALTERA_AVALON_PIO_DATA(KEYPAD_ROWS_BASE) & 4)
			pressed = 1;
		else if (IORD_ALTERA_AVALON_PIO_DATA(KEYPAD_ROWS_BASE) & 8)
			pressed = 1;

		//Right Column top to bottom
		IOWR_ALTERA_AVALON_PIO_DATA(KEYPAD_COLS_BASE, 4);
		if (IORD_ALTERA_AVALON_PIO_DATA(KEYPAD_ROWS_BASE) & 1)
			pressed = 1;
		else if (IORD_ALTERA_AVALON_PIO_DATA(KEYPAD_ROWS_BASE) & 2)
			pressed = 1;
		else if (IORD_ALTERA_AVALON_PIO_DATA(KEYPAD_ROWS_BASE) & 4)
			pressed = 1;
		else if (IORD_ALTERA_AVALON_PIO_DATA(KEYPAD_ROWS_BASE) & 8)
			pressed = 1; //POUND

	}

	usleep(100000);

	return;

}

char * readKeypadCode(void){
	char key;
	char  * combo = malloc(5*sizeof(char));
	int i;

	for (i = 0; i < 4; i ++){
		key = -1;
		while(key == -1)
			key = readKeypad();

		printf("%d\n", key);
		combo[i] = key;
		keyRelease();
	}

	combo[4] = '\0';

	return combo;
}

void servoLock(){
	int i;
	for(i = 0; i < 20; i++){
		IOWR_ALTERA_AVALON_PIO_DATA(SERVO_CONTROLLER_BASE, 1);
		usleep(490);
		IOWR_ALTERA_AVALON_PIO_DATA(SERVO_CONTROLLER_BASE, 0);
		usleep(19510);
	}
	return;
}

void servoUnlock(){
	int i;
	for(i = 0; i < 20; i++){
		IOWR_ALTERA_AVALON_PIO_DATA(SERVO_CONTROLLER_BASE, 1);
		usleep(2400);
		IOWR_ALTERA_AVALON_PIO_DATA(SERVO_CONTROLLER_BASE, 0);
		usleep(18600);
	}
	return;
}

void lcd_write( char* string ){

	//Clears the whole lcd screen
	alt_up_character_lcd_init (char_lcd_dev);

	alt_up_character_lcd_string( char_lcd_dev, string );

	return;
}

void lcd_init( void ){

	// open the Character LCD port
	char_lcd_dev = alt_up_character_lcd_open_dev ("/dev/character_lcd_0");

	if ( char_lcd_dev == NULL){
		printf ("Error: could not open character LCD device\n");
		return;
	}

}

