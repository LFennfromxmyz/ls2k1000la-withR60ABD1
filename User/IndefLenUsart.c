#include "IndefLenUsart.h"

#include "datahandle.h"
/*
��stm32f1xx.it.c��:
        void USART2_IRQHandler(void)
        {
            HAL_UART_IRQHandler(&huart2);
            USER_UART_IRQHandler(&huart2);// ++
        }


*/
/******************************�û�����**********************************/

#define hdma_usartx_rx hdma_usart2_rx
#define IndefLenUsart huart2
#define IndefLenUsartName USART2

#define DEBUG huart1
/**************************************************************************/
uint8_t receive_buff[255];
extern DMA_HandleTypeDef hdma_usartx_rx;

//��ʼ�����������ݽӿ�
void USAR_IndefLenUsart_Init(void)
{
    __HAL_UART_ENABLE_IT(&IndefLenUsart, UART_IT_IDLE);
    HAL_UART_Receive_DMA(&IndefLenUsart, (uint8_t *)receive_buff, 255); //����DMA���䣬�����ڵ����ݰ��˵�recvive_buff�У�ÿ��255���ֽ�
}
//
void USER_UART_IRQHandler(UART_HandleTypeDef *huart)
{
    if (huart->Instance == IndefLenUsartName) //�ж��Ƿ��Ǵ���
    {
        if (RESET != __HAL_UART_GET_FLAG(&IndefLenUsart, UART_FLAG_IDLE)) //�ж��Ƿ��ǿ����ж�
        {
            __HAL_UART_CLEAR_IDLEFLAG(&IndefLenUsart); //��������жϱ�־�������һֱ���Ͻ����жϣ�
            USAR_UART_IDLECallback(huart);             //�����жϴ�����
        }
    }
}

void USAR_UART_IDLECallback(UART_HandleTypeDef *huart)
{
    HAL_UART_DMAStop(&IndefLenUsart); //ֹͣ����DMA����

    uint8_t data_length = BUFFER_SIZE - __HAL_DMA_GET_COUNTER(&hdma_usartx_rx); //������յ������ݳ���

    Data_Handle(receive_buff, data_length);

    memset(receive_buff, 0, data_length); //������ջ�����
    data_length = 0;
    HAL_UART_Receive_DMA(&IndefLenUsart, (uint8_t *)receive_buff, 255); //������ʼDMA���� ÿ��255�ֽ�
}

void Data_Handle(uint8_t *buff, uint8_t size)
{
    uint8_t rx_buff[255] = {0};
    memcpy(rx_buff, buff, size);

    //HAL_UART_Transmit(&huart1, rx_buff, size, 0x200); //���Ժ����������յ������ݴ�ӡ��ȥ

    ProcessRx(rx_buff,size);
}
