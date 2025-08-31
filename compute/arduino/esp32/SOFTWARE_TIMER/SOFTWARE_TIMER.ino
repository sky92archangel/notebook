#include <Ticker.h>

#define LED_PIN 12    // 板载LED引脚（ESP32S3通常为2号引脚）
#define LED_PIN_ONCE 13
 // 创建Ticker对象
Ticker timer; // 周期性触发定时器
Ticker timer_once;

// 中断函数：翻转指定引脚电平（注意：Ticker中断函数无需IRAM_ATTR）
// 修正：添加参数类型 int
void toggle(int pin) {
  digitalWrite(pin, !digitalRead(pin));
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN_ONCE, OUTPUT);
  // 启动定时器（修正：attch -> attach）
  // 周期性定时器：每0.5秒触发一次，翻转LED_PIN
  timer.attach(0.5,toggle,LED_PIN);
    // 单次触发定时器：2秒后触发一次，翻转LED_PIN_ONCE
  // 注意：Ticker的once()方法用于单次触发
  timer_once.attach(2.1,toggle,LED_PIN_ONCE);
}

void loop() {
}
