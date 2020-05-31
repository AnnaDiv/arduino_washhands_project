/*
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int trigPin = 9;
const int echoPin = 10;

float duration, distance;
int threshold = 15;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Wash hands!");
}

void loop() {
  digitalWrite(trigPin, LOW); //in the loop first you have to make sure that the trigPin is clear so we have to set that pin on a LOW State for just 2 µs. 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);// Now for generating the ultrasound wave we have to set the trigPin on HIGH State for 10 µs.
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH); //Using the pulseIn()function you have to read the travel time and put that value into the variable “duration”. 
  distance = (duration * .0343) / 2; //  At the end the function will return the length of the pulse in microseconds. For getting the distance we will multiply the duration by 0.034 and divide it by 2
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < threshold) {
    countdown();
    lcd.setCursor(0, 1); // set the cursor to column 0, line 1
    lcd.print(" ");
    lcd.setCursor(2, 2);
    lcd.print(" ");
  }
  delay(100);
}

void countdown() { //count down the time you need to wash hands
  
  int seconds = 20;

  for (int i=seconds; i>0; i--) {
    lcd.setCursor(0, 1);
    seconds--;
    if (seconds < 10){
      lcd.setCursor(1, 1);
      lcd.print(" ");
    }
    lcd.setCursor(0, 1);
    lcd.print(seconds);
    lcd.setCursor(2, 2);
    lcd.print("s");
    delay(1000);
  }
  seconds =20;
  lcd.setCursor(0, 1);
  lcd.print("All done!");
  delay(3000);
  lcd.setCursor(0, 1);
  lcd.print(" ");
  lcd.setCursor(1, 1);
  lcd.print(" ");
  lcd.setCursor(2, 2);
  lcd.print(" ");
  lcd.setCursor(3, 3);
  lcd.print(" ");
  lcd.setCursor(4, 4);
  lcd.print(" ");
  lcd.setCursor(5, 5);
  lcd.print(" ");
  lcd.setCursor(6, 6);
  lcd.print(" ");
  lcd.setCursor(7, 7);
  lcd.print(" ");
  lcd.setCursor(8, 8);
  lcd.print(" ");
}
