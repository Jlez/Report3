/*
Using ultrasonic sensor, display distance on serial monitor
*/
double findDistance(int trigger, int echo){       // Function to find distance using trigger and echo as variables
	digitalWrite(trigger, LOW);                     //Send pulse from Ultrasonic
  	delay(5);
  	digitalWrite(trigger, HIGH);
  	delay(10);
  	digitalWrite(trigger, LOW);
 	
  	double time = pulseIn(echo, HIGH);        // Read pulse
  	// Convert the time into a distance
  	double distance = (time/2) * 0.0343;      // Time/2 because there and back and 0.0343 because speed of sound or smth idk
  	return distance;                          // gives a value to the function

}
#include <LiquidCrystal.h>          // Allows the lcd library to be referenced for new functions

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


int triggerPin = 6;                            // Set trigger to pin 11
int echoPin = 7;                               // Set echo to pin 12
double d;                                       // Store distance as a double

void setup() {
  // put your setup code here, to run once:
	pinMode(triggerPin, OUTPUT);       
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  lcd.begin(15,2);                             // Setup the rows an colums needed

}

void loop() {
  // put your main code here, to run repeatedly:
  d = findDistance(triggerPin,echoPin);        // function to find distance
  Serial.println(d);                           // print distance to serial monitor
  lcd.setCursor(0,0);                          // Start the line at the first column and first row of the lcd
  lcd.print("Distance= ");                     // Display "Distance= " on the lcd
  lcd.print(d);                                // Display the distance on the lcd
  lcd.print("cm  ");                           // Display "cm  " on the lcd, the spaces after cm are to clear previous numbers
  delay(200);                                  // Delay to make it easier to read the lcd


}

