#ifndef _dr_oled_H
#define _dr_oled_H

#include "usart.h"
#include "dma.h"
#include  <string.h>

void USAR_IndefLenUsart_Init(void);
void USAR_UART_IDLECallback(UART_HandleTypeDef *huart);
void USER_UART_IRQHandler(UART_HandleTypeDef *huart);
void Data_Handle(uint8_t *buff,uint8_t size);

extern uint8_t receive_buff[255]; //声明外部变量

#endif


