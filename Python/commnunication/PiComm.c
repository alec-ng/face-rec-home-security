#include <bcm2835.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

#define DE2_FLAG RPI_GPIO_P1_16
#define PI_FLAG RPI_GPIO_P1_18
#define BUFFER0 RPI_BPLUS_GPIO_J8_40
#define BUFFER1 RPI_BPLUS_GPIO_J8_38
#define BUFFER2 RPI_BPLUS_GPIO_J8_36
#define BUFFER3 RPI_BPLUS_GPIO_J8_32
#define BUFFER4 RPI_BPLUS_GPIO_J8_37
#define BUFFER5 RPI_BPLUS_GPIO_J8_35
#define BUFFER6 RPI_BPLUS_GPIO_J8_33
#define BUFFER7 RPI_BPLUS_GPIO_J8_31

char receive(void);

int main(int argc, char **argv)
{
    // If you call this, it will not actually access the GPIO
    // Use for testing
//    bcm2835_set_debug(1);
    if (!bcm2835_init())
        return 1;
    // Set RPI pin P1-16 to be an input
    //  with a pullup
    bcm2835_gpio_fsel(DE2_FLAG, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(DE2_FLAG, BCM2835_GPIO_PUD_UP);

    bcm2835_gpio_fsel(PI_FLAG, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_set_pud(PI_FLAG, BCM2835_GPIO_PUD_UP);

    bcm2835_gpio_fsel(BUFFER0, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(BUFFER0, BCM2835_GPIO_PUD_UP);

    bcm2835_gpio_fsel(BUFFER1, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(BUFFER1, BCM2835_GPIO_PUD_UP);

    bcm2835_gpio_fsel(BUFFER2, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(BUFFER2, BCM2835_GPIO_PUD_UP);

    bcm2835_gpio_fsel(BUFFER3, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(BUFFER3, BCM2835_GPIO_PUD_UP);

    bcm2835_gpio_fsel(BUFFER4, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(BUFFER4, BCM2835_GPIO_PUD_UP);

    bcm2835_gpio_fsel(BUFFER5, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(BUFFER5, BCM2835_GPIO_PUD_UP);

    bcm2835_gpio_fsel(BUFFER6, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(BUFFER6, BCM2835_GPIO_PUD_UP);

    bcm2835_gpio_fsel(BUFFER7, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(BUFFER7, BCM2835_GPIO_PUD_UP);

    while (1){
       //  Read some data
       char value = receive();
        printf("%c", value);
        
    }

    struct timeval start, end;
    long mtime, secs, usecs;
    gettimeofday(&start, NULL);
    int i;
    for(i = 0;i < 150000; i++){
        char j = receive();
	//printf("%c", j);
    }
    gettimeofday(&end, NULL);
    secs = end.tv_sec - start.tv_sec;
    usecs = end.tv_usec - start.tv_usec;
    mtime = ((secs)*1000+usecs/1000.0) +0.5;
    printf("%d chars were received in %d milliseconds\n",i, mtime);
    while(1);
    bcm2835_close();
    return 0;
}

char receive(void) {
    bcm2835_gpio_write(PI_FLAG, LOW);
    while(bcm2835_gpio_lev(DE2_FLAG) == LOW);
    char received = bcm2835_gpio_lev(BUFFER0);
    received <<= 1;
    received |= bcm2835_gpio_lev(BUFFER1);
    received <<= 1;
    received |= bcm2835_gpio_lev(BUFFER2);
    received <<= 1;
    received |= bcm2835_gpio_lev(BUFFER3);
    received <<= 1;
    received |= bcm2835_gpio_lev(BUFFER4);
    received <<= 1;
    received |= bcm2835_gpio_lev(BUFFER5);
    received <<= 1;
    received |= bcm2835_gpio_lev(BUFFER6);
    received <<= 1;
    received |= bcm2835_gpio_lev(BUFFER7);
    bcm2835_gpio_write(PI_FLAG, HIGH);
    while(bcm2835_gpio_lev(DE2_FLAG) == HIGH);
    bcm2835_gpio_write(PI_FLAG, LOW);
    return received;
}
