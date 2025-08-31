
// #define CHANNEL 0     //通道
// #define RESOLUTION 8  //分辨率
#define BOLD 9600    //波特率  伯德率
#define LED_PIN 12 
#define POT_PIN 10
 
int pot_value;
int led_value;
 
void setup() {

  Serial.begin(BOLD);  
  pinMode(POT_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {

  pot_value = analogRead(POT_PIN);
  Serial.println(pot_value);
  if(pot_value<2000){pot_value=0;}
  if(pot_value>4000){pot_value=4095;}

  led_value = pot_value/16.0;
  if(led_value>255){led_value=255;}
  analogWrite(LED_PIN,led_value);
  
  delay(50);


}
