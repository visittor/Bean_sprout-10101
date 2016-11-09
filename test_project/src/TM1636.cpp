#include "mbed.h"
#include "TM1636.h"

static int8_t seven_seg_cvt[18] = {0x3f,0x06,0x5b,0x4f,
                         0x66,0x6d,0x7d,0x07,
                         0x7f,0x6f,0x77,0x7c,
                         0x39,0x5e,0x79,0x71,
                         0x40,0x00};

TM1636::TM1636(PinName sda, PinName scl):SDA(sda),SCL(scl){
  // DigitalInOut SDA(sda);
  // DigitalInOut SCL(scl);
  SDA.output();
  SCL.output();
}

void TM1636::init(uint8_t brigthness){
  set(brigthness);
}
void TM1636::set(uint8_t brigthness, uint8_t setdata ,uint8_t setaddr){
  cmd_setdata = setdata;
  cmd_setaddr = setaddr;
  cmd_display = 0x88|brigthness;
}

void TM1636::start(){
  SCL = 1;
  SDA = 1;
  SDA = 0;
  SCL = 0;
}

void TM1636::stop(){
  SDA = 0;
  SCL = 0;
  SCL = 1;
  SDA = 1;
}

void TM1636::writeByte(uint8_t data){
  uint8_t counter = 0;
  for(int i = 0; i<8;i++){
    SCL = 0;
    if(data&0x01){
      SDA = 1;
    }
    else{
      SDA = 0;
    }
    data = data>>1;
    SCL = 1;
    SCL = 0;
  }
  SCL = 0;
  SDA = 1;
  SCL = 1;
  SCL = 0;
  SDA.input();
  while (SDA.read() == 1){
    counter +=1;
    if(counter == 200)//
    {
     SDA.output();

     SDA = 0;
     counter =0;
    }
    SDA.input();
  }
  SDA.output();
}

void TM1636::display(uint8_t data[]){
  start();
  writeByte(ADDR_AUTO);
  stop();
  start();
  writeByte(cmd_setaddr);
  for (int i=0; i<4;i++){
    writeByte(data[i]);
  }
  stop();
  start();
  writeByte(cmd_display);
  stop();
}

void TM1636::display(uint8_t addr ,uint8_t data){
  start();
  writeByte(ADDR_FIXED);
  stop();
  start();
  writeByte(0xc0|data);
  writeByte(data);
  stop();
  start();
  writeByte(cmd_display);
  stop();
}

void TM1636::clearScreen() {
  display(0x00,0x00);
  display(0x01,0x00);
  display(0x02,0x00);
  display(0x03,0x00);
}

uint8_t TM1636::change_to_segment(uint8_t number){
  return seven_seg_cvt[number];
}

void TM1636::change_to_segment(uint8_t number[]){
  for(int i = 0;i < 4; i++){
    number[i] = seven_seg_cvt[number[i]];
  }
}
