#include "mbed.h"
#include "colorShield.h"

// #define RST_BIT 4
// #define LAT_BIT 2
// #define SLB_BIT 1
// #define SCL_BIT 8
// #define SDA_BIT 16
//
// #define line1 1;
// #define line2 2;
// #define line3 4;
// #define line4 8;
// #define line5 16;
// #define line6 32;
// #define line7 64;
// #define line8 128;

// SPI RGB_SPI(PB_15,D7,D6);

// BusOut LINE(D8,D9,D10,D11,D12,D13,D3,D4);

// BusOut something(A0,A1,A2,D6,D7);
// BusIn InSomething(A0,A1,A2,D6,D7);

Serial pc(D1,D0);

// DigitalOut RST_LED(PA_4);
// DigitalOut LAT_LED(PA_1);
// DigitalOut SLB_LED(PA_0);
// DigitalOut SDA_LED(D7);
// DigitalOut SCL_LED(D6);

// InterruptIn button(PC_13);

Color_shield colorShield;


// struct colorStruct{
//   unsigned char R;
//   unsigned char G;
//   unsigned char B;
// };
//
// struct colorStruct color(unsigned char R,unsigned char G,unsigned char B){
//   struct colorStruct color2return;
//   color2return.R = R;
//   color2return.G = G;
//   color2return.B = B;
// }

uint8_t pat_1[8][8][3] ={     {{0,28,3},{0,26,5},{0,24,7},{0,22,9},{0,20,11},{0,18,12},{0,16,14},{0,14,16}},
                              {{0,26,5},{0,24,7},{0,22,9},{0,20,11},{0,18,12},{0,16,14},{0,14,16},{0,12,18}},
                              {{0,24,7},{0,22,9},{0,20,11},{0,18,12},{0,16,14},{0,14,16},{0,12,18},{0,10,20}},
                              {{0,22,9},{0,20,11},{0,18,12},{0,16,14},{0,14,16},{0,12,18},{0,10,20},{0,8,22}},
                              {{0,20,11},{0,18,12},{0,16,14},{0,14,16},{0,12,18},{0,10,20},{0,8,22},{0,6,24}},
                              {{0,18,12},{0,16,14},{0,14,16},{0,12,18},{0,10,20},{0,8,22},{0,6,24},{0,4,26}},
                              {{0,16,14},{0,14,16},{0,12,18},{0,10,20},{0,8,22},{0,6,24},{0,4,26},{0,2,28}},
                              {{0,30,0},{0,28,3},{0,26,5},{0,24,7},{0,22,9},{0,20,11},{0,18,12},{0,16,14}},
                            };



uint8_t pat_2[8][8][3] ={     {{25,0,1},{25,0,3},{25,0,5},{25,0,7},{25,0,9},{25,0,10},{25,0,12},{25,0,14}},
                              {{25,0,3},{25,0,5},{25,0,7},{25,0,9},{25,0,10},{25,0,12},{25,0,14},{25,0,16}},
                              {{25,0,5},{25,0,7},{25,0,9},{25,0,10},{25,0,12},{25,0,14},{25,0,16},{25,0,18}},
                              {{25,0,7},{25,0,9},{25,0,10},{25,0,12},{25,0,14},{25,0,16},{25,0,18},{25,0,19}},
                              {{25,0,9},{25,0,10},{25,0,12},{25,0,14},{25,0,16},{25,0,18},{25,0,19},{25,0,20}},
                              {{25,0,10},{25,0,12},{25,0,14},{25,0,16},{25,0,18},{25,0,19},{25,0,20},{25,0,22}},
                              {{25,0,12},{25,0,14},{25,0,16},{25,0,18},{25,0,19},{25,0,20},{25,0,22},{25,0,24}},
                              {{25,0,0},{25,0,1},{25,0,3},{25,0,5},{25,0,7},{25,0,9},{25,0,10},{25,0,12}},
                            };
uint8_t pat_3[8][8][3] ={     {{21,0,0},{17,0,0},{13,0,0},{9,13,0},{5,17,0},{1,21,0},{0,25,0},{0,21,1}},
                              {{17,0,0},{13,0,0},{9,13,0},{5,17,0},{1,21,0},{0,25,0},{0,21,1},{0,17,5}},
                              {{13,0,0},{9,13,0},{5,17,0},{1,21,0},{0,25,0},{0,21,1},{0,17,5},{0,13,9}},
                              {{9,13,0},{5,17,0},{1,21,0},{0,25,0},{0,21,1},{0,17,5},{0,13,9},{0,0,13}},
                              {{5,17,0},{1,21,0},{0,25,0},{0,21,1},{0,17,5},{0,13,9},{0,0,13},{0,0,17}},
                              {{1,21,0},{0,25,0},{0,21,1},{0,17,5},{0,13,9},{0,0,13},{0,0,17},{0,0,21}},
                              {{0,25,0},{0,21,1},{0,17,5},{0,13,9},{0,0,13},{0,0,17},{0,0,21},{0,0,25}},
                              {{25,0,0},{21,0,0},{17,0,0},{13,0,0},{9,13,0},{5,17,0},{1,21,0},{0,25,0}},
                            };


// int select_pat = 0;
//
// void flip(){
//   select_pat += 1;
//
//   if (select_pat>2){
//     select_pat = 0;
//   }
// }


int main(int argc, char const *argv[]) {
  // button.fall(&flip);
  // pc.printf("dddddddddddddddddddddddddddddddddddddddddddddddddddddddd" );
  // int wd;
  // SCL_LED = 1;
  // RST_LED = 1;
  // RST_LED =0;
  // RST_LED =1;
  // // RGB_SPI.frequency(20000000);
  // // RGB_SPI.format(8,1);
  // LAT_LED = 0;
  // SLB_LED  =0;
  // int l=0;
  // LINE = 1;
  // for (int i =0;i<8;i++){
  //   for(int j =0;j<3;j++){
  //     for(int k=0;k<6;k++){
  //       SDA_LED = 1;
  //       SCL_LED = 0;
  //       SCL_LED = 1;
  //       }
  //     }
  //     LINE = LINE*2;
  //   }
  //
  // LAT_LED = 1;
  // LAT_LED = 0;
  // pc.printf("wait\n");
  // wait(1);
  colorShield.init();

  // RGB_SPI.format(8,0);

  // uint8_t color[3] = {10,10,0};
  // char line = 0x01;
  // int counter = 1;
  // uint8_t c;
  //
  // LINE = 1;
  // pc.printf("d" );

  while (1==1) {
    // RST_LED =0;
    // RST_LED =1;
    // SLB_LED = 1;
    // counter = 1;
    // for (int l = 0; l<8 ; l++){
    //   LINE = counter;
    //   counter *= 2;
    //   for(int i = 0; i<8;i++){
    //     for(int j = 0; j <3; j++){
    //       if (select_pat == 0){
    //         c = pat_1[l][i][j];
    //       }
    //       else if(select_pat == 1){
    //         c = pat_2[l][i][j];
    //       }
    //       else if(select_pat == 2){
    //         c = pat_3[l][i][j];
    //       }
    //       // switch (select_pat) {
    //       //   pc.printf("fall %d\n",select_pat);
    //       //   case 0:
    //       //     c = pat_1[l][i][j];
    //       //     // c += 2;
    //       //   case 1:
    //       //     c = pat_2[l][i][j];
    //       //   case 2:
    //       //     c = pat_3[l][i][j];
    //       //
    //       // }
    //       c *= 8;
    //       for(int k = 0; k <8; k++){
    //         if (c&0x80){
    //           SDA_LED = 1;
    //         }
    //         else{
    //           SDA_LED = 0;
    //         }
    //         // pc.printf("%d ",c&0x80 );
    //         c= c<<1;
    //         SCL_LED = 0;
    //         SCL_LED = 1;
    //         // RGB_SPI.write(100);
    //       }
    //       // pc.printf("\n" );
    //     }
    //
    //   }
    //
    //   LAT_LED = 1;
    //   LAT_LED = 0;
    //   // LINE = 0;
    //
    //   // if (counter>256){counter = 1;}
    //
    // }
    colorShield.display(pat_2,2);
  }

  return 0;
}
