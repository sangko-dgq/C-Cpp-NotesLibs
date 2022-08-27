/* 孤独的二进制
   面向对象点灯
*/
#include "Arduino.h"
#include "HAL_LED.h"
#include "Task.h"

Led *led_gobal;

void setup()
{
  Serial.begin(Serial_Debug_Baud);

  led_gobal->init();

  taskInit();
}

void loop()
{

}

