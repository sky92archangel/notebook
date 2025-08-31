
#define FREQ 2000     //频率
#define RESOLUTION 8  //分辨率
#define BOLD 9600     //波特率  伯德率

#define LED_PIN 12
#define POT_PIN 10

int pot_value;
int led_value;

void setup() {

  //ADC分辨率
  analogReadResolution(RESOLUTION);
  //输入衰减
  analogSetAttenuation(ADC_11db);

  //建立LEDC通道
  //示例：设置   3.X的通道是自动分配的
  ledcAttach(LED_PIN, FREQ, RESOLUTION);
 
  Serial.begin(BOLD); 
}

void loop() { 
  pot_value = analogRead(POT_PIN);
  Serial.println(pot_value);
 
  if (pot_value < 100) { pot_value = 0; }
  if (pot_value > 255) { pot_value = 255; } 
  ledcWrite(LED_PIN, pot_value);
  
  delay(50);
}
