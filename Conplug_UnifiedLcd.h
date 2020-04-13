//
// Copyright (c) 2019 Conplug (https://conplug.com.tw)
// Author: Hartman Hsieh
//
// Description :
//   IIC address detects automatically.
//
// Connections :
//   LCD Module => IIC
//
// Required Library :
//   https://github.com/bearwaterfall/DFRobot_LCD-master
//   https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library
//

#ifndef __CONPLUG_UNIFIEDLCD_H__
#define __CONPLUG_UNIFIEDLCD_H__

#include <inttypes.h>
#include "Print.h"


#define LCD_LIB_TYPE_DFROBOT 1
#define LCD_LIB_TYPE_COMMON 2


#include "DFRobot_LCD.h"
#include <LiquidCrystal_I2C.h>

class Conplug_UnifiedLcd : public Print 
{

public:
    Conplug_UnifiedLcd(uint8_t lcd_cols, uint8_t lcd_rows);
    void init();
    virtual size_t write(uint8_t);
    void setCursor(uint8_t, uint8_t);
    void setRGB(uint8_t r, uint8_t g, uint8_t b); // Set backlight color
    void printSpace(int count);

private:
    int Col = 16;
    int Row = 2;
    DFRobot_LCD* DfrobotLcd = 0;
    LiquidCrystal_I2C* CommonLcd = 0;
    int LcdLibType = LCD_LIB_TYPE_DFROBOT;
    int TryLcdAddress[2] = {0x27, 0x3f};

};

#endif // __CONPLUG_UNIFIEDLCD_H__
