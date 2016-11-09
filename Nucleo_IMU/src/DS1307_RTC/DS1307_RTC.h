
#ifndef DS1307_RTC_H
#define DS1307_RTC_H

#include "mbed.h"

#define DS1307_addr 0xd0

#define YEAR_OFFSET 2000

class DS1307_RTC{
public:
    DS1307_RTC(PinName sda, PinName scl);
    
    void RTC_write_reg(int reg, int val);
    int RTC_read_reg(char reg);
    int bcd(int dec);
    int unbcd(int bcd);
    void set_RTC_time(void);
    void set_RTC_time_UTC(float utc_time, int timezone);
    void get_RTC_time(char *str);        

//    char  *Day[];
//    char  *Mon[];
     
    int rtc_sec;
    int rtc_minute;
    int rtc_hours;
    int rtc_day;
    int rtc_date;
    int rtc_month;
    int rtc_year;
    
private:
    I2C _i2c;  
        
};

#endif /* DS1307_RTC_H */
