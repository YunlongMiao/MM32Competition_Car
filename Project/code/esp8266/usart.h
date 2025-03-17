#ifndef __USART_H
#define __USART_H 			   

#include "stm32f10x.h"
#include "stdio.h"

void uart2_Init(u32 bound);
void uart3_Init(u32 bound);
void USART2_IRQHandler(void);
void USART3_IRQHandler(void);

#endif
