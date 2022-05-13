arm-none-linux-gnueabihf-gcc --sysroot sysroot rpi-media-streaming/src/volume/main.c -I sysroot/usr/include/arm-linux-gnueabihf/ -L sysroot/usr/lib/arm-linux-gnueabihf/ -lasound -ldl -lpthread -lm -lrt -o volume


