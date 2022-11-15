#include <hwlcd.hpp>

hwlcd::hwlcd(I2C* i2c, uint8_t address) {
    this->i2c = i2c;
    this->address = address;
}

void hwlcd::init(bool cursor, bool blink) {
    wait_us(20000);
    send_nippel(0b0011, 0, 0);
    wait_us(5000);
    send_nippel(0b0011, 0, 0);
    wait_us(1000);
    send_nippel(0b0011, 0, 0);

    send_nippel(0b0010, 0, 0);

    send_byte(LCD_4_BIT, 0, 0);
    send_byte(LCD_CLEAR, 0, 0);
    send_byte(LCD_CURSOR_RIGHT, 0, 0);
    send_byte(LCD_CURSOR_PRIMARY_LINE, 0, 0);
    send_byte(display_ctrl_builder(true, cursor, blink), 0, 0);

    clear();
}

void hwlcd::cursorpos(uint8_t pos) {
    send_byte(LCD_CURSOR_PRIMARY_LINE + pos, 0, 0);
}

void hwlcd::clear() {
    send_byte(LCD_CLEAR, 0, 0);
    cursorpos(0x0);
}

void hwlcd::putc(char c) {
    send_byte(c, 0, 1);
}

void hwlcd::puts(const char *s) {
    while (*s) {
        putc(*s++);
    }
}

void hwlcd::send_byte(char b, uint8_t rw, uint8_t rs) {
    char data[1];
    data[0] = (b & 0xF0) + 0x08 + ((rw & 0x01) << 1) + (rs & 0x01);
    i2c->write(address, data, 1);
    wait();
    data[0] = (b & 0xF0) + 0xC + ((rw & 0x01) << 1) + (rs & 0x01);
    i2c->write(address, data, 1);
    wait();
    data[0] = (b & 0xF0) + 0x8 + ((rw & 0x01) << 1) + (rs & 0x01);
    i2c->write(address, data, 1);
    wait();
    data[0] = ((b & 0xF) << 4) + 0x8 + ((rw & 0x01) << 1) + (rs & 0x01);
    i2c->write(address, data, 1);
    wait();
    data[0] = ((b & 0xF) << 4) + 0xC + ((rw & 0x01) << 1) + (rs & 0x01);
    i2c->write(address, data, 1);
    wait();
    data[0] = ((b & 0xF) << 4) + 0x8 + ((rw & 0x01) << 1) + (rs & 0x01);
    i2c->write(address, data, 1);
    wait();
}
void hwlcd::send_nippel(char b, uint8_t rw, uint8_t rs) {
    char data[1];
    data[0] = ((b & 0xF) << 4) + 0x0 + ((rw & 0x01) << 1) + (rs & 0x01);
    i2c->write(address, data, 1);
    wait();
    data[0] = ((b & 0xF) << 4) + 0x4 + ((rw & 0x01) << 1) + (rs & 0x01);
    i2c->write(address, data, 1);
    wait();
    data[0] = ((b & 0xF) << 4) + 0x0 + ((rw & 0x01) << 1) + (rs & 0x01);
    i2c->write(address, data, 1);
    wait();
}

void hwlcd::wait() {
    wait_us(1000);
}

uint8_t hwlcd::display_ctrl_builder(bool display, bool cursor, bool blink) {
    return 0x08 | (display ? 0x04 : 0x00) | (cursor ? 0x02 : 0x00) | (blink ? 0x01 : 0x00);
}

uint8_t i2c_find_first_device(I2C& i2c) {
    for (uint8_t address = 0; address < 255; address++) {
        const char sdata[] = {0x55};
        char data[1];
        i2c.write(address, sdata, 1);
        i2c.read(address, data, 1);

        if (data[0] == 0x55) {
            return address;
        }
    }

    abort();
}
