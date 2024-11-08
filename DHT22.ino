void dhtReading() {
  temp1 = dht1.readTemperature();
  hum1 = dht1.readHumidity();

  temp2 = dht2.readTemperature();
  hum2 = dht2.readHumidity();

  temp3 = dht3.readTemperature();
  hum3 = dht3.readHumidity();

  temp4 = dht4.readTemperature();
  hum4 = dht4.readHumidity();

  // Initialize variables for calculating the averages
  float totalTemp = 0.0;
  float totalHum = 0.0;
  int workingSensors = 0;

  // Display individual sensor values and accumulate total for average calculation
  if (!isnan(temp1) && !isnan(hum1)) {
    Serial.print("DHT1 Temperature: ");
    Serial.println(temp1);
    Serial.print("DHT1 Humidity: ");
    Serial.println(hum1);
    totalTemp += temp1;
    totalHum += hum1;
    workingSensors++;
  } else {
    Serial.println("DHT1 failed");
  }

  if (!isnan(temp2) && !isnan(hum2)) {
    Serial.print("DHT2 Temperature: ");
    Serial.println(temp2);
    Serial.print("DHT2 Humidity: ");
    Serial.println(hum2);
    totalTemp += temp2;
    totalHum += hum2;
    workingSensors++;
  } else {
    Serial.println("DHT2 failed");
  }

  if (!isnan(temp3) && !isnan(hum3)) {
    Serial.print("DHT3 Temperature: ");
    Serial.println(temp3);
    Serial.print("DHT3 Humidity: ");
    Serial.println(hum3);
    totalTemp += temp3;
    totalHum += hum3;
    workingSensors++;
  } else {
    Serial.println("DHT3 failed");
  }

  if (!isnan(temp4) && !isnan(hum4)) {
    Serial.print("DHT4 Temperature: ");
    Serial.println(temp4);
    Serial.print("DHT4 Humidity: ");
    Serial.println(hum4);
    totalTemp += temp4;
    totalHum += hum4;
    workingSensors++;
  } else {
    Serial.println("DHT4 failed");
  }

  // Calculate the average temperature and humidity only if there are working sensors
  if (workingSensors > 0) {
    avgTemp = totalTemp / workingSensors;
    avgHum = totalHum / workingSensors;

    Serial.print("Average Temperature: ");
    Serial.println(avgTemp);
    Serial.print("Average Humidity: ");
    Serial.println(avgHum);

    // Relay control logic based on humidity
    if (avgHum >= dht_Threshold_Upper) {
      digitalWrite(RELAY_PIN, LOW);  // Turn OFF the relay
      Serial.println("Relay OFF (Humidity High)");
    } else if (avgHum <= dht_Threshold_Lower) {
      digitalWrite(RELAY_PIN, HIGH);   // Turn ON the relay
      Serial.println("Relay ON (Humidity Low)");
    }
  } else {
    Serial.println("No working sensors.");
    digitalWrite(RELAY_PIN, LOW);   // Turn on the relay if no sensors are working
  }

  if (digitalRead(RELAY_PIN) == HIGH) {
    pumpState = "ON ";
  }
  else {
    pumpState = "OFF ";
  }
  // Delay before the next reading
  delay(1000);  // Wait for 2 seconds between readings
}
