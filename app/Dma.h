#ifndef __Dma_H__
#define __Dma_H__

#include <stdint.h>

typedef struct{
	  volatile uint32_t CR;
	  volatile uint32_t NDTR;
	  volatile uint32_t PAR;
	  volatile uint32_t M0AR;
	  volatile uint32_t M1AR;
	  volatile uint32_t FCR;
}Stream_t;

typedef struct DMA_Type DMAtype;
struct DMA_Type{
  volatile uint32_t LISR;
  volatile uint32_t HISR;
  volatile uint32_t LIFCR;
  volatile uint32_t HIFCR;
  Stream_t	S0;
  Stream_t	S1;
  Stream_t	S2;
  Stream_t	S3;
  Stream_t	S4;
  Stream_t	S5;
  Stream_t	S6;
  Stream_t	S7;
};

#define Dma1_reg  ((DMAtype *)0x40026000)

#define EN 1

#define CLEAR_S4	(0x3D)
#define CLEAR_S5	(0x3D << 6)
#define CLEAR_S6	(0x3D << 16)
#define CLEAR_S7	(0x3D << 22)

enum dataSize
{
	BYTE,   	//8 BIT
	HALF_WORD,	//16 BIT
	WORD		//32 BIT
};

enum direction
{
	PeripheralToMemory,
	MemoryToPeripheral,
	MemoryToMemory
};

enum priorityLevel
{
	Low,
	Medium,
	High,
	VeryHigh
};

void configureDMA1ForDAC1();
void enableDma();
void disableDma();
void cleaDmaHighInterruptFlag(int streamToClear);
void enableMemoryIncrement(int enable);
void enablePeripheralIncrement(int enable);
void memoryDataSize(int dataSize);
void peripheralDataSize(int dataSize);
void numberOfDataTransferDMA(int numOfData);
void peripheralBaseAddr(uint32_t address);
void memory0BaseAddr(uint32_t address);
void memory1BaseAddr(uint32_t address);
void dataTransferDirection(int direction);
void priority(int level);
void enableMemoryCircularMode(int enable);
void enableDoubleBufferMode(int enable);
/*
void clearDMAFlag(DMA* dma,int st,int posBit);
void clearDMAstatus(DMA* dma,int st);
int getDMA1Status( int st,int posBit );
*/
#endif // __Dma_H__
