#include "mbed.h"
#include "colorShield.h"
#include "selfmpu.h"

uint8_t wall[3] = {0,25,25};
uint8_t path[3] = {0,0,0};
uint8_t character[3] = {255,255,0};
Serial pc(D1,D0);
Color_shield color_s;
MPU9555 mpu;

float gyroBias[3],accBias[3];

int frameCountx = 0;
int frameCounty = 0;
int centerNow[2] = {3,3};
int previousCenter[2] = {3,3};
int mapsize[2] = {48,48};
uint8_t *output[8][8];

uint8_t *Bigmap[48][48] = {
                            {wall,path,path,path,wall,wall,wall,wall,path,path,wall,wall,wall,wall,wall,wall,wall,path,wall,wall,wall,wall,wall,wall,wall,path,path,path,wall,wall,path,path,path,wall,path,wall,wall,wall,wall,path,path,wall,path,path,path,wall,path,path},
                            {wall,path,path,path,wall,path,path,wall,path,path,wall,path,path,path,path,path,wall,path,path,path,path,path,wall,wall,wall,path,path,path,wall,wall,path,path,path,wall,path,path,path,path,path,path,path,wall,path,path,path,wall,path,path},
                            {wall,path,path,path,wall,path,path,wall,path,path,wall,path,path,path,path,path,wall,path,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,path,path,path,wall,wall,wall,wall,wall,wall,wall,wall,wall,path,path,path,wall,path,path},
                            {wall,path,path,path,wall,path,path,wall,path,path,wall,path,path,wall,path,path,wall,path,wall,wall,wall,wall,wall,path,path,wall,wall,wall,wall,wall,path,path,path,wall,path,path,path,path,path,path,path,path,path,path,path,wall,path,path},
                            {wall,path,path,path,wall,path,path,wall,path,path,wall,path,path,wall,path,path,wall,path,path,path,path,path,path,path,path,wall,wall,path,path,path,path,path,path,wall,path,path,path,path,path,path,path,path,path,path,path,wall,path,path},
                            {path,path,path,path,wall,path,path,wall,path,path,wall,path,path,wall,path,path,wall,wall,wall,wall,wall,wall,wall,path,path,wall,wall,path,path,path,path,path,path,wall,path,path,path,path,path,path,path,path,path,path,path,wall,path,path},
                            {path,path,path,path,wall,path,path,wall,path,path,wall,path,path,wall,path,path,path,path,path,path,path,wall,wall,path,path,wall,wall,path,path,path,path,path,path,wall,path,path,path,wall,wall,wall,wall,wall,wall,path,path,wall,path,path},
                            {path,path,path,path,wall,path,path,wall,path,path,wall,path,path,wall,path,path,path,path,path,path,path,wall,wall,path,path,wall,wall,path,path,path,wall,wall,wall,wall,path,path,path,wall,path,path,path,path,wall,path,path,wall,path,path},
                            {wall,wall,wall,wall,wall,path,path,wall,path,path,wall,path,path,wall,wall,wall,wall,wall,wall,wall,path,wall,wall,path,path,wall,wall,path,path,path,wall,wall,wall,wall,path,path,path,wall,path,wall,wall,path,wall,path,path,wall,wall,wall},
                            {path,path,path,path,path,path,path,wall,path,path,wall,path,path,wall,path,path,path,path,path,path,path,path,path,path,path,path,wall,path,path,path,wall,wall,wall,wall,path,path,path,wall,path,wall,wall,path,wall,path,path,path,path,path},
                            {path,path,path,path,path,path,path,wall,path,path,wall,path,path,wall,wall,wall,wall,wall,wall,path,wall,wall,wall,wall,wall,wall,wall,path,path,path,wall,wall,wall,wall,path,path,path,wall,path,wall,wall,path,wall,path,path,path,path,path},
                            {wall,wall,wall,wall,wall,wall,wall,wall,path,path,wall,path,path,path,path,path,path,wall,wall,path,wall,wall,path,path,path,path,wall,path,path,path,path,path,path,path,path,path,path,wall,path,wall,wall,path,wall,path,path,wall,wall,wall},
                            {path,path,path,path,path,path,path,path,path,path,wall,path,path,path,path,path,path,wall,wall,wall,wall,wall,path,path,path,path,wall,path,path,path,path,path,path,path,path,path,path,wall,path,wall,path,path,wall,path,path,wall,path,path},
                            {wall,wall,wall,wall,wall,wall,wall,wall,path,path,wall,wall,path,wall,path,path,path,path,path,path,path,wall,path,path,wall,path,wall,path,path,path,path,path,path,path,path,path,path,wall,path,wall,wall,wall,wall,wall,wall,wall,wall,wall},
                            {path,path,path,path,path,path,path,path,path,path,wall,wall,path,wall,path,path,path,path,path,path,path,wall,path,path,wall,path,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,path,path,path,path,path,path,path,path,path,path},
                            {path,path,path,path,path,path,path,path,path,path,wall,wall,path,wall,path,path,path,path,path,path,path,wall,path,path,wall,path,wall,wall,wall,wall,wall,wall,wall,path,path,path,path,wall,path,path,path,path,path,path,path,path,path,path},
                            {wall,wall,wall,wall,wall,path,path,wall,wall,wall,wall,wall,path,wall,path,path,path,wall,wall,wall,wall,wall,path,path,wall,path,path,path,path,path,path,path,path,path,path,path,path,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall},
                            {wall,wall,wall,wall,wall,path,path,wall,wall,wall,wall,wall,path,wall,path,path,path,wall,wall,wall,wall,wall,path,path,wall,wall,wall,wall,wall,path,path,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall},
                            {path,wall,path,path,path,path,path,wall,path,path,path,path,path,wall,path,path,path,wall,path,path,path,path,path,path,path,path,wall,path,wall,path,path,wall,path,path,path,path,path,path,path,path,path,path,path,path,path,path,path,path},
                            {path,wall,path,path,path,path,path,wall,wall,wall,wall,wall,wall,wall,path,path,path,wall,path,path,path,path,path,path,path,path,wall,path,wall,path,path,wall,path,path,path,path,path,path,path,path,path,path,path,path,path,path,path,path},
                            {path,wall,path,path,path,path,path,path,path,path,path,path,path,path,path,path,path,wall,path,path,path,path,path,path,path,path,wall,path,wall,path,path,wall,path,path,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,path},
                            {wall,wall,wall,wall,wall,path,path,path,path,path,path,path,path,path,path,path,path,wall,path,path,path,wall,wall,wall,path,path,wall,path,wall,path,path,wall,path,path,wall,path,path,path,path,path,path,path,path,path,path,path,wall,path},
                            {path,path,path,path,wall,path,path,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,path,path,path,wall,wall,wall,path,path,wall,path,path,path,path,wall,path,path,wall,path,path,path,path,path,path,path,path,path,path,path,wall,path},
                            {path,path,path,path,wall,path,path,wall,wall,path,path,path,path,path,path,path,path,path,path,path,path,wall,wall,wall,path,path,wall,path,path,path,path,wall,path,path,wall,path,path,path,path,path,path,path,path,path,path,path,wall,path},
                            {path,path,path,path,wall,path,path,wall,wall,path,path,path,path,path,path,path,path,path,path,path,path,wall,wall,wall,path,path,wall,wall,wall,wall,wall,wall,path,path,wall,path,path,path,wall,path,path,wall,wall,wall,path,path,wall,path},
                            {wall,path,path,path,wall,path,path,wall,wall,path,path,path,path,path,path,path,path,path,path,path,path,wall,wall,wall,path,path,path,path,path,path,path,path,path,path,wall,path,path,path,wall,path,path,path,path,wall,path,path,wall,wall},
                            {wall,path,path,path,wall,path,path,wall,wall,path,path,path,wall,wall,path,path,path,wall,wall,wall,wall,wall,wall,wall,path,path,path,path,path,path,path,path,path,path,wall,path,path,path,wall,path,path,wall,path,wall,path,path,wall,wall},
                            {wall,path,path,path,wall,path,path,wall,wall,path,path,path,wall,wall,path,path,path,wall,wall,wall,wall,wall,wall,wall,path,path,path,path,path,path,path,path,path,path,wall,path,path,path,wall,path,path,wall,path,wall,path,path,wall,wall},
                            {wall,path,path,path,wall,path,path,path,path,path,path,path,wall,wall,path,path,path,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,path,path,path,wall,path,path,wall,path,wall,path,path,wall,wall},
                            {wall,path,path,path,wall,path,path,path,path,path,path,path,wall,wall,path,path,path,wall,wall,path,path,path,path,path,path,path,path,path,path,path,path,path,path,path,path,path,path,path,wall,path,path,wall,path,wall,path,path,wall,wall},
                            {wall,path,path,path,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,path,path,path,wall,wall,path,path,path,path,path,path,path,path,path,path,path,path,path,path,path,path,path,path,path,wall,path,path,wall,path,wall,path,path,wall,wall},
                            {path,path,path,path,wall,path,path,path,path,path,path,path,path,path,path,path,path,wall,wall,path,path,path,path,path,path,path,path,path,path,path,path,path,path,path,path,path,path,path,wall,path,path,wall,path,wall,path,path,path,path},
                            {path,path,path,path,wall,path,path,path,path,path,path,path,path,path,path,path,path,wall,wall,path,path,path,wall,wall,wall,path,path,path,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,path,path,wall,path,wall,path,path,path,path},
                            {wall,wall,path,path,wall,path,path,path,path,path,path,path,path,path,path,path,path,wall,wall,path,path,path,wall,wall,wall,path,path,path,wall,path,path,path,path,path,path,path,path,path,path,path,path,wall,path,wall,wall,wall,wall,wall},
                            {path,wall,path,path,wall,wall,wall,wall,path,wall,wall,wall,path,path,path,wall,wall,wall,wall,path,path,path,wall,wall,wall,path,path,path,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,path,path,wall,path,path,path,path,path,path},
                            {wall,wall,wall,wall,wall,wall,wall,wall,path,path,path,wall,path,path,path,wall,wall,wall,wall,path,path,path,wall,wall,wall,path,path,path,path,path,path,path,path,path,path,path,path,path,wall,path,path,wall,wall,wall,wall,wall,wall,wall},
                            {path,path,path,path,path,path,path,wall,path,wall,path,wall,path,path,path,wall,wall,wall,wall,path,path,path,wall,wall,wall,path,path,path,path,path,path,path,path,path,path,path,path,path,wall,path,path,wall,wall,path,path,path,path,path},
                            {path,path,path,path,path,path,path,wall,path,wall,path,wall,path,path,path,wall,wall,wall,wall,path,path,path,wall,wall,wall,path,path,path,path,path,path,path,path,path,path,path,path,path,wall,path,path,wall,wall,path,path,path,path,path},
                            {path,path,path,path,path,path,path,wall,path,wall,path,wall,path,path,path,wall,wall,wall,wall,path,path,path,wall,wall,wall,wall,wall,wall,wall,wall,path,path,path,wall,wall,path,path,path,wall,path,path,wall,wall,path,path,path,path,path},
                            {wall,wall,wall,wall,path,path,path,wall,path,wall,path,wall,path,path,path,path,path,path,path,path,path,path,path,path,path,path,path,path,wall,wall,path,path,path,wall,wall,path,path,path,wall,path,path,wall,wall,wall,wall,wall,wall,wall},
                            {path,path,path,wall,path,path,path,wall,path,wall,path,wall,wall,wall,path,path,path,path,path,path,path,path,path,path,path,path,path,path,wall,wall,path,path,path,wall,wall,path,path,path,wall,path,path,wall,path,path,path,path,path,path},
                            {path,path,path,wall,path,path,path,wall,path,wall,path,wall,wall,wall,path,path,path,path,path,path,path,path,path,path,path,path,path,path,wall,wall,path,path,path,wall,wall,path,path,path,wall,path,path,wall,path,path,path,path,path,path},
                            {path,path,path,wall,path,path,path,wall,path,wall,path,path,path,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,path,path,path,wall,wall,path,path,path,wall,wall,path,path,path,wall,path,path,wall,path,path,path,path,path,path},
                            {wall,wall,wall,wall,path,path,path,wall,wall,wall,wall,wall,path,path,path,path,path,path,path,path,path,path,path,path,wall,path,path,path,wall,wall,path,path,path,wall,wall,path,path,path,wall,path,path,wall,path,path,path,wall,wall,wall},
                            {path,path,path,path,path,path,path,path,path,path,path,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,path,path,path,wall,wall,path,path,path,wall,wall,path,path,path,wall,path,path,wall,path,path,path,wall,path,path},
                            {path,path,path,path,path,path,path,path,path,path,path,wall,path,path,path,path,path,path,path,path,path,path,path,path,path,path,path,path,wall,wall,path,path,path,wall,wall,path,path,path,wall,path,path,wall,path,path,path,wall,path,path},
                            {path,path,path,path,path,path,path,path,path,path,path,wall,path,path,path,path,path,path,path,path,path,path,path,path,path,path,path,path,wall,wall,path,path,path,wall,wall,path,path,path,wall,path,path,wall,path,path,path,wall,path,path},
                            {wall,path,path,path,wall,wall,wall,wall,path,path,wall,wall,path,path,path,path,path,path,path,path,path,path,path,path,path,path,path,path,wall,wall,path,path,path,wall,wall,wall,wall,wall,wall,path,path,wall,path,path,path,wall,path,path},
                          };

uint8_t *map[8][8] = {{wall,wall,wall,path,path,wall,wall,wall},
                      {wall,wall,wall,path,path,wall,wall,wall},
                      {wall,wall,wall,path,path,wall,wall,wall},
                      {path,path,path,path,path,path,path,path},
                      {path,path,path,path,path,path,path,path},
                      {wall,wall,wall,path,path,wall,wall,wall},
                      {wall,wall,wall,path,path,wall,wall,wall},
                      {wall,wall,wall,path,path,wall,wall,wall}};

uint8_t *map2[8][8] = {{wall,wall,wall,path,path,wall,wall,wall},
                      {wall,wall,wall,path,path,wall,wall,wall},
                      {wall,wall,wall,path,path,wall,wall,wall},
                      {path,path,path,path,path,path,path,path},
                      {path,path,path,path,path,path,path,path},
                      {wall,wall,wall,path,path,wall,wall,wall},
                      {wall,wall,wall,path,path,wall,wall,wall},
                      {wall,wall,wall,path,path,wall,wall,wall}};

  uint8_t pat_1[8][8][3] ={     {{0,28,3},{0,26,5},{0,24,7},{0,22,9},{0,20,11},{0,18,12},{0,16,14},{0,14,16}},
                                {{0,26,5},{0,24,7},{0,22,9},{0,20,11},{0,18,12},{0,16,14},{0,14,16},{0,12,18}},
                                {{0,24,7},{0,22,9},{0,20,11},{0,18,12},{0,16,14},{0,14,16},{0,12,18},{0,10,20}},
                                {{0,22,9},{0,20,11},{0,18,12},{0,16,14},{0,14,16},{0,12,18},{0,10,20},{0,8,22}},
                                {{0,20,11},{0,18,12},{0,16,14},{0,14,16},{0,12,18},{0,10,20},{0,8,22},{0,6,24}},
                                {{0,18,12},{0,16,14},{0,14,16},{0,12,18},{0,10,20},{0,8,22},{0,6,24},{0,4,26}},
                                {{0,16,14},{0,14,16},{0,12,18},{0,10,20},{0,8,22},{0,6,24},{0,4,26},{0,2,28}},
                                {{0,30,0},{0,28,3},{0,26,5},{0,24,7},{0,22,9},{0,20,11},{0,18,12},{0,16,14}},
                          };



uint8_t pat_2[8][8][3] ={     {{25,0,1},{25,0,3},{25,0,5},{25,0,7},{25,0,9},{25,0,10},{25,0,12},{25,0,14}},
                              {{25,0,3},{25,0,5},{25,0,7},{25,0,9},{25,0,10},{25,0,12},{25,0,14},{25,0,16}},
                              {{25,0,5},{25,0,7},{25,0,9},{25,0,10},{25,0,12},{25,0,14},{25,0,16},{25,0,18}},
                              {{25,0,7},{25,0,9},{25,0,10},{25,0,12},{25,0,14},{25,0,16},{25,0,18},{25,0,19}},
                              {{25,0,9},{25,0,10},{25,0,12},{25,0,14},{25,0,16},{25,0,18},{25,0,19},{25,0,20}},
                              {{25,0,10},{25,0,12},{25,0,14},{25,0,16},{25,0,18},{25,0,19},{25,0,20},{25,0,22}},
                              {{25,0,12},{25,0,14},{25,0,16},{25,0,18},{25,0,19},{25,0,20},{25,0,22},{25,0,24}},
                              {{25,0,0},{25,0,1},{25,0,3},{25,0,5},{25,0,7},{25,0,9},{25,0,10},{25,0,12}},
                          };
uint8_t pat_3[8][8][3] ={     {{21,0,0},{17,0,0},{13,0,0},{9,13,0},{5,17,0},{1,21,0},{0,25,0},{0,21,1}},
                              {{17,0,0},{13,0,0},{9,13,0},{5,17,0},{1,21,0},{0,25,0},{0,21,1},{0,17,5}},
                              {{13,0,0},{9,13,0},{5,17,0},{1,21,0},{0,25,0},{0,21,1},{0,17,5},{0,13,9}},
                              {{9,13,0},{5,17,0},{1,21,0},{0,25,0},{0,21,1},{0,17,5},{0,13,9},{0,0,13}},
                              {{5,17,0},{1,21,0},{0,25,0},{0,21,1},{0,17,5},{0,13,9},{0,0,13},{0,0,17}},
                              {{1,21,0},{0,25,0},{0,21,1},{0,17,5},{0,13,9},{0,0,13},{0,0,17},{0,0,21}},
                              {{0,25,0},{0,21,1},{0,17,5},{0,13,9},{0,0,13},{0,0,17},{0,0,21},{0,0,25}},
                              {{25,0,0},{21,0,0},{17,0,0},{13,0,0},{9,13,0},{5,17,0},{1,21,0},{0,25,0}},
                          };
void random_spawn(int *ran_res,int max_x,int min_x,int max_y,int min_y){
  int x_axis = rand()%(max_x-min_x+1)+(min_x-1);
  int y_axis = rand()%(max_y-min_y+1)+(min_y-1);
  ran_res[0] = x_axis;
  ran_res[1] = y_axis;
  pc.printf("%d %d\n",ran_res[0],ran_res[1]);

}

void moveMap(uint8_t* map[48][48],int nextCenter[2],int mapsize[2],uint8_t* output[8][8]){
  int row,column;
  for (int i=0;i<8;i++){
    for(int j=0;j<8;j++){
      row = (nextCenter[1]%48)-3+i;
      column = (nextCenter[0]%48)-3+j;
      if (row>=0 && row<mapsize[0]){}
      else if(row<0){row = mapsize[0]+(row%49);}
      else if(row>=mapsize[0]){row = row%48;}
      if(column>=0 && column<mapsize[1]){}
      else if(column<0){column = mapsize[1]+(column%49);}
      else if(column>=mapsize[1]){column = column%48;}
      output[i][j] = map[row][column];
    }
  }
  output[3][3] = character;
}

int main(int argc, char const *argv[]) {
  MPU_ADDRESS = 0x68<<1;

  i2c.frequency(400000);
  color_s.init();
  uint8_t whoami = mpu.readByte(MPU_ADDRESS,WHO_AM_I_MPU9250);
  if (whoami == 0x71) // WHO_AM_I should always be 0x68
  {
    pc.printf("MPU9250 WHO_AM_I is 0x%x\n\r", whoami);
    pc.printf("MPU9250 is online...\n\r");
    color_s.display(pat_3,4);
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
     color_s.display(pat_2,4);
    pc.printf("Could not connect to MPU9250: \n\r");
    pc.printf("%#x \n",  whoami);
    while(1);
  }
  int ran_res_eiei[2];
  srand(time(NULL));
  while(1){
    random_spawn(ran_res_eiei,48,8,48,8);
    centerNow[0] = ran_res_eiei[0];
    centerNow[1] = ran_res_eiei[1];
    if (Bigmap[centerNow[1]][centerNow[0]][0]==wall[0] && Bigmap[centerNow[1]][centerNow[0]][1]==wall[1] && Bigmap[centerNow[1]][centerNow[0]][2]==wall[2]){
    }
    else{
      break;
    }
  }
  pc.printf("%d %d\n",centerNow[0],centerNow[1] );




  while(1){
    int16_t data[7];
    mpu.readATandG(data);
    float ares = mpu.getAres();
    float ax = (float)data[0]*ares - accBias[0];
    float ay = (float)data[1]*ares - accBias[1];
    // pc.printf("ax = %f\t",ax );
    // pc.printf("ay = %f\t\n",ay );
    // pc.printf("az = %f\n",az );
    // pc.printf("%i \n",rand()%100 + 1);



    if (ay<0.2 && ay>-0.2){}
    else if (ay>0){
      if(frameCounty >= 150-(int)(ay*100)){
        centerNow[1]++;
        centerNow[1] = centerNow[1]%48;
        frameCounty = 0;
      }
    }
    else if(ay<=0){
      if(frameCounty >= 150+(int)(ay*100)){
        centerNow[1]--;
        if (centerNow[1]<0){centerNow[1] = 48+(centerNow[1]%49);}
        else{centerNow[1] = centerNow[1]%48;}
        frameCounty = 0;
      }
    }
    if (ax<0.2 && ax>-0.2){}
    else if (ax>0){
      if(frameCountx >= 150-(int)(ax*100)){
        // pc.printf("%d\n", 150-(int)(ax*200));
        centerNow[0]++;
        centerNow[0] = centerNow[0]%48;
        frameCountx = 0;
      }
    }
    else if(ax<=0){
      if(frameCountx >= 150+(int)(ax*100)){
        // pc.printf("%d\n", 150+(int)(ax*200));
        centerNow[0]=centerNow[0]-1;
        if (centerNow[0]<0){centerNow[0] = 48+(centerNow[0]%49);}
        else{centerNow[0] = centerNow[0]%48;}
        frameCountx = 0;
      }
    }
    if (Bigmap[centerNow[1]][centerNow[0]][0]==wall[0] && Bigmap[centerNow[1]][centerNow[0]][1]==wall[1] && Bigmap[centerNow[1]][centerNow[0]][2]==wall[2]){
      centerNow[0] = previousCenter[0];
      centerNow[1] = previousCenter[1];
    }
    // centerNow[0] = 19;
    // centerNow[1] = 19;
    // pc.printf("%d %d\n",centerNow[0],centerNow[1] );
    moveMap(Bigmap,centerNow,mapsize,output);
    color_s.display(output,8);
    frameCountx= (frameCountx+1)%500;
    frameCounty= (frameCounty+1)%500;
    previousCenter[0] = centerNow[0];
    previousCenter[1] = centerNow[1];
  }
  return 0;
}
