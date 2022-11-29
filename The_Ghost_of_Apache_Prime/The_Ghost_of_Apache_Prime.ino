#include <Wire.h>
#include <Servo.h>
int ledPin = 8;
int leedPin = 2;
int buzzerPin = 3;
int trig = 4;
int echo = 5;
Servo motorA;
Servo motorP;
int motoraPin = 6;
int motorpPin = 7;
//basic integer setup declaring all the materials we will need
void setup()
{
  Serial.begin(9600); //start our serial monitor ata refresh rate of 9600
  motorA.attach(motoraPin); // attaches our first motor to get power
  motorP.attach(motorpPin); // attaches our second motor to get  power
  pinMode(ledPin, OUTPUT); // says led is ouput
  pinMode(leedPin, OUTPUT);// says leed is output
  pinMode(buzzerPin, OUTPUT);// says buzzer is output
}

void loop()
{
  long duration, inches, cm; //declares variables for the ping and the result is in inches and centimeters
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);

  pinMode(echo, INPUT);
  duration = pulseIn(echo, HIGH); // transducer code converted space to time
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  delay(100);

  if (inches > 18)
  {
    motorA.write(0); // tells motor not to spin if above 18 in
    motorP.write(0); // tells motor not to spin if above 18 in
    digitalWrite(ledPin, LOW); //led wont turn on if above 18 in
    digitalWrite(leedPin, LOW);//led wont turn on if above 18 in
    //digitalWrite(buzzerPin, LOW);//buzzer wont turn on if above 18 in
    noTone(buzzerPin);
  }
  if (inches < 18 && inches > 2)
  {
    for (int i = 0; i < 100; i = i + 20) // the knight rider statement(for loop to rotate motor to 20 degrees)
    {
      motorA.write(i); //tells motor to spin to i
      motorP.write(i); //tells motor to spin to i
      if (i == 20)
      {
        digitalWrite(ledPin, HIGH);//led jawn (turns led on if under 18 and above 2)
        delay(250);
        digitalWrite(leedPin, HIGH); //led jawn (turns led on if under 18 and above 2)
        delay(250);
        tone(buzzerPin, 6); // Tone(buzzerPin, 6) turns on the buzzer with a frequency of 6
        delay(250);
        Serial.println("buzzer should be making noise");
      }
      
      delay(15);
    }
    delay(5000);
    Serial.println("rotated 100 degrees");
  }
  if (inches < 2)
  {
    motorA.write(0); // tells motor not to spin if under 2 in
    motorP.write(0); // tells motor not to spin if under 2 in
    digitalWrite(ledPin, LOW); //led wont turn on if under 2 in
    digitalWrite(leedPin, LOW);//led wont turn on if under 2 in
    noTone(buzzerPin);
    //digitalWrite(buzzerPin, LOW); //buzzer wont turn on if under in
  }



}


long microsecondsToInches(long microseconds) // converts distance to time
{
  return microseconds / 74 / 2;
}
long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}
