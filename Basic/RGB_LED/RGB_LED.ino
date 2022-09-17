const int RED_PIN = 5;
const int GREEN_PIN = 4;
const int BLUE_PIN = 0;

void setup()
{
pinMode(RED_PIN, OUTPUT);
pinMode(GREEN_PIN, OUTPUT);
pinMode(BLUE_PIN, OUTPUT);
}
void loop()
{

mainColors();
showSpectrum();
mainColors();
}
void mainColors()
{
// Off (all LEDs off):

digitalWrite(RED_PIN, 1);
digitalWrite(GREEN_PIN, 1);
digitalWrite(BLUE_PIN, 1);

delay(1000);

// Red (turn just the red LED on):

digitalWrite(RED_PIN, 0);
digitalWrite(GREEN_PIN, 1);
digitalWrite(BLUE_PIN, 1);

delay(1000);

// Green (turn just the green LED on):

digitalWrite(RED_PIN, 1);
digitalWrite(GREEN_PIN, 0);
digitalWrite(BLUE_PIN, 1);

delay(1000);

// Blue (turn just the blue LED on):

digitalWrite(RED_PIN, 1);
digitalWrite(GREEN_PIN, 1);
digitalWrite(BLUE_PIN, 0);

delay(1000);

// Yellow (turn red and green on):

digitalWrite(RED_PIN, 0);
digitalWrite(GREEN_PIN, 0);
digitalWrite(BLUE_PIN, 1);

delay(1000);

// Cyan (turn green and blue on):

digitalWrite(RED_PIN, 1);
digitalWrite(GREEN_PIN, 0);
digitalWrite(BLUE_PIN, 0);

delay(1000);

// Purple (turn red and blue on):

digitalWrite(RED_PIN, 0);
digitalWrite(GREEN_PIN, 1);
digitalWrite(BLUE_PIN, 0);

delay(1000);

// White (turn all the LEDs on):

digitalWrite(RED_PIN, 0);
digitalWrite(GREEN_PIN, 0);
digitalWrite(BLUE_PIN, 0);

delay(1000);
}
void showSpectrum()
{

for (int i=-255;i<=0; i=i+5)
{
    analogWrite(RED_PIN,i);
    analogWrite(GREEN_PIN,i+255);
    analogWrite(BLUE_PIN,i+500);
    delay(10);
}
}
