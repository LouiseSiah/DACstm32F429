#include "Dma.h"

void configureDMA1ForDAC1()
{
	int readDma = 0;
  //CHANNEL SELECTION
 	Dma1_reg->S5.CR &= ~ (7 << 25);
 	readDma = Dma1_reg->S5.CR;
 	Dma1_reg->S5.CR |= 7 << 25;
 	readDma = Dma1_reg->S5.CR;
  //memory burst transfer
	Dma1_reg->S5.CR &= ~ (3 << 23);
	readDma = Dma1_reg->S5.CR;
	Dma1_reg->S5.CR |= 0 << 23;
	readDma = Dma1_reg->S5.CR;

  //peripheral burst transfer
	Dma1_reg->S5.CR &= ~ (3 << 21);
	readDma = Dma1_reg->S5.CR;
	Dma1_reg->S5.CR |= 0 << 21;
	readDma = Dma1_reg->S5.CR;


  //Peripheral flow controller
	Dma1_reg->S5.CR &= ~ (1 << 5);
	readDma = Dma1_reg->S5.CR;
	Dma1_reg->S5.CR |= 0 << 5;
	readDma = Dma1_reg->S5.CR;


  //Transfer complete interrupt enable
	Dma1_reg->S5.CR &= ~(1 << 4);
	readDma = Dma1_reg->S5.CR;
  //Half transfer interrupt enable
	Dma1_reg->S5.CR &= ~(1 << 3);
	readDma = Dma1_reg->S5.CR;
  //Transfer error interrupt enable
  	Dma1_reg->S5.CR &= ~(1 << 2);
  	readDma = Dma1_reg->S5.CR;
  //Direct mode error interrupt enable
  	Dma1_reg->S5.CR &= ~(1 << 1);
  	readDma = Dma1_reg->S5.CR;


}

void enableDma()
{
	uint32_t read;
	Dma1_reg->S5.CR |= 1;
	read = Dma1_reg->S5.CR;
}

void disableDma()
{
	Dma1_reg->S5.CR &= ~ 1;
	Dma1_reg->S5.CR |= 0;
}

void cleaDmaHighInterruptFlag(int streamToClear)
{
	uint32_t read;
	Dma1_reg->HIFCR = streamToClear;
	read = Dma1_reg->HIFCR;
}

void enableMemoryIncrement(int enable)
{
	Dma1_reg->S5.CR &= ~ (1 << 10);
	Dma1_reg->S5.CR |= (enable << 10);
}

void enablePeripheralIncrement(int enable)
{
	Dma1_reg->S5.CR &= ~ (1 << 9);
	Dma1_reg->S5.CR |= (enable << 9);
}

void memoryDataSize(int dataSize)
{
	Dma1_reg->S5.CR &= ~ (3 << 13);
	Dma1_reg->S5.CR |= (dataSize << 13);
}

void peripheralDataSize(int dataSize)
{
	Dma1_reg->S5.CR &= ~ (3 << 11);
	Dma1_reg->S5.CR |= (dataSize << 11);
}

void numberOfDataTransferDMA(int numOfData)
{
	uint32_t read;
	Dma1_reg->S5.NDTR = numOfData;
	read = Dma1_reg->S5.NDTR;
}

void peripheralBaseAddr(uint32_t address)
{
	uint32_t read;
	disableDma();
	Dma1_reg->S5.PAR = (uint32_t)address; 		/* destination address */
	read = Dma1_reg->S5.PAR ;
}

void memory0BaseAddr(uint32_t address)
{
	uint32_t read;
	disableDma();
	Dma1_reg->S5.M0AR = (uint32_t)address;	/* source address */
	read = Dma1_reg->S5.M0AR ;
}

void memory1BaseAddr(uint32_t address)
{
	uint32_t read;
	disableDma();
	read = Dma1_reg->S5.CR;
	Dma1_reg->S5.M1AR = (uint32_t)address;
	read = Dma1_reg->S5.M1AR;
}

void dataTransferDirection(int direction)
{
	uint32_t read;
	Dma1_reg->S5.CR &= ~ (3 << 6);
	Dma1_reg->S5.CR |= direction << 6;
	read = Dma1_reg->S5.CR;
}

void priority(int level)
{
	uint32_t read;
	Dma1_reg->S5.CR &= ~ (3 << 16);
	Dma1_reg->S5.CR |= level << 16;
	read = Dma1_reg->S5.CR;
}


void enableMemoryCircularMode(int enable)
{
	Dma1_reg->S5.CR &= ~ (1 << 8);
	Dma1_reg->S5.CR |= (enable << 8);
}

void enableDoubleBufferMode(int enable)
{
	Dma1_reg->S5.CR &= ~ (1 << 18);
	Dma1_reg->S5.CR |= (enable << 18);


	//  //Current target (only in double buffer mode)
	//	Dma1_reg->S5.CR &= ~ (1 << 19);
	//	Dma1_reg->S5.CR |= ~(1 << 19);

}
/*
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
*/
