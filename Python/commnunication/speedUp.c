#include <Python.h>
#include <wiringPi.h>
#include <unistd.h>

int gpio_setup( void );
char get_byte( void );
char do_transfer( void );


//The wiringPi library has specific pin bindings 
//To see the pin bindings if you have the wiringPi library installed in cmdline write "gpio readall"
#define PIN18 1
#define PIN23 4
#define PIN24 5
#define PIN25 6
#define PIN12 26
#define PIN16 27
#define PIN20 28
#define PIN21 29
#define PIN17 0
#define PIN27 2
#define PIN22 3

//DO NOT USE THESE PINS NOT SURE IF THEY WORK
#define PIN08 10 //CE0 DONT WORK IN C DO NOT USE
#define PIN07 11 //CE1 DONT WORK IN C DO NOT USE
#define PIN04 7 //NOT SURE IF WORKING 

//Define a new exception object for out module
static PyObject * exmodError;

static PyObject * exmod_get_data_c( PyObject * self , PyObject * args ){
	
	unsigned int length = 0;
	int type;
	int i = 0;
	int temp;
	char* Incoming = malloc( sizeof( char ) * 153600 );
	char* Outgoing = malloc( sizeof( char ) * 230400 );

	gpio_setup();

	type = do_transfer();

	printf( "TYPE: %d\n" , type );

	for( i = 0 ; i < 4 ; i++ ){

		if( i == 0 )
                        length |= (do_transfer());
                else if( i == 1 )
                        length |= (do_transfer() << 8);
                else if( i == 2 )
                        length |= (do_transfer() << 16);
                else if( i == 3 )
                        length |= (do_transfer() << 24);

	}

	printf( "LENGTH: %u\n" , length );

	PyObject * list = PyList_New( length );

	for( i = 0 ; i < length ; i++ ){
	
		temp = do_transfer();

		PyObject * num =  Py_BuildValue( "i" , temp );
		Incoming[i] = temp;
		
		//PyList_SET_ITEM( list , index , data )

		PyList_SET_ITEM( list , i , num );

	}

	printf( "TRANSFER DONE\n" );

	if( type != 1 )
		return list;

	for( i = 0 ; i < length/2 ; i++ ){
		Outgoing[(i*3)] = ( ( Incoming[i*2] & 0b00011111 ) * 8 );
		Outgoing[(i*3)+1] = ( ( ( Incoming[(i*2)+1] & 0b00000111 ) * 32 ) + ( ( Incoming[(i*2)] & 0b11100000 ) / 8 ) );
		Outgoing[(i*3)+2] = ( ( Incoming[(i*2)+1] & 0b11111000 ) );
	}

	printf( "16 to 24 CONVERSION FINISHED\n" );

	int width = 320;
	int height = 240;
	int y, x;
	char* name = malloc( sizeof( char ) * 50 );
	char* name_full;

	if( !PyArg_ParseTuple( args , "s" , &name ) ){
		strcpy( name , "output" );
	}

	name_full = strcat( name , ".ppm" );

	FILE *f = fopen( "temp.ppm" , "wb" );

	fprintf( f, "P6\n%i %i 255\n", width, height );

	for( y = 0 ; y < height ; y++ ){

		for( x = 0 ; x < width ; x++ ){
			
			fputc( Outgoing[((320*y)+(x))*3+2] , f ); //Red
			fputc( Outgoing[((320*y)+(x))*3+1] , f ); //Gree
			fputc( Outgoing[((320*y)+(x))*3+0], f );  //Blue

		}

	}

	fclose( f );

	printf( "CREATED IMAGE NAMED IMG %s\n" , "temp.ppm" );

	return list;
}

int gpio_setup( void ){
	
	wiringPiSetup();

	pinMode( PIN21 , INPUT );
	pinMode( PIN20 , INPUT );
	pinMode( PIN16 , INPUT );
	pinMode( PIN12 , INPUT );
	pinMode( PIN27 , INPUT );
	pinMode( PIN17 , INPUT );
	pinMode( PIN25 , INPUT );
	pinMode( PIN24 , INPUT );
	pinMode( PIN23 , INPUT );
	pinMode( PIN22 , OUTPUT );

	digitalWrite( PIN22 , LOW );

	printf( "GPIO setup successfully\n" );

	return 0;
}


char get_byte( void ){

	char byte = 0;

	if( digitalRead( PIN12 ) == HIGH )
		byte |= 0x01;
	if( digitalRead( PIN17 ) == HIGH )
		byte |= 0x02;
	if( digitalRead( PIN16 ) == HIGH )
		byte |= 0x04;
	if( digitalRead( PIN27 ) == HIGH )
		byte |= 0x08;
	if( digitalRead( PIN20 ) == HIGH )
		byte |= 0x10;
	if( digitalRead( PIN25 ) == HIGH )
		byte |= 0x20;
	if( digitalRead( PIN21 ) == HIGH )
		byte |= 0x40;
	if( digitalRead( PIN24 ) == HIGH )
		byte |= 0x80;

	//printf( "BYTE VALUE: %d\n" , byte );

	return byte;

}

char do_transfer( void ){

	char byte;
	//int sleepAmount = 0;

	//usleep( sleepAmount );
	//printf("waiting for valid HIGH\n");
        while( digitalRead( PIN23 ) == LOW );
	//usleep( sleepAmount );

        //printf("reading data\n");
        byte = get_byte();
	//usleep( sleepAmount );
        //printf( "DATA READ: %d \n" , byte );

	//usleep( sleepAmount );
        //printf("ack HIGH\n");
        digitalWrite( PIN22 , HIGH );

	//usleep( sleepAmount );
        //printf("waiting for valid LOW\n");
        while( digitalRead( PIN23 ) == HIGH );
	//usleep( sleepAmount );

        //printf("ack LOW \n");
        digitalWrite( PIN22 , LOW );
	//usleep( sleepAmount );

	return byte;

}

static PyMethodDef exmod_methods[] = {
	//"PythonName"	"C-function Name" 	argument_presentation	description
	{"get_data", 	exmod_get_data_c, 	METH_VARARGS, 		"Gets the DMA from the DE2 using GPIO COMM" },
	{NULL, NULL , 0 , NULL} //MUST HAVE DO NOT REMOVE
};

PyMODINIT_FUNC initexmod(void){
	PyObject *m;
	m = Py_InitModule( "exmod" , exmod_methods );
	if( m == NULL )
		return; 

	exmodError = PyErr_NewException( "exmod.error", NULL , NULL );
	Py_INCREF(exmodError);

	PyModule_AddObject( m , "error" , exmodError );
}

