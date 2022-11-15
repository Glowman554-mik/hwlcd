#pragma once

#include "mbed.h"

#define LCD_CLEAR 0x01
#define LCD_CURSOR_RIGHT 0x06
#define LCD_CURSOR_PRIMARY_LINE 0x80
#define LCD_4_BIT 0x28

class hwlcd {
    public:
        hwlcd(I2C* i2c, uint8_t address);

        void init(bool cursor, bool blink);
        void cursorpos(uint8_t pos);
        void clear();

        void putc(char c);
        void puts(const char* s);
    private:
        void send_byte(char b, uint8_t rw, uint8_t rs);
        void send_nippel(char b, uint8_t rw, uint8_t rs);
        void wait();
        uint8_t display_ctrl_builder(bool display, bool cursor, bool blink);

        I2C* i2c;
        uint8_t address;
};

uint8_t i2c_find_first_device(I2C& i2c);
