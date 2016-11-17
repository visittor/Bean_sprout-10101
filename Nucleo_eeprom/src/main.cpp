
#include "mbed.h"
#include "eeprom.h"

EEPROM memory(D14,D15,0);

Serial pc(PA_11,PA_12);

int main()
{

    int8_t data_dummy='r';
    int8_t data[4];
    float x=0.0f,j=9785.26844;
    int16_t y=0x3321,z;

    memory.write(1,(int8_t)data_dummy);
    wait_ms(1);

    memory.write(2,(int8_t)'c');
    wait_ms(1);
    memory.read(1,data,2);
    wait_ms(1);


    memory.write(10,j);
    wait_ms(1);

    memory.read(10,x);
    wait_ms(1);


    memory.write(1,(int16_t)y);
    wait_ms(1);
    memory.read(1,z);
    wait_ms(1);

    pc.printf("read[1] = %c\n",data[0]);
    pc.printf("read[2] = %c\n",data[1]);

    pc.printf("float = %f\n",x);

    pc.printf("int16 =%d\n",z);


}
