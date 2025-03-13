#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize LCD (Check your I2C address: 0x27 or 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define pins
const int sensorPin = A0; // Moisture sensor
const int pumpLED = 7;    // LED placeholder for pump

// Moisture calibration values
const int dryValue = 600;   // Value when dry
const int wetValue = 300;   // Value when wet
const int threshold = 30;   // Moisture % to turn pump ON

void setup() {
    lcd.begin(16, 2);  
    lcd.backlight();
    pinMode(sensorPin, INPUT);
    pinMode(pumpLED, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    int sensorValue = analogRead(sensorPin);
    int moisturePercent = map(sensorValue, dryValue, wetValue, 0, 100);
    moisturePercent = constrain(moisturePercent, 0, 100);

    Serial.print("Moisture: ");
    Serial.print(moisturePercent);
    Serial.println("%");

    // Display on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Soil Moisture:");
    lcd.setCursor(0, 1);
    lcd.print(moisturePercent);
    lcd.print("%");

    // Pump (LED placeholder) control
    if (moisturePercent < threshold) {
        digitalWrite(pumpLED, HIGH);  // Turn ON LED (Pump)
        Serial.println("Pump ON");
    } else {
        digitalWrite(pumpLED, LOW);   // Turn OFF LED (Pump)
        Serial.println("Pump OFF");
    }

    delay(1000);
}
