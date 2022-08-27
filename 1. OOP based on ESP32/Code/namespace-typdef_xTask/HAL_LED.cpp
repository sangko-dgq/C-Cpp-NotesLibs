#include "HAL.h"

HAL::LED_Info_t ledinfo_Default, ledinfo_G, ledinfo_Y, ledinfo_R;

void HAL::setPin(LED_Info_t *LED_Info_t_param, byte pin_param)
{

  if ((pin_param < 40) && (pin_param >= 0))
  {
    LED_Info_t_param->_pin = pin_param;
    pinMode(LED_Info_t_param->_pin, OUTPUT);

    Serial.printf("[setPin]%d\r\n", LED_Info_t_param->_pin);
  }
  else Serial.println("invalid pin number");
}

byte HAL::getPin(LED_Info_t *LED_Info_t_param)
{
  return LED_Info_t_param->_pin;
}

void HAL::setTaskTime(LED_Info_t *LED_Info_t_param, uint64_t taskTime_param)
{
  LED_Info_t_param->_taskTime = taskTime_param;
}
uint64_t HAL::getTaskTime(LED_Info_t *LED_Info_t_param)
{
  return LED_Info_t_param->_taskTime;
}


void HAL::on(LED_Info_t *LED_Info_t_param)
{
  digitalWrite(LED_Info_t_param->_pin, HIGH);
}

void HAL::off(LED_Info_t *LED_Info_t_param)
{
  digitalWrite(LED_Info_t_param->_pin, LOW);
}

void HAL::toggle(LED_Info_t *LED_Info_t_param, uint32_t time_dy)
{
  on(LED_Info_t_param);
  delay(time_dy);
  off(LED_Info_t_param);
  delay(time_dy);
}




void HAL::ledInit()
{

  setPin(&ledinfo_Default, LED_Default);
  setPin(&ledinfo_G, LED_G);
  setPin(&ledinfo_Y, LED_Y);
  setPin(&ledinfo_R, LED_R);

  setTaskTime(&ledinfo_G, 1000);
  setTaskTime(&ledinfo_Y, 500);
  setTaskTime(&ledinfo_R, 100);

  on(&ledinfo_Default);
  on(&ledinfo_G);
  on(&ledinfo_Y);
  on(&ledinfo_R);

  Serial.printf("[ledInit]%d\r\n", ledinfo_G._pin);
  Serial.println("The Led Class used : " + String(sizeof(LED_Info_t)) + "Bytes");
}

/*****************************TASK
  /*任务本体*/
void HAL::task(void* argument)  //"void* argument" must
{
  while (1)
  {
    toggle(&ledinfo_G, 10);
    // Serial.printf("[task]%d\r\n", getPin(&ledinfo_G));
    vTaskDelay(100);
  }
}
void HAL::task2(void* argument)  //"void* argument" must
{
  while (1)
  {
    toggle(&ledinfo_Y, 100);
    // Serial.printf("[task]%d\r\n", getPin(&ledinfo_G));
    vTaskDelay(100);
  }
}

void HAL::task3(void* argument)  //"void* argument" must
{
  while (1)
  {
    toggle(&ledinfo_R, 500);
    // Serial.printf("[task]%d\r\n", getPin(&ledinfo_G));
    vTaskDelay(100);
  }
}


void HAL::startTask(LED_Info_t *LED_Info_t_param)
{
  xTaskCreate(task, "led_task", 1024, NULL, 2, &LED_Info_t_param->_taskHandle);
  xTaskCreate(task2, "led_task", 1024, NULL, 2, &LED_Info_t_param->_taskHandle);
  xTaskCreate(task3, "led_task", 1024, NULL, 2, &LED_Info_t_param->_taskHandle);


  //ERROR :  &(LED_Info_t_param->_taskHandle)
  //Right：  &LED_Info_t_param->_taskHandle
}
void HAL::endTask(LED_Info_t *LED_Info_t_param)
{
  off(LED_Info_t_param);
  vTaskDelete(LED_Info_t_param->_taskHandle);
}

