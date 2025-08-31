
#define FREQ 2000     //频率
#define CHANNEL 0     //通道
#define RESOLUTION 8  //分辨率
#define LED_PIN 13
 
void setup() { 
  //示例：设置   3.X的通道是自动分配的
  ledcAttach(LED_PIN, FREQ, RESOLUTION);
}

void loop() {
  for (int i = 0; i < pow(2, RESOLUTION); i++) {
    ledcWrite(LED_PIN, i);
    delay(5);
  }

  for (int i = pow(2, RESOLUTION) - 1; i > 0; i--) {
    ledcWrite(LED_PIN, i);
    delay(5);
  }
}
