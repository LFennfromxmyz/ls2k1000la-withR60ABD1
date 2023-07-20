#include "dr_button.h"
#include "dr_key.h"

#include "debug.h"

static uint8_t key_num = 0;

static Button key3;	
static Button key4; 


static uint8_t ReadKey3(void)
{
	if (!HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin))
		return 0;
	else
		return 1;
}

static void Key3_PRESS_DOWN_Handler(void *btn, uint8_t event)
{
	if (event & SINGLE_CLICK)
	{
		key_num = 3;
		printf("key_num3:%d\r\n", key_num);
	}
}

static uint8_t ReadKey4(void)
{
	if (!HAL_GPIO_ReadPin(KEY4_GPIO_Port,KEY4_Pin))
		return 0;
	else
		return 1;
}

static void Key4_PRESS_DOWN_Handler(void *btn, uint8_t event)
{
	if (event & SINGLE_CLICK)
	{
		key_num = 4;
		printf("key_num4:%d\r\n", key_num);
	}
}

/**
 * @brief 按键初始化,必须放在操作系统任务中
 */
void Key_Init(void)
{
	button_init();
	
	/* 注册按键 */

	button_attach(&key3, ReadKey3, Key3_PRESS_DOWN_Handler, SINGLE_CLICK);
	button_attach(&key4, ReadKey4, Key4_PRESS_DOWN_Handler, SINGLE_CLICK);
}

