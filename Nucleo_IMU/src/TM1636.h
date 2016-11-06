#ifndef TM1636_h
#define TM1636_h

//************definitions for TM1636*********************
#define ADDR_AUTO  0x40
#define ADDR_FIXED 0x44

#define STARTADDR  0xc0
/**** definitions for the clock point of the digit tube *******/
#define POINT_ON   1
#define POINT_OFF  0
/**************definitions for brightness***********************/
#define  BRIGHT_DARKEST 0
#define  BRIGHT_TYPICAL 2
#define  BRIGHTEST      7

//--------------------------------------------------------//
//Special characters index of tube table
#define INDEX_NEGATIVE_SIGN	16
#define INDEX_BLANK			17

#include "mbed.h"

class TM1636 {

public:
  uint8_t cmd_setdata;
  uint8_t cmd_setaddr;
  uint8_t cmd_display;
  // DigitalInOut SDA;
  // DigitalInOut SCL;
  TM1636(PinName ,PinName );
  void init(uint8_t brigthness);
  void set(uint8_t brigthness, uint8_t setdata = 0x40 ,uint8_t setaddr = 0xc0);
  void start(void);
  void stop(void);
  void writeByte(uint8_t data);
  void display(uint8_t data[]);
  void display(uint8_t addr, uint8_t data);
  void clearScreen(void);
  uint8_t change_to_segment(uint8_t number);
  void change_to_segment(uint8_t number[]);

private:
  DigitalInOut SDA;
  DigitalInOut SCL;
};

#endif
