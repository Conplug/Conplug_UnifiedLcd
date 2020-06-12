//
// Copyright (c) 2019 Conplug (https://conplug.com.tw)
// Author: Hartman Hsieh
//
// Description :
//   According to IIC address to initialize different library .
//
// Connections :
//   Connect LCD module to Arduino's IIC bus.
//
// Required Library :
//   https://github.com/bearwaterfall/DFRobot_LCD-master
//   https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library
//

//#include <ESP8266WiFi.h>
#include "Wire.h"
#include "Conplug_UnifiedLcd.h"

Conplug_UnifiedLcd UnifiedLcd(16, 2);

void setup() {
  Serial.begin(9600);
  Wire.begin(); // Join I2C bus
  UnifiedLcd.init();
}

void loop() {
  UnifiedLcd.setCursor(0, 0);
  UnifiedLcd.print(" conplug.com.tw ");
  UnifiedLcd.setCursor(0, 1);
  UnifiedLcd.print("  Hello World!  ");
  delay(2000);
}
