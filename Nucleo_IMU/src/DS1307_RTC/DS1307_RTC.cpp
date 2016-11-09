// J Bradshaw
// 20141010 - I2C Real Time Clock

#include "DS1307_RTC.h"

#define YEAR_OFFSET 2000

DS1307_RTC::DS1307_RTC(PinName sda, PinName scl) : _i2c(sda, scl)
{
    _i2c.frequency(400000);
    
/*    Day[] = {"","Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
    Mon[] = {"","Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};*/
  
  /*
    Day[0] = "";
    Day[1] = "Sun";
    Day[2] = "Mon";
    Day[3] = "Tue";
    Day[4] = "Wed";
    Day[5] = "Thu";
    Day[6] = "Fri";
    Day[7] = "Sat";
    
    Mon[0] = "";
    Mon[1] = "Jan";
    Mon[2] = "Feb";
    Mon[3] = "Mar";
    Mon[4] = "Apr";
    Mon[5] = "May";
    Mon[6] = "Jun";
    Mon[7] = "Jul";
    Mon[8] = "Aug";
    Mon[9] = "Sep";
    Mon[10] = "Oct";
    Mon[11] = "Nov";
    Mon[12] = "Dec";
    */
       
    rtc_sec = 0;
    rtc_minute = 0;
    rtc_hours = 0;
    rtc_day = 0;
    rtc_date = 0;
    rtc_month = 0;
    rtc_year = 0;
}

//function for writing to RTC registers
void DS1307_RTC::RTC_write_reg(int reg, int val)
{
    char cmd[3];
    cmd[0] = reg;
    cmd[1] = val & 0xFF;
    
    _i2c.write(DS1307_addr, cmd, 2); 
}

int DS1307_RTC::RTC_read_reg(char reg)
{
    char byte_read[2];
    
    if(_i2c.write(DS1307_addr, &reg, 1))  //tell the RTC which reg
        printf("\r\nDS1307 - Error sending address!\0");    
  
    if(_i2c.read(DS1307_addr, byte_read, 1))  //read one byte
        printf("\r\nDS1307 - Error reading!\0"); 
    return byte_read[0];  
}

int DS1307_RTC::bcd(int dec)
{
    return ((dec/10)<<4) + (dec%10);
}

int DS1307_RTC::unbcd(int bcd)
{
    return ((bcd>>4)*10) + bcd%16;
}

void DS1307_RTC::set_RTC_time(void)
{
    printf("\r\n\r\nSet the Real Time Clock.\r\nEnter Year and press Enter...\r\n");        
    scanf("%d",&rtc_year);           //Read year
    RTC_write_reg(6, bcd(rtc_year));    //seconds reg
    printf("%d\r\n",rtc_year + YEAR_OFFSET); //print year    

    printf("Enter Month and press Enter...\r\n");        
    scanf("%d",&rtc_month);          //Read month
    RTC_write_reg(5, bcd(rtc_month));   //month reg
    printf("%d\r\n",rtc_month);      //print month    

    printf("Enter Day (Sun=1,Mon=2,Tues=3,etc...) and press Enter...\r\n");        
    scanf("%d",&rtc_day);          //Read day
    RTC_write_reg(3, bcd(rtc_day));   //day reg
    printf("%d\r\n",rtc_day);      //print day
    
    printf("Enter Date and press Enter...\r\n");        
    scanf("%d",&rtc_date);          //Read date
    RTC_write_reg(4, bcd(rtc_date));   //date reg
    printf("%d\r\n",rtc_date);      //print date

    printf("Enter hours and press Enter...\r\n");        
    scanf("%d",&rtc_hours);          //Read hour
    RTC_write_reg(2, bcd(rtc_hours));   //hour reg
    printf("%d\r\n",rtc_hours);      //print hour

    printf("Enter Minutes and press Enter...\r\n");        
    scanf("%d",&rtc_minute);          //Read minute
    RTC_write_reg(1, bcd(rtc_minute));   //minute reg
    printf("%d\r\n",rtc_minute);      //print minute
        
    printf("Enter seconds and press Enter...\r\n");        
    scanf("%d",&rtc_sec);    //Read sec
    printf("%d\r\n",rtc_sec); //print sec
    RTC_write_reg(0, bcd(rtc_sec));     //seconds reg
}

void DS1307_RTC::set_RTC_time_UTC(float utc_time, int timezone){
    int Hour = (int)((int)utc_time/10000) + timezone;
    if(Hour < 0)
        Hour += 24;
    
    int Min = (int)((int)utc_time/100%100);
    int Sec = (int)utc_time % 100;
            
/*    RTC_write_reg(6, bcd(rtc_year));    //seconds reg
    RTC_write_reg(5, bcd(rtc_month));   //month reg
    RTC_write_reg(3, bcd(rtc_day));   //day reg
    RTC_write_reg(4, bcd(rtc_date));   //date reg*/
    
    RTC_write_reg(2, bcd(Hour));   //hour reg    
    RTC_write_reg(1, bcd(Min));   //minute reg
    RTC_write_reg(0, bcd(Sec));     //seconds reg    
}

void DS1307_RTC::get_RTC_time(char *str)
{   
    rtc_sec = unbcd(RTC_read_reg(0));    //
    rtc_minute = unbcd(RTC_read_reg(1));
    rtc_hours = unbcd(RTC_read_reg(2));
    rtc_day = unbcd(RTC_read_reg(3));
    if(rtc_day > 7)
        rtc_day = 0;
    rtc_date = unbcd(RTC_read_reg(4));
    rtc_month = unbcd(RTC_read_reg(5));
    if(rtc_month > 12)
        rtc_month = 0;
    rtc_year = unbcd(RTC_read_reg(6)) + YEAR_OFFSET;
    
    sprintf(str, "%2d:%02d:%02d", rtc_hours,rtc_minute,rtc_sec);
    //sprintf(str, "%2d:%02d:%02d %s %s %d %d", rtc_hours,rtc_minute,rtc_sec,Day[rtc_day],Mon[rtc_month], rtc_date, rtc_year);
    //pc.printf("%s", str);
}
