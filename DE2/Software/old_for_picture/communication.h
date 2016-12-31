#ifndef COMM
#define COMM

#include "system.h"
#include "altera_avalon_pio_regs.h"
#include <stdio.h>

#define ZERO 0x00
#define VALID_HIGH 0x02
#define VALID_LOW 0x00
#define STRING_TYPE 0x02
#define BUFFER_TYPE 0x01
#define BUFFER_LENGTH 153600

void send_string( char *string );

void send_buffer( char *buffer );

void send_data( char* data , unsigned long length );

void send_type( char type );

void send_length( unsigned long length );

void init_comm();

void send_byte( char data );



#endif
