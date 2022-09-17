void setup() 
{
  Serial.begin(9600);
}
void loop() 
{
  int s = analogRead(5);   // read the input on analog pin 0:
  Serial.print(s);        // display the values of 
    delay(1000);
}
