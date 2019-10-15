//This shot detects the amount of attempted and made shots of a basketball on a 10 ft basketball hoop
//Uses arduino MEGA and sensors to help track distances of a basketball and prints it out on at LCD screen

//library needed to use the LCD screen
#include <LiquidCrystal.h>

//defines the constants
LiquidCrystal lcd(12, 11, 5, 6, 3, 2);
const int buzzer = 13;
const int trigPin = 42;
const int echoPin = 43;
const int trigPin2 = 52;
const int echoPin2 = 53;
const int LED = 8;
int period = 3000;
unsigned long time = 0;

//defines variables
long duration, duration2;
int distance, distance2;
int shotAtt = 0;
int shotMake = 0;
int sound = 200;

//setup for the LED, buzzer, LCD screen, and both distance sensors 
void setup() {
  pinMode(LED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  lcd.begin(16, 2);
  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin2, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}

//This loop tests to see if the first distance sensor (which is above the hoop) has detects motion in front of the rim
//The second sensor will then have a period of time to detect if the ball has fallen from the rim to detect a made shot
void loop() {

  distance = dur();
  distance2 = dur2();
  
  if(distance <= 50)
  {
      lightAndSoundAtt();
      unsigned long currentTime = millis();
      for(int i = 300; i > 0; i--)
      {
        if(dur2() <= 80 )
        {
          lightAndSoundMake();
          shotMake++;
          break;
        }
      }
    shotAtt++;
    display();
  }
}


//this function gets the distance from the distance sensor to output a value in cms
int dur()
{
  // Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;
return distance;
}

//this function gets the distance from the distance sensor to output a value in cms
int dur2()
{
// Clears the trigPin
digitalWrite(trigPin2, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin2, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin2, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration2 = pulseIn(echoPin2, HIGH);

// Calculating the distance
distance2= duration2*0.034/2;
return distance2;
}

//this function lights the LED and sets a single tone on the buzzer when a shot has been attempted
void lightAndSoundAtt()
{
  digitalWrite(LED, HIGH);
  tone(buzzer, sound);
  delay(100);
  noTone(buzzer);
  digitalWrite(LED, LOW);
  lcd.clear();
}

//this function light the LED and sets a series of tones on the buzzer when a shot is made
void lightAndSoundMake()
{
  digitalWrite(LED, HIGH);
      tone(buzzer, sound);
      delay(100);
      digitalWrite(LED, LOW);
    
      digitalWrite(LED, HIGH);
      tone(buzzer, sound+200);
      delay(100);
      digitalWrite(LED, LOW);
    
      digitalWrite(LED, HIGH);
      tone(buzzer, sound+600);
      delay(100);
      noTone(buzzer);
      digitalWrite(LED, LOW);
      lcd.clear();
}

//this function displays the data on the LCD screen
void display()
{
  lcd.print("Score: ");
  lcd.print(shotMake);
  lcd.print("/");
  lcd.print(shotAtt);

  Serial.print("Distance1: ");
  Serial.println(distance);
  Serial.print("Distance2: ");
  Serial.println(distance2);
  Serial.print("SHOTS ATTEMPTED: ");
  Serial.println(shotAtt);
  Serial.print("SHOTS MADE: ");
  Serial.println(shotMake);
}
