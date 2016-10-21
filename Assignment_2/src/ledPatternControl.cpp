#include "mbed.h"

void show_pattern(int *pattern, int& numPattern, BusOut& bus_out, int length,int waitTime = 200){
    if (numPattern >= length){
      numPattern = 0 ;
    }
    bus_out = pattern[numPattern];
    wait_ms(waitTime);
}
