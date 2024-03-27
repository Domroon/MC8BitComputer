# Microcontroller 8Bit Computer

## Install Arduino on ArchLinux

    yay arduino-cli
    arduino-cli core update-index

## Compile and Upload

    arduino-cli compile --fqbn arduino:avr:nano ./main/main.ino
    sudo arduino-cli upload -p /dev/ttyUSB0 --fqbn arduino:avr:nano:cpu=atmega328old ./main/main.ino

## Documentation
https://docs.arduino.cc/hardware/nano/