

OOP - encapsulation / Abstraction
封装/抽象

/*
  面向对象点灯
  1. private member add _X
  2. 利用set/get方法对内部私有成员访问。
  3. 常量函数 void XX() const;只读/没有任何写操作
  4. 源文件/实现文件  头文件/接口文件
  
  构造函数与析构函数 constructor/deconstructor
  构造
  1. ClassA objA;  为objA变量对象分配了空间 + 运行了ClassA的构造函数。
  2. 构造函数里进行: 对该类的成员变量初始化。(默认值)
     防止没有传值，变量报错。
     
    默认构造的两种初始化写法：:
     Led::Led()
    {
      _pin = 2;
    }

     Led::Led() : _pin(2)
    {

    }
    重载构造的两种初始化写法：:
    Led::Led(byte pin_param)
    {
      _pin = pin_param;
    }
     Led::Led(byte pin_param) 
         :_pin(pin_param)
    {
        
    }
  
  3. 默认(缺省)构造函数 / 重载构造函数（含参数的构造函数）
    默认(缺省)构造函数
      .h:
      Led();
    .cpp:
      Led::Led()
      {
           
      }
    使用：
    Led led01; 

  参数一致
     .h:
      Led(byte pin_param, string color_param);
    .cpp:
      Led::Led(byte pin_param, string color_param)
      {
           
      }
    使用：
    Led led01(27); // X
    Led led01(27, "Green"); // V

  含参数有默认值
    .h:
      Led(byte pin_param, string color_param = "Green");
    .cpp:
      Led::Led(byte pin_param, string color_param = "Green")
      {
           
      }
    使用：
    Led led01(27); // V
    Led led01(27, "Green"); // V
      
    类型不一样 / 参数不一样，可以实现一个类具有多个构造函数。
    
    重载构造函数的参数有默认值的情况下，只需在声明出写明。
    // X 错误写法: 
    Led(byte pin_param = LED_Default); //.h
    Led::Led(byte pin_param = LED_Default)  //.cpp
    {

    }

    // V 正确写法
    Led(byte pin_param = LED_Default); //.h
    Led::Led(byte pin_param)  //.cpp
    {

    }
    
    析构
    1. 比如：局部变量在一个函数执行完后会自动销毁,释放内存。
    2. 常用于： 比如:SD文件系统中,在构造中打开SD文件,析构中关闭不再使用的文件。

    

    多任务点灯：


源代码：
    void Led::task_ledGreen(void *p)
    {
        while(1)
        {
       ledGreen.toggle(0);
       vTaskDelay(1000);
      }
    }
void Led::task_ledYellow(void *p)
    {
    while(1)
    {
       task_ledYellow.toggle(0);
       vTaskDelay(1000);
    }
    }

    xTaskCreate(Led::task_ledGreen, "task_ledGreen", 1024, NULL, 1, NULL);
    
    代码改进：
    利用指针作为参数，创建某个任务模板。所有对象直接传入地址使用。
    /*LED闪烁任务*/
    void led_shine_task(void *p)
    {
      // *p  ->  *Led
      Led led = *(Led *)p;
      while (1)
      {
        led.toggle(0);
        vTaskDelay(led.getTaskTime());
      }
    }
    /*绿黄红灯-闪烁任务*/
    xTaskCreate(led_shine_task, "task_ledGreen", 1024, &ledGreen, 1, NULL);
    xTaskCreate(led_shine_task, "task_ledYellow", 1024, &ledYellow, 1, NULL);
    xTaskCreate(led_shine_task, "task_ledRed", 1024, &ledRed, 1, NULL);

    继续改进：
    将freertos隐藏在类的成员方法里面. 并且利用任务句柄关闭任务 TaskHandle_t
.h:
class Led
{
    private:
    ...
    TaskHandle_t _taskHandle;
    ...

    public:
    ...
    void task(); //任务本体
    static void startTaskImpl(void *_this); //类型转换
    void startTask();//开始
    void endTask();//终止

}
 .cpp:   
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

   注意: 执行任务的对象必须为全局变量，防止析构销毁对象，而任务是会不断执行的。(比如不能在setup函数里面实例会绑定全局任务的Led)

    extern用法:
    extern处不用跟赋值。否则会报错
    源处：
    Led Led_esp, ledGreen(LED_G), ledYellow(LED_Y), ledRed(LED_R);
    Extern处:
    /*
    错误写法1: 
      extern Led Led_esp, ledGreen(LED_G), ledYellow(LED_Y), ledRed(LED_R);
    错误写法2:
    extern Led Led_esp;
      extern ledGreen(LED_G), ledYellow(LED_Y), ledRed(LED_R);
    */
    正确写法:
      extern Led Led_esp, ledGreen, ledYellow, ledRed;


*/