#include<iostream>
#include<stdlib.h>
#include<ctime>
#include<pthread.h>
#include<stdio.h>
#include<climits>
#include<algorithm>
#include<time.h>
#include<sys/time.h>

using namespace std;

const int AMOUNT_OF_NUMS = 10'000;
int randnums [AMOUNT_OF_NUMS];

int main(int argc, char *argv[]){
  clock_t beginC = clock();
  struct timeval begin, end;
  gettimeofday(&begin,NULL);

  time_t t;
  time(&t);
  srand((unsigned)t); //seed randomizer using time of execution

  for(int i=0; i<AMOUNT_OF_NUMS; i++){
    randnums[i]=rand();
  }

  int min;
  min = *min_element(randnums, randnums+10'000);
  printf("expected min: %d\n", min);

  clock_t endC = clock();
  gettimeofday(&end,NULL);
  printf("elapsed timeofday: %d\n", end.tv_usec-begin.tv_usec);
  printf("elapsed clock: %d\n", beginC);
}