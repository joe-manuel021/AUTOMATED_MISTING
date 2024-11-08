void saveEEPROM() {
  // Write values to EEPROM
  EEPROM.put(0, dht_Threshold_Lower);      // Store the first float at address 0
  EEPROM.put(4, dht_Threshold_Upper);      // Store the second float at address 4
  EEPROM.put(8, totalSeconds);        // Store the long at address 8

  // Commit changes to EEPROM
  EEPROM.commit();

  Serial.println("Data Save");
}
