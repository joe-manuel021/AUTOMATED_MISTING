void pumpTimeCheck() {
  if (digitalRead(RELAY_PIN) == HIGH) {
    if (timer == true) {
      relayOnTime = rtc.now();
    }
    timer = false;
  }
  else {
    if (timer == false) {
      relayOffTime = rtc.now();
      relayOnDuration = relayOffTime - relayOnTime;
      Serial.println("relayOnDuration = " + String(relayOnDuration.totalseconds()));
      totalSeconds = totalSeconds + relayOnDuration.totalseconds();
      Serial.println("Total Seconds = " + totalSeconds);
      saveEEPROM();
    }
    timer = true;
  }


}

void displayClear() {
  displayText("                    ", 0, 1);
  displayText("                    ", 0, 2);
  displayText("                    ", 0, 3);
  displayText("                    ", 0, 4);
  refreshLCD = TRUE;
}
void horizontalTextScrolling(String textToDisplay, byte textRow, byte textColumn, byte textSize) {

  lcd.setCursor(textRow, textColumn - 1);

  subText = textToDisplay.substring(subTextPosition, textSize + subTextPosition);
  if (millis() - lcdMillis >= lcdScrollSpeed) {
    subTextPosition++;
    lcdMillis = millis();
  }


  if (textToDisplay.length() - subTextPosition < textSize) {
    subText = textToDisplay.substring(subTextPosition);
    subText = ensureLength(subText, textSize);
    Serial.println("subText = " + subText);
  }
  //  Serial.println("subText = " + subText);
  displayText(subText, textRow, textColumn);

  if (subText.length() == 0) {
    subTextPosition = 0;
  }
}





void displayText(String textToDisplay, byte textRow, byte textColumn) {
  int len = textToDisplay.length();

  if (textColumn == 1) {
    for (int i = textRow; i < len + textRow; i++) {
      positionedArray1[i] = textToDisplay.charAt(i - textRow);
    }
    compiledString = String(positionedArray1);
  }

  else if (textColumn == 2) {
    for (int i = textRow; i < len + textRow; i++) {
      positionedArray2[i] = textToDisplay.charAt(i - textRow);
    }
    compiledString = String(positionedArray2);
  }

  else if (textColumn == 3) {
    for (int i = textRow; i < len + textRow; i++) {
      positionedArray3[i] = textToDisplay.charAt(i - textRow);
    }
    compiledString = String(positionedArray3);
  }

  else if (textColumn == 4) {
    for (int i = textRow; i < len + textRow; i++) {
      positionedArray4[i] = textToDisplay.charAt(i - textRow);
    }
    compiledString = String(positionedArray4);
  }

  lcd.setCursor(0, textColumn - 1);
  lcd.print(compiledString);
  //  Serial.println("compiledString = " + compiledString);
}

String ensureLength(String str, int length) {
  // Add spaces to the end if the string is shorter than the desired length
  str.concat("                    ");
  str = str.substring(0, length);
  return str;
}


void rotaryCode_rotation(float &varChange, float stepVal) {

  // Read the current state of CLK
  currentStateCLK = digitalRead(CLK);

  if (currentStateCLK != lastStateCLK  && currentStateCLK == 1) {
    if (digitalRead(DT) != currentStateCLK) {
      varChange = varChange - stepVal;
      currentDir = "CCW";
    } else {
      // Encoder is rotating CW so increment
      varChange = varChange + stepVal;
      currentDir = "CW";
    }

    Serial.print("Direction: ");
    Serial.print(currentDir);
    Serial.print(" | Counter: ");
    Serial.println(varChange);
    refreshLCD = TRUE;
  }

  // Remember last CLK state
  lastStateCLK = currentStateCLK;
}
