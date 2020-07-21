#include "stm32l1xx.h"
#define BufferSize 32

uint8_t SPI1_Buffer_Tx[BufferSize] = {};
uint8_t SPI2_Buffer_Tx[BufferSize] = {};
	
void f()
{
}

void g()
{
    f();
}

void SPI_Init(SPI_TypeDef * SPIx);
	
void SPI_Write(SPI_TypeDef * SPIx, uint8_t *buffer, int size);

void SPI_Read(SPI_TypeDef * SPIx, uint8_t *buffer, int size);

int main(void){
	  GPIO_Init();
	
    SPI_Init(SPI1);                         /* Initialize SPI 1 */	
    SPI_Init(SPI2);                         /* Initialize SPI 2 */	
    SPI_Write(SPI1, SPI1_Buffer_Tx, 32);    /* SPI 1 writes data out */	
    SPI_Read(SPI2, SPI2_Buffer_Tx, 32);     /* SPI 2 reads data */	
    g();
	while(1);
}

void SPI_Init(SPI_TypeDef * SPIx){}

void SPI_Write(SPI_TypeDef * SPIx, uint8_t *buffer, int size){
    int i = 0;
	
	  for(i = 0; i < size; i++){
		    while(!(SPIx->SR & SPI_SR_TXE));    /* Wait for TXE (transmit buffer empty) */
			      SPIx->DR = buffer[i];
		}
		while(SPIx->SR & SPI_SR_BSY);           /* Wait for not busy */
}

void SPI_Read(SPI_TypeDef * SPIx, uint8_t *buffer, int size){
    int i = 0;
	
	  for(i = 0; i < size; i++){
		    while(!(SPIx->SR & SPI_SR_TXE));    /* Wait for TXE (transmit buffer empty) */
			      SPIx->DR = buffer[i];
		}
		while(SPIx->SR & SPI_SR_BSY);           /* Wait for not busy */
}

