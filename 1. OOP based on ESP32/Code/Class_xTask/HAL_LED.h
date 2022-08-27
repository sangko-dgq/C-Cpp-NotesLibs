#ifndef HAL_LED_H
#define HAL_LED_H

#include "Arduino.h"
#include "HAL_Config.h"

class Led
{
  private: //self and friends
    byte _pin;
    uint64_t _taskTime;
    TaskHandle_t _taskHandle;

  public:
    Led(byte pin_param = LED_Default);
    ~Led();

    void setPin(byte pin_param);
    byte getPin() const;
    void setTaskTime(uint64_t taskTime_param = 1000);
    uint64_t getTaskTime();

    void init() const;
    void on() const;
    void off() const;
    void toggle(uint32_t time_dy) const;


    void task();
    static void startTaskImpl(void *_this);
    void startTask();
    void endTask();

};

// extern Led Led_esp, ledGreen(LED_G), ledYellow(LED_Y), ledRed(LED_R);
/*
  extern Led Led_esp;
  extern ledGreen(LED_G), ledYellow(LED_Y), ledRed(LED_R);
*/
extern Led Led_esp, ledGreen, ledYellow, ledRed;

#endif