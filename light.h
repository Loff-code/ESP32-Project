#include <Arduino.h>

int light(bool state, bool appendState){
  int analogValue = analogRead(36);
  String convValue = "";
  // We'll have a few threshholds, qualitatively determined
  if (analogValue < 40) {
      convValue += " => Dark";
  } else if (analogValue < 800) {
    convValue += " => Dim";
  } else if (analogValue < 2000) {
    convValue += " => Light";
  } else if (analogValue < 3200) {
    convValue += " => Bright";
  } else {
    convValue += " => Very bright";
  }
  String output = "\nAnalog Value = "+(String(analogValue) + convValue);
  
  if (state)
  {
   Serial.println(output);
  }
  
  
  fileAppend(output, appendState);
  return analogValue;
}

