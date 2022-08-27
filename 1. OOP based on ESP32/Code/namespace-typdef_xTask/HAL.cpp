

#include "HAL.h"
#include "Task.h"

void HAL::Init()
{
  ledInit();

  Serial.printf("[Init]%d\r\n", ledinfo_G._pin);
  taskInit();
}
void HAL::Update()
{

}