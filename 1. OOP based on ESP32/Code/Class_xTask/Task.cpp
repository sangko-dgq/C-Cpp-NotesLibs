

#include "Task.h"
#include "HAL_LED.h"

void taskInit()
{
  ledGreen.startTask();
  ledYellow.startTask();
  ledRed.startTask();

}



