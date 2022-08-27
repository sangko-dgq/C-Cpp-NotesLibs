

#include "Task.h"
#include "HAL.h"



void HAL::taskInit()
{

  HAL::startTask(&ledinfo_Default);
  HAL::startTask(&ledinfo_G);
  HAL::startTask(&ledinfo_Y);
  HAL::startTask(&ledinfo_R);


}



