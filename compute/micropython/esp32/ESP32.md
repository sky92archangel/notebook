# MICROPYTHON 操作 ESP32 单片机

[TOC]

## 一、LED

点亮一个LED

```python
import time 
from machine import Pin

pin_led = Pin(12,Pin.OUT)

pin_led.on()
#pin_led.value(1)
```

LED闪烁

```python
import time 
from machine import Pin

pin_led = Pin(12,Pin.OUT)

while 1:
    pin_led.on()
    time.sleep(1)
    pin_led.off()
    time.sleep(1)
 
```

流水灯

```python
import time 
from machine import Pin
 

pin_lst = [17,18,19]

led_lst= []

for pin in  pin_lst:
    led_lst.append(Pin(pin,Pin.OUT))

for led in led_lst:
    led.off()

while 1:
    for led in led_lst:
        led.on()
        time.sleep(0.2)
        led.off()
        time.sleep(0.2)
 
```

## 二、数码显像管



```python
import time 
from machine import Pin

a = Pin(0,Pin.OUT)
b = Pin(2,Pin.OUT)
c = Pin(4,Pin.OUT)
d = Pin(5,Pin.OUT)
e = Pin(12,Pin.OUT)
f = Pin(14,Pin.OUT)
g = Pin(26,Pin.OUT)
dp = Pin(33,Pin.OUT)

led_lst=[a,b,c,d,e,f,g,dp]
  
for led in led_lst:
    time.sleep(.2)
    led.off()
   

num_dict = {
    # [a,b,c,d,e,f,g,dp]
    0:[1,1,1,1,1,1,0,0],
    1:[0,1,1,0,0,0,0,0],
    2:[1,1,0,1,1,0,1,0],
    3:[1,1,1,1,0,0,1,0],
    4:[0,1,1,0,0,1,1,0],
    5:[1,0,1,1,0,1,1,0],

}
num=3
logic_lst =num_dict.get(num) 
print(logic_lst)
for i in range(len(logic_lst)):
    led_lst[i].value(not logic_lst[i])
 
```





## 脉宽调制 

### PWM呼吸灯

采用方波0V电压周期占空比调整平均输出电压，达到利用比例控制输出电压的手段：

```python
from machine import Pin,PWM
import time
#定义输出口
led_pin =Pin(12,Pin.OUT) 
#建立脉宽调制
led =PWM(led_pin,freq=1000)
# duty 占空比范围1-1023
#duty_u16 范围 0-65535
#duty_ns 为纳秒单位脉冲宽度 范围 0-50000
limit = 1024
#
while 1:
    for i in range(limit):
        led.duty(i)
        time.sleep_ms(1)
    for i in range(limit-1,0,-1):
        led.duty(i)
        time.sleep_ms(1)
```



舵机

```python
from machine import Pin,PWM
import time

#标准PWM信号周期固定为20ms
# 0.5ms = 00 度= 0.5//20
# 1.0ms = 45 度= 1.0//20
# 1.5ms = 90 度= 1.5//20
# 2.0ms = 135 度= 2.0//20
# 2.5ms = 180 度= 2.5//20


pwm_pin = Pin(4,Pin.OUT)

servo_pwm =PWM(pwm_pin )
servo_pwm.freq(50)

servo_pwm.duty(int(1023*0.5/20))

while 1:  
    servo_pwm.duty(int(1023*1.0/20))
    time.sleep(1)
    servo_pwm.duty(int(1023*2.0/20))
    time.sleep(1)

 

```







