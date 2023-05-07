/*
Using ultrasonic sensor, display distance on serial monitor
Display the values from the DHT 11 on the lcd as well.
*/
#include <LiquidCrystal.h>          // Allows the lcd library to be referenced for new functions
int STATE;
int Hold;
byte degree[8] = {                  // Create a character for the degree symbol
  B00010,
  B00101,
  B00010,
  B00000,
  B00000,
  B00000,
  B00000,
};
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 8     // Digital pin connected to the DHT sensor 


// Uncomment the type of sensor in use:
#define DHTTYPE    DHT11     // DHT 11
//#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)


DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;


int triggerPin = 6;                            // Set trigger to pin 11
int echoPin = 7;                               // Set echo to pin 12
double d;                                      // Store distance as a double
int Count = 0;                                 // Start the counter at 0

void setup() {
  // put your setup code here, to run once:
	pinMode(triggerPin, OUTPUT);       
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  lcd.begin(15,2);                                                  // Setup the rows an colums needed
  lcd.createChar(0, degree);                                        // Names the custome character "degree"
  // Initialize device.
  dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));                
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);                                                   
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 5000;
STATE = digitalRead(inpin);

}

void loop() {
  // put your main code here, to run repeatedly:
  d = findDistance(triggerPin,echoPin);        // function to find distance
  Serial.println(d);                           // print distance to serial monitor
  lcd.setCursor(0,0);                          // Start the line at the first column and first row of the lcd
  lcd.print("Distance= ");
  lcd.print(d);
  lcd.print("cm  ");
  delay(200);    // Delay between measurements.
    delay(delayMS);
    // Get temperature event and print its value.
    sensors_event_t event;

      dht.temperature().getEvent(&event);
      if (isnan(event.temperature)) {
      Serial.println(F("Error reading temperature!"));
      }
      else {
        Serial.print(F("Temperature: "));               // Display "Temperature: " to the serial monitor
        Serial.print(event.temperature);                // Display the temperature in Celsius
        Serial.println(F("°C"));                        // Display "°C" to the serial monitor
        lcd.setCursor(0,1);                             // Start the line at the first column and first row of the lcd
        lcd.print("T= ");                               // Display "Temp= " directly from the analog input, to the lcd
        lcd.print(event.temperature);                   // Displays the temperature in Celsius
        lcd.write(byte(0));                             // Displays the custome character on the lcd
        lcd.print("C");                                 // Displays the letter "C" to signify Celsius
      }

      }

      // Get humidity event and print its value.
      dht.humidity().getEvent(&event);
      if (isnan(event.relative_humidity)) {
        Serial.println(F("Error reading humidity!"));
      }
      else {
        Serial.print(F("Humidity: "));                  // Display "Humidity: " on the serial monitor
        Serial.print(event.relative_humidity);          // Display the hummidity on the serial monitor
        Serial.println(F("%"));                         // Display "%" on the serial monitor
        lcd.setCursor(7,1);                             // Start the line at the first column and second row of the lcd
        lcd.print("H= ");                               // Display "humidity: " on the lcd
        lcd.print(event.relative_humidity);             // Displays the humidity
        lcd.print("%  ");                               // Display the "%" symbol
      }


 }



  

}

double findDistance(int trigger, int echo){       // Function to find distance using trigger and echo as variables
	digitalWrite(trigger, LOW);                     //Send pulse from Ultrasonic
  	delay(5);
  	digitalWrite(trigger, HIGH);
  	delay(10);
  	digitalWrite(trigger, LOW);
 	
  	double time = pulseIn(echo, HIGH);        // Read pulse
  	// Convert the time into a distance
  	double distance = (time/2) * 0.0343;      // Time/2 because there and back and 0.0343 because speed of sound 
  	return distance;                          // gives a value to the function

}