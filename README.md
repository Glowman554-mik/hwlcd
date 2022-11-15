# hwlcd library

## Instalation

1) add the library as a git submodule or using the `mbed add` command
2) add `include(hwlcd/hwlcd.cmake)` into the CMakeLists.txt file beneath `mbed_configure_app_target`
3) add `include_directories(hwlcd/include)` beneath that
4) add `${HWLCD_SRC}` into the target\_sources

