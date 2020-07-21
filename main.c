#include "stm32l1xx.h"

#define BufferSize 32

uint8_t SPI1_Buffer_Tx[BufferSize] = {
    0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
    0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10,
    0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,
    0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,0x20
};

uint8_t SPI2_Buffer_Tx[BufferSize] = {
    0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,
    0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,0x60,
    0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,
    0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,0x70
};

uint8_t SPI1_Buffer_Rx[BufferSize] = {0xFF};
uint8_t SPI2_Buffer_Rx[BufferSize] = {0xFF};

uint8_t Rx1_Counter = 0;
uint8_t Rx2_Counter = 0;

void SPI_Init(SPI_TypeDef * SPIx);
	
void SPI_Write(SPI_TypeDef * SPIx, uint8_t *buffer, int size);

void SPI_Read(SPI_TypeDef * SPIx, uint8_t *buffer, int size);

void SPIx_IRQHandler(SPI_TypeDef *SPIx, uint8_t *buffer, uint8_t *counter);
void SPI1_IRQHandler(void);
void SPI2_IRQHandler(void);

int main(void){
	  GPIO_Init();
	  NVIC_SetPriority(SPI1_IRQn, 1);         /* Set priority to 1 */
	  NVIC_EnableIRQ(SPI1_IRQn);              /* Enable SPI1 interrupt */
	  NVIC_SetPriority(SPI2_IRQn, 2);         /* Set priority to 2 */
	  NVIC_EnableIRQ(SPI2_IRQn);              /* Enable SPI2 interrupt */
    SPI_Init(SPI1);                         /* Initialize SPI 1 */	
    SPI_Init(SPI2);                         /* Initialize SPI 2 */	
    SPI_Write(SPI1, SPI1_Buffer_Tx, 32);    /* SPI 1 writes data out */	
    SPI_Read(SPI2, SPI2_Buffer_Tx, 32);     /* SPI 2 reads data */	

	  while(1);
}

void SPI_Init(SPI_TypeDef * SPIx){
    if(SPIx == SPI1){                           /* Set SPI1 as master */
		    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;     /* Enable SPI1 clock */
			  RCC->APB2RSTR |= RCC_APB2RSTR_SPI1RST;  /* Reset SPI1 */
			  RCC->APB2RSTR &= ~RCC_APB2RSTR_SPI1RST; /* Clear reset SPI1 */
			  SPIx->CR1 |= SPI_CR1_MSTR;              /* Master selection: 0 = slave, 1 = master */
			  SPIx->CR1 |= SPI_CR1_SSI;               /* Manage slave selection */
		} else if(SPIx == SPI2){                    /* Set SPI2 as slave */
		    RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;     /* Enable SPI2 clock */
			  RCC->APB1RSTR |= RCC_APB1RSTR_SPI2RST;  /* Reset SPI2 */
			  RCC->APB1RSTR &= ~RCC_APB1RSTR_SPI2RST; /* Clear reset SPI2 */
			  SPIx->CR1 &= ~SPI_CR1_MSTR;             /* Master selection: 0 = slave, 1 = master */
			  SPIx->CR1 &= ~SPI_CR1_SSI;              /* Manage slave selection */			
			
		}
		SPIx->CR1 &= ~SPI_CR1_RXONLY;               /* Configure duplex or receive only: 0 = full-duplex */
		SPIx->CR1 &= ~SPI_CR1_DFF;                  /* frame size = 8bits */
		
		
		
		SPIx->CR1 |= SPI_CR1_BIDIOE;                /* Output enable bidirectional mode */
		SPIx->CR2 |= SPI_CR2_RXNEIE;                /* Enable RX buffer not empty interrupt */
		SPIx->CR2 |= SPI_CR2_ERRIE;                 /* Enable error interrupt */
		SPIx->CR1 |= SPI_CR1_SPE;                   /* Enable SPI */
}

void SPI_Write(SPI_TypeDef * SPIx, uint8_t *buffer, int size){
    int i = 0;
	
	  for(i = 0; i < size; i++){
		    while(!(SPIx->SR & SPI_SR_TXE));    /* Wait for TXE (transmit buffer empty) */
			      SPIx->DR = buffer[i];
		}
		while(SPIx->SR & SPI_SR_BSY);           /* Wait until SPI is not busy */
}

void SPI_Read(SPI_TypeDef * SPIx, uint8_t *buffer, int size){
    int i = 0;
	
	  for(i = 0; i < size; i++){
		    while(!(SPIx->SR & SPI_SR_TXE));    /* Wait for TXE (transmit buffer empty) */
			      SPIx->DR = buffer[i];
						while(!(SPI1->SR & SPI_SR_TXE)); /* Wait for TXE */
			          SPI1->DR = 0xFF;						/* Dummy byte */
		}
		while(SPI1->SR & SPI_SR_BSY);           /* Wait until SPI is not busy */
}

void SPIx_IRQHandler(SPI_TypeDef *SPIx, uint8_t *buffer, uint8_t *counter){
	  if(SPIx->SR & SPI_SR_RXNE){             /* if SPI receive register is not empty */
			  buffer[*counter] = SPIx->DR;        /* Reading SPI_DR automatically clears RXNE flag */
			  (*counter)++;
		    if((*counter) >= BufferSize)
				    (*counter) = 0;
		}
}

void SPI1_IRQHandler(void){
    SPIx_IRQHandler(SPI1, SPI1_Buffer_Rx, & Rx1_Counter);
}

void SPI2_IRQHandler(void){
    SPIx_IRQHandler(SPI2, SPI2_Buffer_Rx, & Rx2_Counter);
}
