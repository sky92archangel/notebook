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













