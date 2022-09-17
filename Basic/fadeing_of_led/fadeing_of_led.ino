int led = 5;           // the PWM pin the LED is attached to
void setup() 
{
  pinMode(led, OUTPUT);
}

void loop() 
{
  for(int i=0;i<=255; i=i+5)
  {
    analogWrite(led,i);
    delay(50);
  }

  delay(1000);

  for(int i=255;i>=0; i=i-5)
  {
    analogWrite(led,i);
    delay(50);
  }

}
