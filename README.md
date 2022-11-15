# hwlcd library

## Instalation

1) add the library as a git submodule or using the `mbed add` command
2) add `include(hwlcd/hwlcd.cmake)` into the CMakeLists.txt file beneath `mbed_configure_app_target`
3) add `include_directories(hwlcd/include)` beneath that
4) add `${HWLCD_SRC}` into the target\_sources

## Usage

```cpp
#include "mbed.h"
#include "hwlcd.hpp"

I2C i2c(I2C_SDA, I2C_SCL);

int main() {
    hwlcd lcd(&i2c, i2c_find_first_device(i2c));
    lcd.init(true, false);
    lcd.puts("Hello world!");

    while (true) {}
}

```
