

### **extern 处不用跟赋值。否则会报错**

源处：

```c++
Led Led_esp, ledGreen(LED_G), ledYellow(LED_Y), ledRed(LED_R);
```

Extern处:
/*
错误写法1: 
  extern Led Led_esp, ledGreen(LED_G), ledYellow(LED_Y), ledRed(LED_R);
错误写法2:
extern Led Led_esp;
extern ledGreen(LED_G), ledYellow(LED_Y), ledRed(LED_R);
*/
正确写法:

```c++
  extern Led Led_esp, ledGreen, ledYellow, ledRed;
```

