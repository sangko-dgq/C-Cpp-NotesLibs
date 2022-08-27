#include "HAL_LED.h"



Led::Led(byte pin_param)
{
  this->setPin(pin_param);
}
Led::~Led()
{

}

void Led::setPin(byte pin_param)
{

  if ((pin_param < 40) && (pin_param >= 0))
  {
    _pin = pin_param;
    pinMode(_pin, OUTPUT);
  }
  else Serial.println("invalid pin number");
}



byte Led::getPin() const
{
  return _pin;
}

void Led::setTaskTime(uint64_t taskTime_param)
{
  _taskTime = taskTime_param;
}
uint64_t Led::getTaskTime()
{
  return _taskTime;
}



void Led::on() const
{
  digitalWrite(_pin, HIGH);
}

void Led::off() const
{
  digitalWrite(_pin, LOW);
}

void Led::toggle(uint32_t time_dy) const
{
  digitalWrite(_pin, !digitalRead(_pin));
  delay(time_dy);
}


/*OUT*/
Led Led_esp, ledGreen(LED_G), ledYellow(LED_Y), ledRed(LED_R);
void Led::init() const
{

  ledGreen.setTaskTime(1000);
  ledYellow.setTaskTime(500);
  ledRed.setTaskTime(100);

  Led_esp.on();
  //on
  ledGreen.on();
  ledYellow.on();
  ledRed.on();
  delay(1000);

  //off
  ledGreen.off();
  ledYellow.off();
  ledRed.off();
  delay(1000);

  Serial.println("The Led Class used : " + String(sizeof(ledGreen)) + "Bytes");
}

/*****************************TASK

  /*任务本体*/
void Led::task()
{
  while (1)
  {
    this->toggle(0);
    // vTaskDelay(this->getTaskTime());
    vTaskDelay(this->_taskTime);  //属于Led类。自己允许访问私有
  }
}
/*类型转换*/
void Led::startTaskImpl(void *_this)
{
  /* this =>  Led* */
  static_cast<Led*>(_this) -> task();
}
/*任务开关*/
void Led::startTask()
{
  xTaskCreate(this->startTaskImpl, "led_task", 2048, this, 5, &_taskHandle);
}
void Led::endTask()
{
  this->off();
  vTaskDelete(_taskHandle);
}