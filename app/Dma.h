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

#define Peripheral_to_memory  0
#define Memory_to_peripheral  1
#define Memory_to_memory      2




void configureDMA();
void enableDma();
void DMA_memcpy8( uint32_t pDstAddr, uint32_t pSrcAddr, unsigned int uSize );

void clearDMAFlag(DMA* dma,int st,int posBit);
void clearDMAstatus(DMA* dma,int st);
int getDMA1Status( int st,int posBit );
#endif // __Dma_H__