#include "mbed.h"

//------------------------------------
// Hyperterminal configuration
// 9600 bauds, 8-bit data, no parity
//------------------------------------

Serial pc(D8, D2);

DigitalOut myled(LED1);

int main()
{

    uint8_t state_menu=0;
    uint8_t state_show=0;
    uint8_t state_exit =0;
    uint8_t data;

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
                            if(state_menu == 0) {
                                pc.printf("LED Test\n");
                                pc.printf("a.LED ON\n");
                                pc.printf("s.LED OFF\n");
                                pc.printf("x.Exit\n");
                                state_menu = 1;
                            }

                        if(pc.readable()) {
                            data = pc.getc();
                            pc.printf("\n");
                            state_menu=0;

                            switch(data) {

                                case 'a':
                                    myled = 1;
                                    break;

                                case 's':
                                    myled =0;

                                    break;

                                case 'x':
                                    state_exit =1;

                                    break;

                                default:
                                    pc.printf("plz select a or s\n");
                                    pc.printf("\n\n");
                                    break;
                            }
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
