
int pin_list[2] = { 12, 13 };
int num = sizeof(pin_list)/sizeof(pin_list[0]);

void setup() {

  for (int i=0; i < num; i++) {
    auto cur_pin = pin_list[i];
    pinMode(cur_pin, OUTPUT);
    delay(200);
  } 
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i=0; i < num; i++) {
    auto cur_pin = pin_list[i]; 
    digitalWrite(cur_pin, HIGH);
    delay(50);
  } 
  
  for (int i=0; i < num; i++) {
    auto cur_pin = pin_list[i]; 
    digitalWrite(cur_pin, LOW);
    delay(50);
  } 
  
 
}
