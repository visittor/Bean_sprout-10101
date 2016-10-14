#include "mbed.h"
#include "segment.h"

AnalogIn analog_value(A1);
BusOut led(D2,D3,D4,D5,D6,D7,D8,D9);
DigitalIn sw(D10);


void lab2_1(float analog_value);
// void Analog_to_7segment(float analog_value,BusOut& busout);

int sw_val_old = 0;
int sw_val;
bool is_7seg = false;

int main(int argc, char const *argv[]) {
  /* code */
  while(1){
    sw_val = sw.read();

    if (sw_val==1 && sw_val_old == 0){
      is_7seg = !is_7seg;
    }
    float analog = analog_value.read();

    if (is_7seg == true){
      Analog_to_7segment(analog,led);
    }
    else{
      lab2_1(analog);
    }

    printf("%d \n",sw_val);

    sw_val_old = sw_val;

  }
  return 0;
}

void lab2_1(float analog_value) {
    printf("\nAnalogIn example\n");


        float meas = analog_value; // Converts and read the analog input value (value from 0.0 to 1.0)
        meas = meas * 3300; // Change the value to be in the 0 to 3300 range
        printf("measure = %.0f mV\n", meas);
        if (meas < 412 ) { // If the value is greater than 2V then switch the LED on
          led = 1;
        }
        else if (meas > 412 && meas < 421*2) {
          led = 3;
          printf("LED3 \n");
        }
        else if (meas > 412*2 && meas < 421*3) {
          led = 7;
          printf("LED7 \n");
        }
        else if (meas > 412*3 && meas < 421*4) {
          led = 15;
          printf("LED15 \n");
        }
        else if (meas > 412*4 && meas < 421*5) {
          led = 31;
          printf("LED31 \n");
        }
        else if (meas > 412*5 && meas < 421*6) {
          led = 63;
          printf("LED63 \n");
        }
        else if (meas > 412*6 && meas < 421*7) {
          led = 127;
          printf("LED127 \n");
        }
        else if (meas > 412*7 && meas < 421*8) {
          led = 255;
          printf("LED255 \n");
        }
        wait(0.2); // 200 ms

}
// void Analog_to_7segment(float analog_value,BusOut& busout){
//   analog_value = analog_value*3300;
//   int In_mV = (int)analog_value;
//   int Integer = In_mV/1000;
//   int Decimal = (In_mV/100)%10;
//   busout = Integer*16 + Decimal;
//   wait(0.2);
// }
