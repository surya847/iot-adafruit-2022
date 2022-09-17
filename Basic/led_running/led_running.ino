
int led[4]={ 16,5,4,0};

void setup()
{
  for(int i=0; i<4; i++)
  {
    pinMode(led[i], OUTPUT);
  }
}

void loop()
{
  for(int i =0; i<4;i++)
  {
    digitalWrite(led[i], HIGH);
    delay(100);
    digitalWrite(led[i], LOW);
   }

   delay(500);

 for(int i =3; i>=0;i--)
  {
    digitalWrite(led[i], HIGH);
    delay(100);
    digitalWrite(led[i], LOW);
   }
   
delay(500);
  
}
