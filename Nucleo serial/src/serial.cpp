#include "mbed.h"
#include "ledPatternControl.h"

//------------------------------------
// Hyperterminal configuration
// 9600 bauds, 8-bit data, no parity
//------------------------------------

Serial pc(D8, D2);

DigitalOut myled(LED1);
BusOut led(D3,D9,D10,D11,D12,D13,D14,D15);

int pat_1[16] = {1,2,4,8,16,32,1,2,4,8,16,32,63,0,63,0};
int pat_2[16] = {32,16,8,4,2,1,1,2,4,8,16,32,63,0,63,0};
int pat_3[15] = {63,0,62,60,56,48,32,0,32,48,56,60,62,63,0};
int pat_4[13] = {5,10,20,40,32,40,20,10,5,0,63,0,1};
int pat_5[8] = {129,66,36,24,36,66,129,255};
int pat_6[35] = {1,2,4,8,16,32,64,128,129,130,132,136,160,192,193,194,196,200,208,224,225,226,228,232,240,241,242,244,248,249,250,252,253,254,255};
int pat_7[9] = {255,231,195,129,0,129,195,231,255};
int pat_8[35] = {255,254,253,252,250,249,248,244,242,241,240,232,228,226,225,224,208,200,196,194,193,192,160,136,132,130,129,128,64,32,16,8,4,2,1};

int numPattern = 0;

int main()
{

    uint8_t state_menu=0;
    uint8_t state_show=0;
    uint8_t state_exit =0;
    uint8_t data;
    int showing = 0;

    myled = 0;
    printf("Hello World !\n\n");
    while(1) {
        if(state_show == 0) {
            pc.printf("************\n");
            pc.printf("   Menu   \n");
            pc.printf("************\n");
            pc.printf("1.LED Test\n");
            pc.printf("2.Print Test\n");
            state_show =1;
        }
        if(pc.readable()) {
            data = pc.getc();
            pc.printf("\n");
            state_show =0;
            state_exit =0;

            switch(data) {
                case '1':
                    do {
                            if(state_menu == 0 && showing == 0) {
                                pc.printf("LED Test\n");
                                pc.printf("a.LED ON\n");
                                pc.printf("s.LED OFF\n");
                                pc.printf("x.Exit\n");
                                state_menu = 1;
                            }

                        if(pc.readable()) {
                            data = pc.getc();

                            state_menu=0;
                          }
                            switch(data) {

                                case 'a':
                                    myled = 1;
                                    showing = 1;
                                    show_pattern(pat_4, numPattern, led, 13);
                                    numPattern += 1;
                                    break;

                                case 's':
                                    myled =0;
                                    showing = 1;
                                    show_pattern(pat_7, numPattern, led, 9);
                                    numPattern += 1;
                                    break;
                                case 'd':
                                    myled =0;
                                    showing = 1;
                                    show_pattern(pat_8, numPattern, led, 35);
                                    numPattern += 1;
                                    break;
                                case 'f':
                                    myled =0;
                                    showing = 1;
                                    show_pattern(pat_6, numPattern, led, 35);
                                    numPattern += 1;
                                    break;
                                case 'g':
                                    myled =0;
                                    showing = 1;
                                    show_pattern(pat_5, numPattern, led, 8);
                                    numPattern += 1;
                                    break;
                                case 'h':
                                    myled =0;
                                    showing = 1;
                                    show_pattern(pat_4, numPattern, led, 13);
                                    numPattern += 1;
                                    break;
                                case 'j':
                                    myled =0;
                                    showing = 1;
                                    show_pattern(pat_3, numPattern, led, 15);
                                    numPattern += 1;
                                    break;
                                case 'k':
                                    myled =0;
                                    showing = 1;
                                    show_pattern(pat_2, numPattern, led, 16);
                                    numPattern += 1;
                                    break;
                                case 'l':
                                    myled =0;
                                    showing = 1;
                                    show_pattern(pat_1, numPattern, led, 16);
                                    numPattern += 1;
                                    break;
                                case 'x':
                                    state_exit =1;

                                    break;

                                default:
                                    pc.printf("plz select a or s\n");
                                    pc.printf("\n\n %c",data);
                                    break;
                            }

                    } while(state_exit ==0);

                    pc.printf("\n");
                    break;

                case '2':

                    do {
                        if(state_menu == 0) {
                            pc.printf("Print Test\n");
                            pc.printf("a.Print -Hello-\n");
                            pc.printf("s.Print -Bye Bye-\n");
                            pc.printf("x.Exit\n");
                            state_menu = 1;
                        }
                        if(pc.readable()) {
                            data = pc.getc();
                            pc.printf("\n");
                            state_menu=0;

                            switch(data) {

                                case 'a':
                                    pc.printf("--> Hello <-- \n\n");

                                    break;

                                case 's':
                                    pc.printf("--> Bye Bye <-- \n\n");

                                    break;

                                case 'x':
                                    state_exit =1;


                                    break;

                                default:
                                    pc.printf("plz select a or s\n");
                                    pc.printf("\n");
                                    break;

                            }
                        }
                    } while(state_exit ==0);
                    pc.printf("\n");
                    break;


                case 0x00:

                    break;

                default:
                    pc.printf("plz select 1 or 2 only\n");
                    pc.printf("\n");
                    break;
            }
        }
    }
}
