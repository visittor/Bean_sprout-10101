
#include "mbed.h"
#include "MCP4922.h"

MCP4922 MCP(SPI_MOSI, SPI_SCK,SPI_CS);  // MOSI, SCLK, CS


/**** Main Function  ***/
int main(void)
{
    MCP.frequency(20000000);

    uint16_t i=0;
    uint8_t state=0;
    while(1) {
        if(i < 0x0FFE) {
            i++;

        } else {
            i=0;
            state = ~state;
        }

        if(state ==0) {
            MCP.writeA(i);
        } else {
            MCP.writeA( ((~i)+1)&0x0FFF);
        }
        wait_us(1);
    }
}