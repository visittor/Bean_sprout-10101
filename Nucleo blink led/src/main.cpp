//lab GPIO 1-1 output

#include "mbed.h"

DigitalOut myled(LED1);
BusIn mysw(D5, D4, D3);

int main() {
    while(1) {
        myled = 1; // LED is ON
        wait(.1); // 200 ms
        myled = 0; // LED is OFF
        wait(.1); // 1 sec
    }
}

//lab GPIO 1-2 output2

/*
#include "mbed.h"

DigitalOut myled(LED1);
DigitalOut myled2(D12);
Timer t;

int main()
{
    t.start();
    while(1) {
        if(t.read_ms() <100) {
            myled = 1; // LED is ON
            myled2= 1;
        } else if(t.read_ms() <400) {
            myled = 0; // LED is OFF}
            myled2= 1;
        } else if(t.read_ms() <800)
        {
            myled = 0; // LED is OFF}
            myled2= 0;
            }
        else{
            t.reset();
        }

    }
}
*/

// lab GPIO 1-3input and output
/*
#include "mbed.h"

DigitalOut myled(LED1);
DigitalIn mybutton(USER_BUTTON);

int main()
{
    while(1) {

        if(mybutton == 0) {
            myled = 1; // LED is ON
        } else {
            myled = 0; // LED is OFF
        }
    }
}
*/

//lab GPIO 1-4 input state
/*
#include "mbed.h"

DigitalOut myled(LED1);
DigitalOut myled2(D12);

DigitalIn mybutton(USER_BUTTON);

Timer t;

int main()
{
    int state=0;
    int timer_delay1=100,timer_delay2=200;
    t.start();
    while(1) {

        if(mybutton == 0) {
        //    wait_ms(10)
            while(mybutton !=1) ;

            if(state <2) {
                state++;
            } else {
                state =0;
            }

        }

        if(state == 0) {
            timer_delay1 =100;
            timer_delay2 =200;
        } else if(state ==1) {
            timer_delay1 =100;
            timer_delay2 =500;
        } else if(state ==2) {
            timer_delay1 =500;
            timer_delay2 =1000;
        }

        if(t.read_ms() <timer_delay1) {
            myled = 1; // LED is ON
            myled2= 0;
        } else if(t.read_ms() <timer_delay2) {
            myled = 0; // LED is OFF}
            myled2= 1;
        } else {
            t.reset();
        }

    }
}
*/
