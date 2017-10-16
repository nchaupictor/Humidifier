// Humidifier Unit for Arrayer
// Parts:
// - 16x2 LCD Screen
// - Funduino Nano
// - DHT11 Temperature/Humidity Sensor
// - 2 100 Ohm Resistor
// - 1 10 kOhm Resistor
// - 1 50V Diode
// - IRL520n MOSFET
                            // - 1 1k Potentiometer
// - 1 5V 30mmx30mm Fan

// --------------------------------------------------------------------------------------------------//
#include "DHT.h"
#include <LiquidCrystal.h>

//Define constants
#define DHTPIN 6     
#define FanPin 9
#define DHTTYPE DHT11   // DHT 11
unsigned long time;

// Initialise classes
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(12,11,5,4,3,2);

// --------------------------------------------------------------------------------------------------//
void setup() {
  pinMode(FanPin, OUTPUT);
  // Start Serial
  Serial.begin(9600);
  lcd.begin(16,2);
  dht.begin();
}

// --------------------------------------------------------------------------------------------------//
void loop() {
  //Start timer
  Serial.print("Time: ");
  time = millis()/1000;
  Serial.print(time);
  Serial.print("  ");

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print data to serial
  Serial.print("\t");
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");

  // Copy data to lcd
  lcd.setCursor(0,0);
  lcd.print("Humidity: ");
  lcd.print(h);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print(" *C");

  // Create a condition to set humidity to 70% and then shut off fan - ON/OFF control using the MOSFET
  if(h <= 70){
    digitalWrite(FanPin, HIGH);
    Serial.println("Fan ON");
  }
  else{
    digitalWrite(FanPin, LOW);
    Serial.println("Fan OFF");
  }
  
  // Wait a few seconds between measurements.
  delay(5000);
}
