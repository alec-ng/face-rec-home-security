#ifndef COMM
#define COMM

#include "system.h"
#include "altera_avalon_pio_regs.h"
#include <stdio.h>

#define ZERO 0x00
#define VALID_HIGH 0x02
#define VALID_LOW 0x00
#define BUFFER_TYPE 0x01
#define BUFFER_LENGTH 153600
#define CODE_TYPE 0x02
#define CODE_LENGTH 4

void send_code( char *code );

void send_buffer( char *buffer );

void send_data( char* data , unsigned long length );

void send_type( char type );

void send_length( unsigned long length );

void init_comm();

void send_byte( char data );



#endif
