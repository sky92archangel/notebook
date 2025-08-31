
#define LED_PIN 12
#define LED_PIN_ONCE 13

hw_timer_t *timer = NULL;
hw_timer_t *timer_once = NULL;
  
//中断函数 让LED亮几秒
void IRAM_ATTR timer_interrupt() {
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}

void IRAM_ATTR timer_once_interrupt() {
  digitalWrite(LED_PIN_ONCE, !digitalRead(LED_PIN_ONCE));
 
  // timerAlarm(timer_once, 0, false, 0);  // 手动禁用定时器
}

void setup() { 
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN_ONCE, OUTPUT);

  // 1. 初始化定时器：仅需传入「频率」（单位：Hz）
  // 旧代码“80分频”对应ESP32主频240MHz，计算频率：240MHz / 80 = 3MHz → 但实际需1ms中断，频率应为1000Hz
  timer = timerBegin(1000);       // 定时器0（自动分配），1000Hz → 1ms中断周期
  timer_once = timerBegin(1000);  // 定时器1（自动分配），1000Hz → 1ms中断周期

  // 2. 绑定中断函数：仅需传入「定时器」和「中断函数」
  timerAttachInterrupt(timer, timer_interrupt);  // 新内核默认边缘触发，无需第三个参数
  timerAttachInterrupt(timer_once, timer_once_interrupt);

  // 3. 设置中断周期并启用定时器：合并旧代码的timerAlarmWrite和timerAlarmEnable
  // 注意：timerWrite的单位是「时钟周期」，需根据定时器频率换算
  // 公式：时钟周期数 = 目标周期（秒） × 定时器频率（Hz）
  uint32_t alarm_cycles = 1 * 1000;  // 1秒中断 → 1s × 1000Hz = 1000个时钟周期

  // 启用定时器（第二个参数true=自动重载，false=单次触发）
  timerAlarm(
    timer,         // 定时器对象
    alarm_cycles,  // 中断周期（1000个时钟周期 = 1秒）
    true,          // 自动重载（循环触发）
    0              // 重载次数（0=无限次）
  );

  // 单次定时器：5秒后触发一次（5000个时钟周期），仅触发1次
  timerAlarm(
    timer_once,        // 定时器对象
    alarm_cycles * 3,  // 中断周期（5000个时钟周期 = 5秒）
    false,             // 不自动重载（仅触发一次）
    0                  // 重载次数（0=无限次，但因autoreload=false，实际只触发1次）
  );
}

void loop() {

}
