

#include <Arduino.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <Wire.h>

#include "Conplug_UnifiedLcd.h"


Conplug_UnifiedLcd::Conplug_UnifiedLcd(uint8_t lcd_cols, uint8_t lcd_rows)
{
    Wire.begin();
    //delay(100);
    Wire.beginTransmission((0x7c>>1)); // Address - (0x7c>>1) is DFRobot LCD's.
    uint8_t data8 = Wire.endTransmission();
    if (data8 == 0) {
        LcdLibType = LCD_LIB_TYPE_DFROBOT;
        DfrobotLcd = new DFRobot_LCD(16, 2);
    }
    else {
        LcdLibType = LCD_LIB_TYPE_COMMON;
        //
        // Scan Lcd IIC address in table - TryLcdAddress.
        //
        for(int i = 0; i < sizeof(TryLcdAddress); i++) {
            Wire.beginTransmission(TryLcdAddress[i]);
            data8 = Wire.endTransmission();
            if (data8 == 0) {
                CommonLcd = new LiquidCrystal_I2C(TryLcdAddress[i], 16, 2);
                break;
            }
        }
    }
}


void Conplug_UnifiedLcd::init()
{
    if(LcdLibType == LCD_LIB_TYPE_DFROBOT) {
        if(DfrobotLcd != 0) {
            DfrobotLcd->init();
            //delay(100);
            DfrobotLcd->display();
        }
    }
    else if(LcdLibType == LCD_LIB_TYPE_COMMON) {
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
