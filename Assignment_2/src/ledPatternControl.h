#ifndef LEDPATTERNCONTROL_H
#define LEDPATTERNCONTROL_H

#include "mbed.h"

void show_pattern(int *pattern, int& numPattern, BusOut& bus_out, int length,int waitTime = 200);

#endif
