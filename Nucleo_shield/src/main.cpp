#include "mbed.h"

#define RST_BIT 4
#define LAT_BIT 2
#define SLB_BIT 1
#define SCL_BIT 8
#define SDA_BIT 16

#define line1 1;
#define line2 2;
#define line3 4;
#define line4 8;
#define line5 16;
#define line6 32;
#define line7 64;
#define line8 128;

// SPI RGB_SPI(PB_15,D7,D6);

BusOut LINE(D8,D9,D10,D11,D12,D13,D3,D4);

// BusOut something(A0,A1,A2,D6,D7);
// BusIn InSomething(A0,A1,A2,D6,D7);

Serial pc(D1,D0);

DigitalOut RST_LED(PA_4);
DigitalOut LAT_LED(PA_1);
DigitalOut SLB_LED(PA_0);
DigitalOut SDA_LED(D7);
DigitalOut SCL_LED(D6);

struct colorStruct{
  unsigned char R;
  unsigned char G;
  unsigned char B;
};

struct colorStruct color(unsigned char R,unsigned char G,unsigned char B){
  struct colorStruct color2return;
  color2return.R = R;
  color2return.G = G;
  color2return.B = B;
}

uint8_t pat_1[8][8][3] ={ {{255,0,0},{255,18,0},{255,36,0},{255,54,0},{255,72,0},{255,90,0},{255,108,0},{255,126,0}},
                              {{255,18,0},{255,36,0},{255,54,0},{255,72,0},{255,90,0},{255,108,0},{255,126,0},{255,144,0}},
                              {{255,36,0},{255,54,0},{255,72,0},{255,90,0},{255,108,0},{255,126,0},{255,144,0},{255,162,0}},
                              {{255,54,0},{255,72,0},{255,90,0},{255,108,0},{255,126,0},{255,144,0},{255,162,0},{255,180,0}},
                              {{255,72,0},{255,90,0},{255,108,0},{255,126,0},{255,144,0},{255,162,0},{255,180,0},{255,198,0}},
                              {{255,90,0},{255,108,0},{255,126,0},{255,144,0},{255,162,0},{255,180,0},{255,198,0},{255,206,0}},
                              {{255,108,0},{255,126,0},{255,144,0},{255,162,0},{255,180,0},{255,198,0},{255,206,0},{255,224,0}},
                              {{255,126,0},{255,144,0},{255,162,0},{255,180,0},{255,198,0},{255,206,0},{255,224,0},{255,242,0}},
                            };



uint8_t pat_2[8][8][3] ={ {{255,0,0},{255,0,0},{255,0,0},{255,0,0},{255,0,0},{255,0,0},{255,0,0},{255,0,0}},
                              {{255,0,0},{255,0,0},{255,0,0},{255,0,0},{255,0,0},{255,0,0},{255,0,0},{255,0,0}},
                              {{255,0,0},{255,0,0},{255,0,0},{255,0,0},{255,0,0},{255,0,0},{255,0,0},{255,0,0}},
                              {{255,0,0},{255,0,0},{255,0,0},{255,0,0},{255,0,0},{255,0,0},{255,0,0},{255,0,0}},
                              {{255,0,0},{255,0,0},{255,0,0},{255,0,0},{255,0,0},{255,0,0},{255,0,0},{255,0,0}},
                              {{255,0,0},{255,0,0},{255,0,0},{255,0,0},{255,0,0},{255,0,0},{255,0,0},{255,0,0}},
                              {{255,0,0},{255,0,0},{255,0,0},{255,0,0},{255,0,0},{255,0,0},{255,0,0},{255,0,0}},
                              {{255,0,0},{255,0,0},{255,0,0},{255,0,0},{255,0,0},{255,0,0},{255,0,0},{255,0,0}}
                              };
int main(int argc, char const *argv[]) {
  pc.printf("dddddddddddddddddddddddddddddddddddddddddddddddddddddddd" );
  int wd;
  SCL_LED = 1;
  RST_LED = 1;
  RST_LED =0;
  RST_LED =1;
  // RGB_SPI.frequency(20000000);
  // RGB_SPI.format(8,1);
  LAT_LED = 0;
  SLB_LED  =0;
  int l=0;
  LINE = 1;
  for (int i =0;i<8;i++){
    for(int j =0;j<3;j++){
      for(int k=0;k<6;k++){
        SDA_LED = 1;
        SCL_LED = 0;
        SCL_LED = 1;
        }
      }
      LINE = LINE*2;
    }

  LAT_LED = 1;
  LAT_LED = 0;
  pc.printf("wait\n");
  wait(1);

  // RGB_SPI.format(8,0);

  uint8_t color[3] = {10,10,0};
  char line = 0x01;
  int counter = 1;
  uint8_t c;

  LINE = 1;
  pc.printf("d" );
  LAT_LED = 0;
  while (1==1) {
    // RST_LED =0;
    // RST_LED =1;
    SLB_LED = 1;
    for(int i = 0; i<8;i++){
      for(int j = 0; j <3; j++){
        c = color[j];
        if (j == 0){
          // pc.printf("red\n");
        }
        else if (j ==1){
          // pc.printf("green\n");
        }
        else{
          // pc.printf("blue\n" );
        }
        for(int k = 0; k <8; k++){
          if (c&0x80){
            SDA_LED = 1;
          }
          else{
            SDA_LED = 0;
          }
          // pc.printf("%d ",c&0x80 );
          c= c<<1;
          SCL_LED = 0;
          SCL_LED = 1;
          // RGB_SPI.write(100);
        }
        // pc.printf("\n" );
      }

    }
    LINE = 0;
    LAT_LED = 1;
    LAT_LED = 0;
    LINE = counter;
    counter *= 2;

    // pc.printf("Finish loop\n");
    if (counter>256){counter = 1;}

  }


  return 0;
}
