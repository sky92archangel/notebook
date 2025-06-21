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

单位数码管输出

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

单位数码管输出，打包为类 区分共阳极和共阴极

```python
import time 
from machine import Pin


'''
数码管公共类
共阳极（Common Anode）
共阴极（Common Cathode）
'''

class Seg :
    def __init__(self,
                    pin_idxs:list=[0,2,4,5,12,14,26,33],
                    is_anode=True):
        self.is_anode = is_anode
        self.led_lst=[ ]
        for pin_idx in pin_idxs :
            led = Pin(pin_idx,Pin.OUT)
            self.led_lst.append(led) 
        
        self.num_dict = {
            # [a,b,c,d,e,f,g,dp]
            0:[1,1,1,1,1,1,0,0],
            1:[0,1,1,0,0,0,0,0],
            2:[1,1,0,1,1,0,1,0],
            3:[1,1,1,1,0,0,1,0],
            4:[0,1,1,0,0,1,1,0],
            5:[1,0,1,1,0,1,1,0], 
        }
         
   
    def clear_led(self):         
        for led in self.led_lst:
            time.sleep(.01)
            if self.is_anode:
                led.off()
            else:
                led.on()

    def show_num(self,num:int):
        logic_lst =self.num_dict.get(num) 
        print(f"logic_lst:{logic_lst}")

        for i in range(len(logic_lst)):
            logic_item = logic_lst[i]
            if self.is_anode:
                logic_item = not logic_lst[i] 
            self.led_lst[i].value(logic_item)
        

seg = Seg(pin_idxs= [0,2,4,5,12,14,26,33])
seg.clear_led()
seg.show_num(num=5)
```





## GPIO

按键输入

```python
import time 
from machine import Pin

#默认按钮接电源，一侧为高电平，所以给14端口一个低电平
pin_button = Pin(14,Pin.IN,Pin.PULL_DOWN)

pin_led=Pin(0,Pin.OUT)

#设置状态 避免长按重复判断
status = 0
while 1:
    if pin_button.value()==1:
        time.sleep_ms(80)
		#案件消抖检测
        if pin_button.value()==1 and status == 0:
            pin_led.value(not pin_led.value())
            status=1
        elif pin_button.value()==0:
            status=0

```

以后采用中断实现消抖检测





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

ADC 模式转换

```python
import time 
from machine import Pin,PWM,ADC


# 测试ADC是否可用
def adc_test ():

    adc =ADC(Pin(14))

    val = adc.read()#12位 0-4096
    val_u16=adc.read_u16()#真实 0-65536

    adc.atten(ADC.ATTN_11DB)

    while 1:
        print(f"adc:{adc.read()}")
        print(f"adc-u16:{adc.read_u16()}")
        time.sleep(0.2)

# ADC控制 获得ADC值 用于脉宽调制平均电压 控制LED亮度
def pwn_adc_led():  
    led =PWM(Pin(0) ,freq=1000)
    adc = ADC(Pin(14),atten=ADC.ATTN_11DB)

    while 1:
        # adc.read_u16()
        led.duty_u16(adc.read_u16())
        time.sleep(0.1)
        print(f"adc-u16:{adc.read_u16()}")

pwn_adc_led()
```



OLED显示

```python
from machine import Pin, I2C
import ssd1306

# ESP32 Pin assignment 
i2c = I2C(0, scl=Pin(22), sda=Pin(21))

oled_width = 128
oled_height = 64
oled = ssd1306.SSD1306_I2C(oled_width, oled_height, i2c)

oled.text('Hello, Wokwi!', 10, 10)      
oled.show()

```



## 中断

外部中断消抖

```python
import time 
from machine import Pin

button = Pin(12,Pin.IN,Pin.PULL_DOWN)
led=Pin(21,Pin.OUT)
 
def button_handler(button):
    # status=0
    time.sleep_ms(20)
    if button.value()==1  :
        led.value(not led.value()) 

        #IRQ_RISING 为上升沿触发
# button.irq (handler,trigger) 
button.irq (button_handler,Pin.IRQ_RISING)

 
```

定时器中断

```python
import time 
from machine import Pin,Timer
 


def timer_test():

    def timer_0_irq (timer_obj):
        print(0) 
    timer_0=Timer(0)
    timer_0.init( mode=Timer.PERIODIC,
                period=500,
                callback=timer_0_irq)
    
    def timer_1_irq (timer_obj):
        print(1) 
    timer_1=Timer(1)
    timer_1.init( mode=Timer.PERIODIC,
                period=100,
                callback=timer_1_irq)
     
    def timer_2_irq (timer_obj):
        print(2)
    timer_2=Timer(2)
    timer_2.init( mode=Timer.PERIODIC,
                period=1000,
                callback=timer_2_irq)
    
    def timer_3_irq (timer_obj):
        print(3)
    timer_3=Timer(3)
    timer_3.init( mode=Timer.PERIODIC,
                period=500,
                callback=timer_3_irq)



def timer_demo() :
    led_1=Pin(21,Pin.OUT)
    led_2=Pin(16,Pin.OUT)

    def timer_0_irq (timer_obj):
        led_1.value(not led_1.value())
    timer_0=Timer(0)
    timer_0.init( mode=Timer.PERIODIC,
                period=500,
                callback=timer_0_irq)
    while 1:
        time.sleep_ms(100)
        led_2.value(not led_2.value())

timer_demo()
```



## 网络

WIFI

```python
import time 
from machine import Pin 
import network


def create_ap(ap_name:str='esp32-ap'):
    ap = network.WLAN(network.AP_IF) 
    ap.active(True) 
    ap.config(essid=ap_name)

def connect_wifi(essid:str,password:str):
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    wlan.disconnect()

    print(f'scanning:{wlan.scan()}')
    print(f'connecting',end="")
    wlan.connect(essid,password)

    while not wlan.isconnected():
        print(".",end='')
        time.sleep(0.5)
    print('\n!!!connect success!!!\n')
 
connect_wifi('Wokwi-GUEST','')
 
```



HTTP请求

```python
import urequests

def http_request_demo():

    request_params={"city":"上海","key":"a702b975fa48a063b1a57c938bafb47a"}
    url=f"http://apis.juhe.cn/simpleWeather/query?city={request_params.get('city')}&key={request_params.get('key')}"
    response = urequests.get(url)
    print(response.text)
    print(response.json())

    realtime = response.json()['result']['realtime']
    print(realtime)

http_request_demo()
```



## 控制

摇杆控制



```python
from machine import Pin,PWM,ADC
import time

def joystick_test():
    ps2_x = ADC(Pin(15),atten=ADC.ATTN_11DB)
    ps2_y = ADC(Pin(2),atten=ADC.ATTN_11DB)
    ps2_button=Pin(4,Pin.IN)

    while 1:
        print(f"x:{ps2_x.read()},y:{ps2_y.read()},z:{ps2_button.value()}")
        time.sleep(0.2)




def control_demo():
    ps2_x = ADC(Pin(15),atten=ADC.ATTN_11DB)
    ps2_y = ADC(Pin(2),atten=ADC.ATTN_11DB)
 
    my_servo =PWM(Pin(13,Pin.OUT) ,freq=50)
  
    while 1 :
        x_val = ps2_x.read()

        servo_angle = x_val/4095*(2.4-0.5)/20*1024+0.5/20*1024
        my_servo.duty(round(servo_angle))
        time.sleep(0.2)
        
control_demo()
```



继电器

```python

from machine import Pin,PWM,ADC
import time
 
relay_pin = Pin(15,Pin.OUT)

def relay_on():
    relay_pin.value(1)
 
def relay_off():
    relay_pin.value(0)

def blink():
    relay_on()
    time.sleep(0.5)
    relay_off()
    time.sleep(0.5)

while 1:
    blink()

```





## SD

```


```





























