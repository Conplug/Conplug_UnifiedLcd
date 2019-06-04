

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

private:
    DFRobot_LCD* DfrobotLcd = 0;
    LiquidCrystal_I2C* CommonLcd = 0;
    int LcdLibType = LCD_LIB_TYPE_DFROBOT;
    int TryLcdAddress[2] = {0x27, 0x3f};

};

#endif // __CONPLUG_UNIFIEDLCD_H__
