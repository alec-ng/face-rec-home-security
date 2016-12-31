#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <system.h>
#include "sys/alt_dma.h"
#include "alt_types.h"
#include <sys/alt_irq.h>
#include <io.h>
#include "communication.h"

volatile int rx_done = 0;

/*
* Callback function that obtains notification that the data
* is received.
*/
void done (void* handle, int * data)
{
	rx_done++;
}


int main()
{

	init_comm();

  while(1){

	  printf("2\n");
	  while((IORD_ALTERA_AVALON_PIO_DATA(BUTTON_3_BASE) & 1) == 1);

	  //START OF DMA CODE (MEMORY TO MEMORY?)

	  int rc;
	  alt_dma_txchan txchan;
	  alt_dma_rxchan rxchan;

	  char * buffer = malloc(153600);

	  assert(buffer);

	  void* tx_data = (void*) FRAME_SAVE_DMA_READ_MASTER_PIXEL_BUFFER_BASE; /* pointer to data to send */
	  void* rx_buffer = (void*) buffer; /* pointer to rx buffer */

	  /* Create the transmit channel */
	  if ((txchan = alt_dma_txchan_open(FRAME_SAVE_DMA_NAME)) == NULL)
	  {
		  printf ("Failed to open transmit channel\n");
		  exit (1);
	  }
	  /* Create the receive channel */
	  if ((rxchan = alt_dma_rxchan_open(FRAME_SAVE_DMA_NAME)) == NULL)
	  {
		  printf ("Failed to open receive channel\n");
		  exit (1);
	  }

	  alt_dma_rxchan_ioctl(rxchan, ALT_DMA_SET_MODE_8, NULL);
	  alt_dma_txchan_ioctl(txchan, ALT_DMA_SET_MODE_8, NULL);

	  //printf("TX chan space: %d\n", alt_dma_txchan_space(txchan));
	  //printf("RX chan space: %d\n", alt_dma_rxchan_depth(rxchan));

	  /* Post the receive request */
	  if ((rc = alt_dma_rxchan_prepare (rxchan,
			  rx_buffer,
			  153600,
//			  1024,
			  done,
			  NULL)) < 0)
	  {
		  printf ("Failed to post read request, reason = %i\n", rc);
		  exit (1);
	  }

	  /* Post the transmit request */
	  if ((rc = alt_dma_txchan_send (txchan,
			  tx_data,
			  153600,
//			  8,
			  NULL,
			  NULL)) < 0)
	  {
		  printf ("Failed to post transmit request, reason = %i\n", rc);
		  exit (1);
	  }


	  printf("Transfering...\n");
	  /* wait for transfer to complete */
	  while (!rx_done);

	  alt_dma_rxchan_close(rxchan);
	  alt_dma_txchan_close(txchan);

	  printf ("Transfer successful!\n");

	  //END OF DMA CODE

	  send_buffer( buffer );

	  while ((IORD_ALTERA_AVALON_PIO_DATA(BUTTON_3_BASE) & 1) == 0);

  }

  return 0;
}
