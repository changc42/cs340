/*
this assignment makes you want to never look at C++ again. there are so many confusing things like void*, and casting. 

Compile this code in standard fashion. 
g++ Assignment2.cpp
./a.out

output is the minimum calculated using the threads, and a minimum calculated using only the main process. There are two methods of calculating minimum to check validity of output.

I used structs to pass data between threads. The main process passes a struct to the 5 level 1 threads. Then, each level1 thread passes a struct to each of its 20 threads. The lower level threads will modify the structs passed to them, and the higher level threads will be aware of those changes.

*/


#include<iostream>
#include<stdlib.h>
#include<ctime>
#include<pthread.h>
#include<stdio.h>
#include<climits>
#include<algorithm>
#include<time.h>

using namespace std;

//declare array of randnums of size 10,000
const int AMOUNT_OF_NUMS = 10'000;
int randnums [AMOUNT_OF_NUMS];

//each struct will be passed to a thread via pthread_create
struct Level1Params{
  int min;
  int mins[20];
  int numsSlice[2000];
};

struct Level2Params{
  int min;
  int numsSlice[100];
};

//the starter_function which the threads will execute
//each function calculates min of given numbers and stores back in struct
void* level2Func(void* param){
  Level2Params* myLevel2Param = (Level2Params*)param;
  myLevel2Param->min = *min_element(myLevel2Param->numsSlice,myLevel2Param->numsSlice+100);
  printf("min of level2param[%p]: %d\n",(void*)myLevel2Param, myLevel2Param->min);
  pthread_exit(0);
}

void* level1Func(void* param){
  Level1Params* myLevel1Param = (Level1Params*)param;
  pthread_t tids[20];
  pthread_attr_t attrs[20];

  Level2Params level2ParamsArr[20];

  for(int i=0; i<20; i++){
    for(int j=i*100; j<i*100+100; j++){
      level2ParamsArr[i].numsSlice[j-(i*100)]=myLevel1Param->numsSlice[j];
    }
    pthread_attr_init(&attrs[i]);
    pthread_create(&tids[i], &attrs[i], level2Func, &level2ParamsArr[i]);
    pthread_join(tids[i], NULL);
  }
  for(int i=0; i<20; i++){
    myLevel1Param->mins[i]=level2ParamsArr[i].min;
  }
  myLevel1Param->min = *min_element(myLevel1Param->mins,myLevel1Param->mins+20);
  pthread_exit(0);
}

int main(int argc, char *argv[]){
  time_t t;
  time(&t);
  srand((unsigned)t); //seed randomizer using time of execution

  

  //fill array with random numbers
  for(int i=0; i<AMOUNT_OF_NUMS; i++){
    randnums[i]=rand();
  }

  const int NUM_LVL1_THREADS=5;
  pthread_t tids[NUM_LVL1_THREADS];
  pthread_attr_t attrs[NUM_LVL1_THREADS];

  Level1Params level1ParamsArr[5]; 

  //create 5 threads and pass sections of the randnums array to each struct
  for(int i=0; i<NUM_LVL1_THREADS; i++){
    for(int j=i*2000; j<i*2000+2000; j++){
      level1ParamsArr[i].numsSlice[j-(i*2000)]=randnums[j];
    }
    pthread_attr_init(&attrs[i]);
    pthread_create(&tids[i], &attrs[i], level1Func, &level1ParamsArr[i]);
    pthread_join(tids[i], NULL);
  }

  int mins[5];
  for(int i=0; i<5; i++){
    mins[i]= level1ParamsArr[i].min;
  }

  int min;
  min = *min_element(mins,mins+5);
  
  printf("calculated min: %d\n", min);

  int expected_min = *min_element(randnums, randnums+10'000);
  printf("expected min: %d\n", expected_min);

}