
#define BUTTON 14
#define LED_PIN 12
 
volatile bool flag = false;
volatile int num = 0;

//中断函数 让LED亮几秒
void handle_interrupt() {
  flag = true;
  num++;

  //如果出发次数为偶数则亮灯 否则暗
  if(num%2==0){
  digitalWrite(LED_PIN, HIGH);
  }
  else{
  digitalWrite(LED_PIN, LOW);

  }
    
  // delay(2000);
  // digitalWrite(LED_PIN,, LOW); 
}

void setup() {
  Serial.begin(9600);

  pinMode(BUTTON, INPUT_PULLDOWN);
  pinMode(LED_PIN,OUTPUT);

  auto button_pin = digitalPinToInterrupt(BUTTON);             //触发中断的端口
  attachInterrupt(button_pin, handle_interrupt, FALLING);      // 设置中断端口、设置执行的函数、设置中断条件
}

void loop() {

  if (flag) {
    Serial.println("LED_FOR_2S");
    flag = false;
  }
}
