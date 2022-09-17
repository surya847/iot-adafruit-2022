#define TRIGGER 5 // defining trigger pin
#define ECHO 4 // defining echo pin


void setup()
{
  Serial.begin(9600);
  pinMode(TRIGGER, OUTPUT); //initializing trigger as output
  pinMode(ECHO, INPUT); //initialing trigger as input
}

void loop()
{
  int duration1, dist1;
  digitalWrite(TRIGGER, LOW); // make trigger low
  delayMicroseconds(2);
  digitalWrite(TRIGGER, HIGH); // make trigger high
  delayMicroseconds(10); //give 10 microsec delay
  digitalWrite(TRIGGER, LOW);
  duration1 = pulseIn(ECHO, HIGH);
  dist1 = duration1*0.034 / 2; // calibrate the distance using pulse
  Serial.print("distance in cm: ");
  Serial.println(dist1); // Print the distance value
  delay(1000);

}
