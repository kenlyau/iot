const int led = 2;
void setup() {
  pinMode(led, OUTPUT);
  digitalWrite(led, 1);   
  delay(1000);                      
  digitalWrite(led, 0);
  delay(2000); 
  ESP.deepSleep(20e6); // 20e6 is 20 microseconds
}

void loop() {
}
