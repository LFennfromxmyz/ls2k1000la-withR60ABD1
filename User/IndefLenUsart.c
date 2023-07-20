#include "IndefLenUsart.h"

#include "datahandle.h"
/*
在stm32f1xx.it.c中:
        void USART2_IRQHandler(void)
        {
            HAL_UART_IRQHandler(&huart2);
            USER_UART_IRQHandler(&huart2);// ++
        }


*/
/******************************用户配置**********************************/

#define hdma_usartx_rx hdma_usart2_rx
#define IndefLenUsart huart2
#define IndefLenUsartName USART2

#define DEBUG huart1
/**************************************************************************/
uint8_t receive_buff[255];
extern DMA_HandleTypeDef hdma_usartx_rx;

//初始化不定长数据接口
void USAR_IndefLenUsart_Init(void)
{
    __HAL_UART_ENABLE_IT(&IndefLenUsart, UART_IT_IDLE);
    HAL_UART_Receive_DMA(&IndefLenUsart, (uint8_t *)receive_buff, 255); //设置DMA传输，将串口的数据搬运到recvive_buff中，每次255个字节
}
//
void USER_UART_IRQHandler(UART_HandleTypeDef *huart)
{
    if (huart->Instance == IndefLenUsartName) //判断是否是串口
    {
        if (RESET != __HAL_UART_GET_FLAG(&IndefLenUsart, UART_FLAG_IDLE)) //判断是否是空闲中断
        {
            __HAL_UART_CLEAR_IDLEFLAG(&IndefLenUsart); //清除空闲中断标志（否则会一直不断进入中断）
            USAR_UART_IDLECallback(huart);             //调用中断处理函数
        }
    }
}

void USAR_UART_IDLECallback(UART_HandleTypeDef *huart)
{
    HAL_UART_DMAStop(&IndefLenUsart); //停止本次DMA传输

    uint8_t data_length = BUFFER_SIZE - __HAL_DMA_GET_COUNTER(&hdma_usartx_rx); //计算接收到的数据长度

    Data_Handle(receive_buff, data_length);

    memset(receive_buff, 0, data_length); //清零接收缓冲区
    data_length = 0;
    HAL_UART_Receive_DMA(&IndefLenUsart, (uint8_t *)receive_buff, 255); //重启开始DMA传输 每次255字节
}

void Data_Handle(uint8_t *buff, uint8_t size)
{
    uint8_t rx_buff[255] = {0};
    memcpy(rx_buff, buff, size);

    //HAL_UART_Transmit(&huart1, rx_buff, size, 0x200); //测试函数：将接收到的数据打印出去

    ProcessRx(rx_buff,size);
}
