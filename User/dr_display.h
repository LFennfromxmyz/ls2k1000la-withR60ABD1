#ifndef _display_dr_H
#define _display_dr_H

#include "main.h"

typedef struct //���߲���
{
	float Draw_Buf[128];//�������ݻ���
	float Draw_Min;//�������ݵ���Сֵ  ��λΪ�ٷֱ�
	float Draw_Max;	//�������ݵ����ֵ
}_DrawCurve;//���߲���


//�ַ�ת��,����ȫ�ֵ���
extern char  LCD_CACHE[50];
//��ʾ����ʼ��
void DisplayInit(void);
//��ʾ��ˢ����ʾ
void DisplayRefresh(void) ;
//����
void Oled_Draw_Point(uint8_t x,uint8_t y);
//��ʾ�ַ���
void Oled_Disp_String(uint8_t x,uint8_t y,char const  *text);
//����
void Interfacr_Shadow(uint8_t x,uint8_t y,uint8_t kuan,uint8_t gao);
//�������
void Clear_Disp(uint8_t x,uint8_t y,uint8_t kuan,uint8_t gao);
//���������ʾ�ַ����ı�־λ
void OledScrollClear(void);
//������ʾ�ַ���
void OledScrollDisplay(uint8_t x,uint8_t y,char* str,uint8_t len);
//��ʾ��������
void OledDisplayBootScreen(void);
//������������
void WriteCurveData(_DrawCurve *Draw,float val);
//��ӡ����
void OledDrawCurve(_DrawCurve Draw,uint8_t fllor,uint8_t upper);
//����
void Display_Line(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2);
//���ƾ���
void Display_REC(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2);
//����ʵ�ľ���
void Display_REC_Solid(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2);
//������ʾ�ַ���
void OledCenteredDisplayStr(uint8_t x,uint8_t y ,uint8_t length,const char *str);
#endif

