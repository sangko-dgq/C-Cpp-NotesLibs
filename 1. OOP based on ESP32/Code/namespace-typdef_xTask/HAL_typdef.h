
#ifndef HAL_TYDEF_H
#define HAL_TYPE_H

#include <stdint.h>
#include "Arduino.h"
#include "HAL_Config.h"

namespace HAL
{
/*LED*/
typedef struct
{
  byte _pin;
  uint64_t _taskTime;
  TaskHandle_t _taskHandle;
} LED_Info_t;

}


















#endif