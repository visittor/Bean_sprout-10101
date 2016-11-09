#include "mbed.h"
#include "selfmpu.h"
#include "TM1636.h"
#include "ds1307.h"

Serial pc(D1,D0);

MPU9555 mpu;

DS1307 ds1307(D14,D15);

// DigitalOut ADO(D7);
// TM1636 tm(D8,D7);
// I2C myi2c(D7,D6);
// DigitalOut pinH(PC_9);
// Serial eiei(PC_6,PA_12);

float gyroBias[3],accBias[3];

int main(int argc, char const *argv[]) {
  // ADO = 1;
  /*Example interface imu*/
  i2c.frequency(400000);

  uint8_t whoami = mpu.readByte(MPU_ADDRESS,WHO_AM_I_MPU9250);
  if (whoami == 0x71) // WHO_AM_I should always be 0x68
  {
    pc.printf("MPU9250 WHO_AM_I is 0x%x\n\r", whoami);
    pc.printf("MPU9250 is online...\n\r");

    mpu.resetMPU();
    mpu.calibrateMPU(gyroBias,accBias);
    pc.printf("gxBias = %f\t",gyroBias[0] );
    pc.printf("gyBias = %f\t",gyroBias[1] );
    pc.printf("gzBias = %f\n",gyroBias[2] );

    pc.printf("axBias = %f\t",accBias[0] );
    pc.printf("axBias = %f\t",accBias[1] );
    pc.printf("axBias = %f\n",accBias[2] );

    wait(2);

    mpu.initial_MPU();
    pc.printf("complete ....\n" );

    wait(2);
  }
  else
   {
    pc.printf("Could not connect to MPU9250: \n\r");
    pc.printf("%#x \n",  whoami);
    while(1);
  }

  while (1) {

    int16_t data[7];
    mpu.readATandG(data);

    float ares = mpu.getAres();
    float gres = mpu.getGres();

    float ax = (float)data[0]*ares - accBias[0];
    float ay = (float)data[1]*ares - accBias[1];
    float az = (float)data[2]*ares - accBias[2]-1;
    // float ax = (float)data[0];
    // float ay = (float)data[1];
    // float az = (float)data[2];
    float T = data[3];
    float gx = (float)data[4]*gres - gyroBias[0];
    float gy = (float)data[5]*gres - gyroBias[1];
    float gz = (float)data[6]*gres - gyroBias[2];

    pc.printf("ax = %f\t",ax );
    pc.printf("ay = %f\t",ay );
    pc.printf("az = %f\n",az );

    pc.printf("gx = %f\t",gx );
    pc.printf("gy = %f\t",gy );
    pc.printf("gz = %f\n",gz );

    wait_ms(500);
}
/**/


/*Example using seven segment on clock shield */
  // uint8_t data[4] = {0x00,0x01,0x02,0x03};
  // tm.change_to_segment(data);
  // tm.init(0x04);
  // while (1) {
  //   tm.display(data);
  //   pc.printf("hello\n");
  //   wait_ms(1);
  // }
/**/
// while (1==1) {
//   char data[1] = {0x01};
//   pinH = 0;
//   pinH = 1;
//   pinH = 0;
//   pinH = 1;
//   myi2c.write(0x90, data, 1,1);
//   eiei.printf("A\n");
//   wait_ms(0.05);
// }

/*Example using realtime clock*/
  // ds1307.twentyfour_hour();
  // ds1307.start_clock();
  // while(1==1){
  //   int sec[1];
  //   int min[1];
  //   int hour[1];
  //   int day[1];
  //   int *date;
  //   int *month;
  //   int *year;
  //   int test = ds1307.gettime(sec,min,hour,day,date,month,year);
  //   printf("%d,%d,%d,test:%d\n",sec[0],min[0],hour[0],test);
  // }


  return 0;
}
