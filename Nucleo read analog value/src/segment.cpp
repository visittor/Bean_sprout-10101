#include "mbed.h"

void Analog_to_7segment(float analog_value,BusOut& busout){
  analog_value = analog_value*3300;
  int In_mV = (int)analog_value;
  int Integer = In_mV/1000;
  int Decimal = (In_mV/100)%10;
  busout = Integer*16 + Decimal;
}
