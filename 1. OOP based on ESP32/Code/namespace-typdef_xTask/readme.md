

## **namespace + typedef + xTask 搭配**

### namespace + typedef

```c++
namespace HAL
{
    typedef struct
    {
          byte _pin;
          uint64_t _taskTime;
          TaskHandle_t _taskHandle;
     } LED_Info_t;
}
```

### 结构体指针类型

**错误写法**: **LED_Info_t** 导致结构体变量无法全局保存值

```c++
/* 声明 */
namespace HAL
{
    void setPin(LED_Info_t LED_Info_t_param, byte pin_param);  
}

/* 实现 */
void HAL::setPin(LED_Info_t LED_Info_t_param, byte pin_param) 
{
   LED_Info_t_param._pin = pin_param;
   pinMode(LED_Info_t_param._pin, OUTPUT);
}
void HAL::ledInit(LED_Info_t LED_Info_t_param)
{
   Serial.printf(LED_Info_t_param._pin);
}

/*使用*/
LED_Info_t led_info_green;
void HAL::ledInit()
{
   setPin(led_info_green,33);
   Serial.printf(led_info_green._pin);  // 始终为默认的0
}
```

**正确写法:** **LED_Info_t*** 参数类型全部采用结构体指针

```c++
/* 声明 */
namespace HAL
{
    void setPin(LED_Info_t* LED_Info_t_param, byte pin_param);  
}
/* 实现 */
void HAL::setPin(LED_Info_t* LED_Info_t_param, byte pin_param) //HAL.cpp
{
   LED_Info_t_param->_pin = pin_param;
   pinMode(LED_Info_t_param->_pin, OUTPUT);
}
void HAL::ledInit(LED_Info_t *LED_Info_t_param)
{
   Serial.printf(LED_Info_t_param->_pin);
}
/*使用*/
LED_Info_t led_info_green;
void HAL::ledInit()
{
   setPin(&led_info_green,33);
   Serial.printf(led_info_green._pin);  
}
```

### 任务创建方式类似