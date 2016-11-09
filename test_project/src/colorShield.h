#ifndef COLORSHIELD_H
#define COLORSHIELD_H

#include "mbed.h"



class Color_shield{
public:
  void init();
  void display(uint8_t *color[8][8], int multiplier);
  void display(uint8_t color[8][8][3], int multiplier);
};
#endif
