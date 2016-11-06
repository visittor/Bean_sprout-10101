#include "mbed.h"
#include "ledPatternControl.h"

// Serial pc(D1,D0);
Serial pc(D8,D2);

BusOut led(D7,D9,D10,D11,D12,D13,D14,D15);

DigitalIn sw4(D4);
DigitalIn sw5(D5);
DigitalIn sw6(D6);

AnalogIn analog_val(A1);

int pat_1[16] = {1,2,4,8,16,32,1,2,4,8,16,32,63,0,63,0};
int pat_2[16] = {32,16,8,4,2,1,1,2,4,8,16,32,63,0,63,0};
int pat_3[15] = {63,0,62,60,56,48,32,0,32,48,56,60,62,63,0};
int pat_4[13] = {5,10,20,40,32,40,20,10,5,0,63,0,1};
int pat_5[8] = {129,66,36,24,36,66,129,255};
int pat_6[35] = {1,2,4,8,16,32,64,128,129,130,132,136,160,192,193,194,196,200,208,224,225,226,228,232,240,241,242,244,248,249,250,252,253,254,255};
int pat_7[9] = {255,231,195,129,0,129,195,231,255};
int pat_8[35] = {255,254,253,252,250,249,248,244,242,241,240,232,228,226,225,224,208,200,196,194,193,192,160,136,132,130,129,128,64,32,16,8,4,2,1};

int number_frame = 0;

uint8_t next_number = '0';
uint8_t current_number = '0';
int showing = 0;
int count = 0;

uint8_t data;
uint8_t choose_pattern;

float meas;

int main() {

  pc.printf("************\n");
  pc.printf("   Menu   \n");
  pc.printf("************\n");
  pc.printf("1.1\n");
  pc.printf("2.2\n");
  pc.printf("3.3\n");

  while(1){
      if (next_number == '0'){
        // pc.printf("************\n");
        // pc.printf("   Menu   \n");
        // pc.printf("************\n");
        // pc.printf("1.1\n");
        // pc.printf("2.2\n");
        // pc.printf("3.3\n");
        if(pc.readable()){
            next_number = pc.getc();
            current_number = next_number;
            number_frame = 0;
            count = 0;
            if (current_number == '1'){
              pc.printf("LED Test\n");
              pc.printf("a.LED ON\n");
              pc.printf("s.LED OFF\n");
              pc.printf("x.Exit\n");
            }
            // else if(current_number == '2'||current_number=='3'){
            //   led = 0;
            //   number_frame = 0;
            //   data = '0';
            // }
          }
        }


      if (current_number == '1'){
          // pc.printf("%c %d\r",data,current_number );
          // pc.printf("%d %d\r",data,current_number );
          if (pc.readable()){
            uint8_t dataTemp =pc.getc();
            // pc.printf("%d %d\r",dataTemp,current_number );
            if (dataTemp == 'a'||dataTemp=='d'||dataTemp=='s'||dataTemp=='x'){data = dataTemp;}
            else{}
            if (data == 'x'){

            }
            else{
              choose_pattern = data;
            }
            showing = 1;
          }
          // pc.printf("%d %d\r",choose_pattern,current_number );
          // switch (choose_pattern) {
          //   case 'a':
          //     show_pattern(pat_7,number_frame,led,9);
          //     number_frame += 1;
          //     break;
          //   case 'd':
          //     show_pattern(pat_8,number_frame,led,35);
          //     number_frame += 1;
          //     break;
          //   case 's':
          //     break;
          // }
          // pc.printf("wait\n");
          // pc.printf("%d %d\r",dataTemp,current_number );
      }


      else if (current_number == '2'){
        if (pc.readable()){
          data = pc.getc();
        }
        pc.printf("switch status = %d%d%d\n",sw4.read(),sw5.read(),sw6.read());
        wait_ms(200);
      }

      else if (current_number=='3'){
        if (pc.readable()){
          data = pc.getc();
        }
        meas = analog_val.read();
        pc.printf("analog value =  %f\n",meas*3.3 );
        wait_ms(200);
      }
      switch (choose_pattern) {
        case 'a':
          show_pattern(pat_7,number_frame,led,9);
          number_frame += 1;
          break;
        case 'd':
          show_pattern(pat_8,number_frame,led,35);
          number_frame += 1;
          break;
        case 's':
          break;
      }

      if (data == 'x'){
        if (current_number=='2'||current_number=='3'||current_number=='1'){
          current_number = '0';
        }
        if (count == 0){
          pc.printf("************\n");
          pc.printf("   Menu   \n");
          pc.printf("************\n");
          pc.printf("1.1\n");
          pc.printf("2.2\n");
          pc.printf("3.4\n");
          next_number = '0';
          count += 1;
        }

        data = '\n';
      }


  }

  return 0;
}
