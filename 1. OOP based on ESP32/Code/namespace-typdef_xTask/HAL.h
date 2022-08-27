#ifndef HAL_H
#define HAL_H

#include "Arduino.h"
#include "HAL_Config.h"
#include "HAL_typdef.h"
extern HAL::LED_Info_t ledinfo_Default, ledinfo_G, ledinfo_Y, ledinfo_R;
namespace HAL
{

void Init();
void Update();

void setPin(LED_Info_t *LED_Info_t_param, byte pin_param);
byte getPin(LED_Info_t *LED_Info_t_param);
void setTaskTime(LED_Info_t *LED_Info_t_param, uint64_t taskTime_param);
uint64_t getTaskTime(LED_Info_t *LED_Info_t_param);
void on(LED_Info_t *LED_Info_t_param);
void off(LED_Info_t *LED_Info_t_param);
void toggle(LED_Info_t *LED_Info_t_param, uint32_t time_dy);
void ledInit();

void task(void *argument);
void task2(void *argument);
void task3(void *argument);

void startTask(LED_Info_t *LED_Info_t_param);
void endTask(LED_Info_t *LED_Info_t_param);
}



#endif



