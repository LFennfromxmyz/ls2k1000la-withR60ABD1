#ifndef _dr_key_H
#define _dr_key_H

void Key_Init(void);
long Get_Key(uint8_t *ucQueueMsgValue, uint32_t xMaxBlockTime);
void button_ticks(void);
#endif
