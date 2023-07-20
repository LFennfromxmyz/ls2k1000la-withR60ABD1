#include "dr_oled.h"
#include "string.h"
#include "main.h"

#include "i2c.h"

#define I2CBUS hi2c1

#define OLED_CMD 0	//д����
#define OLED_DATA 1 //д����

/**
 * @brief д��һ���ֽڡ�
 * @param  dat  Ҫд�������/����
 * @param  cmd  ����/�����־ 0,��ʾ����;1,��ʾ����;
 */
static void OLED_WR_Byte(uint8_t dat, uint8_t cmd)
{
	if (cmd)//д����
	{
		//   OLED_DC_H;
		HAL_I2C_Mem_Write(&I2CBUS, 0x78, 0x40, I2C_MEMADD_SIZE_8BIT, &dat, 1, 0x100);
	}
	else//д����
	{
		// OLED_DC_L;
		HAL_I2C_Mem_Write(&I2CBUS, 0x78, 0x00, I2C_MEMADD_SIZE_8BIT, &dat, 1, 0x100);
	}
}

/**
 * @brief ����OLED��ʾ
 */
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D, OLED_CMD); // SET DCDC����
	OLED_WR_Byte(0X14, OLED_CMD); // DCDC ON
	OLED_WR_Byte(0XAF, OLED_CMD); // DISPLAY ON
}

/**
 * @brief �ر�OLED��ʾ
 */
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D, OLED_CMD); // SET DCDC����
	OLED_WR_Byte(0X10, OLED_CMD); // DCDC OFF
	OLED_WR_Byte(0XAE, OLED_CMD); // DISPLAY OFF
}

/**
 * @brief OLEDȫ����ʾ
 * @param  displaybuf  ������Ҫ��ʾ������
 */
void OLED_Diaplay(char displaybuf[][8])
{
	for (uint8_t i = 0; i < 8; i++)
	{
		OLED_WR_Byte(0xB0 + i, OLED_CMD); //����ҳ��ַ��0~7��
		OLED_WR_Byte(0x00, OLED_CMD);	  //������ʾλ�á��е͵�ַ
		OLED_WR_Byte(0x10, OLED_CMD);	  //������ʾλ�á��иߵ�ַ
		for (uint16_t n = 0; n < 128; n++)
		{
			OLED_WR_Byte(displaybuf[n][i], OLED_DATA);
		}
	}
}
/**
 * @brief OLED��ʼ��
 */
void OLED_Init(void)
{
	OLED_WR_Byte(0xAE, OLED_CMD); //--turn off oled panel
	OLED_WR_Byte(0x00, OLED_CMD); //---set low column address
	OLED_WR_Byte(0x10, OLED_CMD); //---set high column address
	OLED_WR_Byte(0x40, OLED_CMD); //--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0x81, OLED_CMD); //--set contrast control register
	OLED_WR_Byte(0xCF, OLED_CMD); // Set SEG Output Current Brightness
	OLED_WR_Byte(0xA1, OLED_CMD); //--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
	OLED_WR_Byte(0xC8, OLED_CMD); // Set COM/Row Scan Direction   0xc0���·��� 0xc8����
	OLED_WR_Byte(0xA6, OLED_CMD); //--set normal display
	OLED_WR_Byte(0xA8, OLED_CMD); //--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3f, OLED_CMD); //--1/64 duty
	OLED_WR_Byte(0xD3, OLED_CMD); //-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte(0x00, OLED_CMD); //-not offset
	OLED_WR_Byte(0xd5, OLED_CMD); //--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0x80, OLED_CMD); //--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte(0xD9, OLED_CMD); //--set pre-charge period
	OLED_WR_Byte(0xF1, OLED_CMD); // Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_Byte(0xDA, OLED_CMD); //--set com pins hardware configuration
	OLED_WR_Byte(0x12, OLED_CMD);
	OLED_WR_Byte(0xDB, OLED_CMD); //--set vcomh
	OLED_WR_Byte(0x40, OLED_CMD); // Set VCOM Deselect Level
	OLED_WR_Byte(0x20, OLED_CMD); //-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_Byte(0x02, OLED_CMD); //
	OLED_WR_Byte(0x8D, OLED_CMD); //--set Charge Pump enable/disable
	OLED_WR_Byte(0x14, OLED_CMD); //--set(0x10) disable
	OLED_WR_Byte(0xA4, OLED_CMD); // Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte(0xA6, OLED_CMD); // Disable Inverse Display On (0xa6/a7)
	OLED_WR_Byte(0xAF, OLED_CMD); //--turn on oled panel

	OLED_WR_Byte(0xAF, OLED_CMD); /*display ON*/
}
