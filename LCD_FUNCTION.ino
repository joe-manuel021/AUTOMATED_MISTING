void scrollEffect(float &selector) {

  if (selector >= 5 ) {
    selector = 4;
  }
  else if (selector <= 0 ) {
    selector = 1;
  }
  displayText(" ", 0, 1);
  displayText(" ", 0, 2);
  displayText(" ", 0, 3);
  displayText(" ", 0, 4);
  displayText("*", 0, selector);

}

void resetSelect(float &selector) {

  if (selector >= 5 ) {
    selector = 4;
  }
  else if (selector <= 2 ) {
    selector = 3;
  }

  displayText(" ", 6, 3);
  displayText(" ", 6, 4);
  displayText("*", 6, selector);

}

void Main_Display() {
  if (selectionPage == MAIN) {
    dhtReading();
    if (millis() - MainDisplayMillis > 2000) {
      MainDisplayMillis = millis();
      refreshLCD = TRUE;
    }
    if (refreshLCD == TRUE) {
      float temp = 32.56;
      String tempString = "Avg Temp  : " + String(avgTemp) + String(char(223)) + "C";
      displayText(tempString, 0, 1);
      lcd.write(byte(223)); // ASCII code for degree symbol

      // Continue printing after the degree symbol
      lcd.print("C");
      displayText("Avg Humm  : " + String (avgHum) + "%", 0, 2);
      displayText("Pump State: " + pumpState, 0, 3);
      int minutesPump = totalSeconds / 60;   // Get the total minutes
      int secondsPump = totalSeconds % 60;   // Get the remaining seconds
      displayText("Timed ON  : " + String(minutesPump) + "m " + String(secondsPump) + "s", 0, 4);
      refreshLCD = FALSE;
    }

    if (BtnSelect.isToggled()) {
      selectionPage = SELECTION;
      displayClear();
    }
  }

}


void Setup_Selection() {
  if (selectionPage == SELECTION) {

    if (refreshLCD == TRUE) {
      lcdDisplay();
      if (selection >= 4) {
        selection = 3;
      }
      scrollEffect(selection);
      Serial.print("Setup_Selection");
      refreshLCD = FALSE;
    }

    if (BtnSelect.isToggled()) {
      if (selection == 1) {
        selectionPage = MAIN;
        displayClear();
      }
      else if (selection == 2) {
        selectionPage = THRESHOLD;
        displayClear();
      }
      else if (selection == 3) {
        selectionPage = RESET;
        displayClear();
      }

    }

  }
}


void Threshold_Adjustment() {

  if (selectionPage == THRESHOLD) {

    while (adjustThresholdState1 == TRUE) {
      if (refreshLCD == TRUE) {
        displayText("Return", 1, 1);
        displayText("Adjust Threshold", 1, 2);
        displayText("Upper", 1, 3);
        displayText("Lower", 1, 4);
        displayText("<", 8, 3);
        displayText(">", 16, 3);
        displayText(String(dht_Threshold_Upper, 2), 10, 3);
        refreshLCD = FALSE;
      }
      rotaryCode_rotation(dht_Threshold_Upper, .5);

      if (BtnSelect.isToggled()) {
        adjustThresholdState1 = FALSE;
        adjustThresholdState2 = TRUE;
        displayClear();
      }
    }

    while (adjustThresholdState2 == TRUE) {
      if (refreshLCD == TRUE) {
        displayText("Return", 1, 1);
        displayText("Adjust Threshold", 1, 2);
        displayText("Upper", 1, 3);
        displayText("Lower", 1, 4);
        displayText("<", 8, 4);
        displayText(">", 16, 4);
        displayText(String(dht_Threshold_Lower, 2), 10, 4);
        refreshLCD = FALSE;
      }
      rotaryCode_rotation(dht_Threshold_Lower, .5);

      if (BtnSelect.isToggled()) {
        adjustThresholdState1 = FALSE;
        adjustThresholdState2 = FALSE;
        displayClear();
        saveEEPROM();
      }
    }

    if (refreshLCD == TRUE) {
      if (selection >= 3) {
        selection = 2;
      }
      refreshLCD = FALSE;
      displayText("Return", 1, 1);
      displayText("Adjust Threshold", 1, 2);
      displayText("Upper", 1, 3);
      displayText("Lower", 1, 4);
      displayText(String(dht_Threshold_Upper, 2), 8, 3);
      displayText(String(dht_Threshold_Lower, 2), 8, 4);
      scrollEffect(selection);



    }

    if (BtnSelect.isToggled()) {
      if (selection == 1) {
        selectionPage = SELECTION;
        displayClear();
      }
      else if (selection == 2) {
        adjustThresholdState1 = TRUE;
        refreshLCD = TRUE;
        displayClear();
      }
    }





  }
}

void Reset_Timer() {
  while (selectionPage == RESET) {

    rotaryCode_rotation(resetSelector, 1);

    if (refreshLCD == TRUE) {
      resetSelect(resetSelector);
      displayText("Reset Timer?", 5, 1);
      displayText("YES", 7, 3);
      displayText("NO", 7, 4);
      refreshLCD = FALSE;
    }

    if (BtnSelect.isToggled()) {
      if (resetSelector == 3) {
        displayClear();
        displayText("TIMER RESET", 4, 2);
        totalSeconds = 0;
        delay(1000);
        selectionPage = MAIN;
        saveEEPROM();
        delay(2000);
        esp_restart();
      }

      else {
        if (resetSelector == 4) {
          displayClear();
          displayText("TIMER NOT RESET", 3, 2);
          delay(3000);
          selectionPage = MAIN;
        }
      }
      displayClear();
    }
  }
}

void lcdDisplay() {
  displayText("Return", 1, 1);
  displayText("Adjust Threshold", 1, 2);
  displayText("Reset Timer", 1, 3);
}
