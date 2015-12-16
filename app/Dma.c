#include "Dma.h"

void configureDMA1ForDAC1()
{
  //CHANNEL SELECTION
 	Dma1_reg->S5.CR &= ~ (7 << 25);
	Dma1_reg->S5.CR |= 7 << 25;

  //memory burst transfer
  Dma1_reg->S5.CR &= ~ (3 << 23);
	Dma1_reg->S5.CR |= ~ (3 << 23);

  //peripheral burst transfer
  Dma1_reg->S5.CR &= ~ (3 << 21);
	Dma1_reg->S5.CR |= ~ (3 << 21);
  
  //Current target (only in double buffer mode)
	Dma1_reg->S5.CR &= ~ (1 << 19);
	Dma1_reg->S5.CR |= (1 << 19);

  //Current target (only in double buffer mode)
	Dma1_reg->S5.CR &= ~ (1 << 18);
	Dma1_reg->S5.CR |= (1 << 18);
  
  //Memory data size
  Dma1_reg->S5.CR &= ~ (3 << 13);
	Dma1_reg->S5.CR |= ~ (3 << 13);
  
  //Peripheral data size
  Dma1_reg->S5.CR &= ~ (3 << 11);
	Dma1_reg->S5.CR |= ~ (3 << 11);
  
  //Memory increment mode
	Dma1_reg->S5.CR |= (1 << 10);

  //Memory increment mode
	Dma1_reg->S5.CR |= (0 << 9);
  
  //Data transfer direction
  Dma1_reg->S5.CR &= ~ (3 << 6);
	Dma1_reg->S5.CR |= Memory_to_peripheral << 6;
  
  //Peripheral flow controller
  Dma1_reg->S5.CR &= ~ (1 << 5);
  Dma1_reg->S5.CR |= ~ (1 << 5);
  
  //Transfer complete interrupt enable
  Dma1_reg->S5.CR |= (1 << 4);
  //Half transfer interrupt enable
  Dma1_reg->S5.CR |= (1 << 3);
  //Transfer error interrupt enable
  Dma1_reg->S5.CR |= (1 << 2);
  //Direct mode error interrupt enable
  Dma1_reg->S5.CR |= (1 << 1);
  


	ptr->NDTR = (uint32_t)dataSize;
	if(transDireation == PERIPHERAL_TO_MEMORY){
		ptr->PAR = (uint32_t)source;
		ptr->M0AR = (uint32_t)destination;
	}
  else if(transDireation == MEMORY_TO_PERIPHERAL){
		ptr->PAR = (uint32_t)destination;
		ptr->M0AR = (uint32_t)source;
	}else if( transDireation == MEMORT_TO_MEMORY){
		ptr->PAR = (uint32_t)source;
		ptr->M0AR = (uint32_t)destination;
	}
	// checkNDTR = ptr->NDTR;
	// checkCR = ptr->CR;
    // checkPAR = ptr->PAR;
	// checkM0AR = ptr->M0AR;
}



void enableDma()
{
  Dma1_reg->S5.CR |= 1;
}

void DMA_memcpy8(uint32_t peripheralAddress, uint32_t sourceAddress, int numOfData )
{
    														/* As per page 233 this is how to configure a stream */
	uint32_t read ;
	if((Dma1_reg->S5.CR & 1) == 1 )
  {
    Dma1_reg->S5.CR  &= ~ 1 ;  					// 1. If stream is enabled, disable it
    while( ( dma2->S7.CR & ( 1 << EN ) == 1) );
  }
	Dma1_reg->S5.M0AR = sourceAddress;					/* source address */
	Dma1_reg->S5.PAR = peripheralAddress; 					/* destination address */
  Dma1_reg->S5.NDTR = numOfData ;  							// Number of data items to transfer
  read = Dma1_reg->S5.CR;
}

int getDMA2Status( int st,int posBit ){
 uint32_t checkLISR = DMA2->LISR;
 uint32_t checkHISR = DMA2->HISR;
 if(st < 4)
  return (( DMA2->LISR >> posBit) & 1 );
 else
  return (( DMA2->HISR >> posBit) & 1 );
}

int getDMA1Status( int st,int posBit ){
 uint32_t checkLISR = DMA1->LISR;
 uint32_t checkHISR = DMA1->HISR;
 if(st < 4)
  return (( DMA1->LISR >> posBit) & 1 );
 else
  return (( DMA1->HISR >> posBit) & 1 );
}

void clearDMAFlag(DMA* dma,int st,int posBit){
   uint32_t checkLIFCR;
   uint32_t checkHIFCR;

  if(st < 4)
	  dma->LIFCR |= ( 1 << posBit );
  else
	  dma->HIFCR |= ( 1 << posBit );

  checkHIFCR= dma->HIFCR;
  checkLIFCR = dma->LIFCR;
  uint32_t checkLISR = DMA1->LISR;
  uint32_t checkHISR = DMA1->HISR;
}

void clearDMAstatus(DMA* dma,int st){
	uint32_t checkLIFCR = DMA1->HIFCR;
	uint32_t checkHIFCR = DMA1->LIFCR;
	if(st < 4)
		DMA1->LIFCR =  (uint32_t)1 ;
	else
		DMA1->HIFCR =  (uint32_t)1 ;
	 checkHIFCR= DMA1->HIFCR;
	 checkLIFCR = DMA1->LIFCR;
	 uint32_t checkLISR = DMA1->LISR;
	 uint32_t checkHISR = DMA1->HISR;
}