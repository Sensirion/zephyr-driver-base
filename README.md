# Zephyr Driver Base

This is an external module for Zephyr. This repository is the basis for every Sensirion Zephyr I2C driver. This means that code that is identical for all drivers does not have to be included in every driver, and our code generator only requires a few minor changes to adapt to Zephyr.

### Run CTest:
```sh
cmake -S ./tests -B build
cmake --build build
cd build
ctest
```