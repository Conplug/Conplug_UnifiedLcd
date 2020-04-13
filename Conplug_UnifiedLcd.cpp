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


#include <Arduino.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <Wire.h>

#include "Conplug_UnifiedLcd.h"


Conplug_UnifiedLcd::Conplug_UnifiedLcd(uint8_t lcd_cols, uint8_t lcd_rows)
{
    Conplug_UnifiedLcd::Col = lcd_cols;
    Conplug_UnifiedLcd::Row = lcd_rows;
}

void Conplug_UnifiedLcd::init()
{
    int iic_addr = 0;

    Wire.begin();

    //
    // Scan the IIC address.
    //
    Wire.beginTransmission((0x7c>>1)); // Address - (0x7c>>1) is DFRobot LCD's.
    uint8_t data8 = Wire.endTransmission();
    if (data8 == 0) {
        LcdLibType = LCD_LIB_TYPE_DFROBOT;
        Conplug_UnifiedLcd::Col = 16;
        Conplug_UnifiedLcd::Row = 2;
        iic_addr = (0x7c>>1);
        
    }
    else {
        LcdLibType = LCD_LIB_TYPE_COMMON;
        //
        // Scan Lcd IIC address in table - TryLcdAddress.
        //
        for(int i = 0; i < (sizeof(TryLcdAddress) / sizeof(int)); i++) {
            Wire.beginTransmission(TryLcdAddress[i]);
            data8 = Wire.endTransmission();
            if (data8 == 0) {
                iic_addr = TryLcdAddress[i];
                break;
            }
        }
    }

    //
    // Create the LCD instance and init it.
    //
    if(LcdLibType == LCD_LIB_TYPE_DFROBOT) {
        DfrobotLcd = new DFRobot_LCD(16, 2);
        if(DfrobotLcd != 0) {
            DfrobotLcd->init();
            //delay(100);
            DfrobotLcd->display();
        }
    }
    else if(LcdLibType == LCD_LIB_TYPE_COMMON) {
        CommonLcd = new LiquidCrystal_I2C(iic_addr, Conplug_UnifiedLcd::Col, Conplug_UnifiedLcd::Row);
        if(CommonLcd != 0) {
            CommonLcd->begin();
            CommonLcd->backlight();
        }
    }
}

inline size_t Conplug_UnifiedLcd::write(uint8_t value) {
    if(LcdLibType == LCD_LIB_TYPE_DFROBOT) {
        if(DfrobotLcd != 0) {
            DfrobotLcd->write(value);
        }
    }
    else if(LcdLibType == LCD_LIB_TYPE_COMMON) {
        if(CommonLcd != 0) {
            CommonLcd->write(value);
        }
    }
	return 1;
}

void Conplug_UnifiedLcd::setCursor(uint8_t col, uint8_t row)
{
    if(LcdLibType == LCD_LIB_TYPE_DFROBOT) {
        if(DfrobotLcd != 0) {
            DfrobotLcd->setCursor(col, row);
        }
    }
    else if(LcdLibType == LCD_LIB_TYPE_COMMON) {
        if(CommonLcd != 0) {
            CommonLcd->setCursor(col, row);
        }
    }
}

void Conplug_UnifiedLcd::setRGB(uint8_t r, uint8_t g, uint8_t b)
{
    if(LcdLibType == LCD_LIB_TYPE_DFROBOT) {
        if(DfrobotLcd != 0) {
            DfrobotLcd->setRGB(r, g, b);
        }
    }
}

void Conplug_UnifiedLcd::printSpace(int count)
{
    char* str = new char[Conplug_UnifiedLcd::Col + 1];
    int new_count = count;
    
    if(count > Conplug_UnifiedLcd::Col)
        new_count = Conplug_UnifiedLcd::Col;

    memset(&(str[0]), ' ', new_count);
    str[new_count] = '\0';

    if(LcdLibType == LCD_LIB_TYPE_DFROBOT) {
        if(DfrobotLcd != 0) {
            DfrobotLcd->print(str);
        }
    }
    else if(LcdLibType == LCD_LIB_TYPE_COMMON) {
        if(CommonLcd != 0) {
            CommonLcd->print(str);
        }
    }

    delete [] str;
}
