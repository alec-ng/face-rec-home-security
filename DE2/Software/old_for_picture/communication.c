#include "communication.h"

void send_string( char *string ){

	unsigned long length = 0;

	send_type(STRING_TYPE);

	//Different for each data type
	length = (unsigned long)strlen( string );

	//length = 150600;

	send_length( length );

	send_data( string , length );

}

void send_buffer( char *buffer ){

	send_type(BUFFER_TYPE);

	send_length(BUFFER_LENGTH);

	send_data( buffer , BUFFER_LENGTH );
}


void send_data( char* data , unsigned long length ){

	int i;

	for( i = 0 ; i < length ; i++ ){
//		if( length % 10000 == 0 )
				//printf( "%i    " , i );
		send_byte(data[i]);
	}
}

void send_type( char type ){
	send_byte( type );
}

void send_length( unsigned long length ){

	int i;

	for( i = 0 ; i < 4 ; i++ ){

		switch( i ){
		case 0 :
			send_byte( (char)( length & 0x000000FF ) );
			break;
		case 1 :
			send_byte( (char)( ( length & 0x0000FF00 ) >> 8 ) );
			break;
		case 2 :
			send_byte( (char)( ( length & 0x00FF0000 ) >> 16 ) );
			break;
		case 3 :
			send_byte( (char)( ( length & 0xFF000000 ) >> 24 ) );
			break;
		}

	}
}

void init_comm(){

	IOWR_ALTERA_AVALON_PIO_DATA( P_DATA_BASE, ZERO );
	IOWR_ALTERA_AVALON_PIO_DATA( P_SIGNAL_BASE, ZERO );

}

void send_byte( char data ){

	//printf("send data\n");
	IOWR_ALTERA_AVALON_PIO_DATA( P_DATA_BASE, data );

	//printf("valid HIGH\n");
	IOWR_ALTERA_AVALON_PIO_DATA( P_SIGNAL_BASE, VALID_HIGH );

	//printf("wait for ack HIGH\n");
	while( !(IORD_ALTERA_AVALON_PIO_DATA(P_INPUT_BASE) & 0x01) );

	//printf("valid LOW");
	IOWR_ALTERA_AVALON_PIO_DATA( P_SIGNAL_BASE, VALID_LOW );

	//printf("wait for ack LOW\n");
	while( (IORD_ALTERA_AVALON_PIO_DATA(P_INPUT_BASE) & 0x01) );

}

