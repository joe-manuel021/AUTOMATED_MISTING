#include <EEPROM.h>
#include "Arduino.h"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include "RTClib.h"

RTC_DS3231 rtc;

#define DHTTYPE DHT22
#define EEPROM_SIZE 12

// local dependencies
#include "SystemConfig.h"
#include "UserConfig.h"
#include "Buttons.h"
Buttons BtnSelect(SW, INPUT_PULLUP);

// Create DHT instances for each sensor
DHT dht1(DHTPIN1, DHTTYPE);
DHT dht2(DHTPIN2, DHTTYPE);
DHT dht3(DHTPIN3, DHTTYPE);
DHT dht4(DHTPIN4, DHTTYPE);

unsigned long timeElapsed;
LiquidCrystal_I2C lcd(0x27, lcdRow, lcdCol);

void setup() {
  Serial.begin(115200);

  // Initialize the RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  // Initialize the EEPROM
  if (!EEPROM.begin(EEPROM_SIZE)) {
    Serial.println("Failed to initialize EEPROM");
    return;
  }

    EEPROM.get(0, dht_Threshold_Lower);     // Read the first float from address 0
    EEPROM.get(4, dht_Threshold_Upper);      // Read the second float from address 4
    EEPROM.get(8, totalSeconds);             // Read the long from address 8

  Serial.println("Data read from EEPROM:");
  Serial.print("Float 1: ");
  Serial.println(dht_Threshold_Lower);
  Serial.print("Float 2: ");
  Serial.println(dht_Threshold_Upper);
  Serial.print("Long: ");
  Serial.println(totalSeconds);



  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  // Initialize the DHT sensors
  dht1.begin();
  dht2.begin();
  dht3.begin();
  dht4.begin();

  // Initialize the relay pin
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);  // Start with the relay off

  lcd.begin();
  lcd.backlight();
  displayClear();
}

void loop() {

  Main_Display();
  Setup_Selection();
  Threshold_Adjustment();
  Reset_Timer();

  rotaryCode_rotation(selection, 1);
  pumpTimeCheck();
}
