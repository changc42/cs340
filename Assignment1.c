/*
to compile, run "gcc Assignment1.c -o time"
to run, type in "./time [insert command here]"
be sure to run command "./time" with one argument or weird stuff happens
*/

/*
this assignment was very difficult.
at first, I tried to run this code on windows machine. as you can imagine, this did not 
work. Next, I ran the code on mars. This worked. However, there was another problem. I did
not understand how fork() worked. As i stated in class, I forked 4 times, and at the end of
the program, I printf("hello");
I expect 16 lines of "hello", however, everytime I ran the program, A different number
of "hello" lines were outputted. This is very confusing and I still do not have an
explanation for why this is happening

next I had to figure how the pipe and read/write functions worked. For a long time,
I tried to write the "struct timeval tv" into the pipe. I kept getting errors saying 
expected some other argument and got something else instead. I did not realize I could 
only write arrays. Once i figured out i could only pass arrays, I finished the program.
*/

#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>  
#include <stdlib.h> 
#include <errno.h>   
#include <sys/wait.h>
#include <sys/time.h>
#include <string.h>

int main(int argc, char *argv[]){
  //create file descriptor/pipe
  int fd[2];
  pipe(fd);

  //store commandline arguments in command_ variable
  char command_[100];
  strcpy(command_, argv[1]);
  //create string which represents path to command code. required argument in execlp
  char relPath[100];
  sprintf(relPath, "/bin/%s", command_);

  //create `struct timeval` tvP for parent to store current time
  //create tvC for parent to store current time
  //create parentReadChild to store data read from pipe
  struct timeval tvP;
  int parentReadChild[2]; //index 0 stores normal seconds, index 1 stores microseconds
  struct timeval tvC;

  //create child process and store return value in pid
  pid_t pid = fork();

  //if in parent, execute the following
  if(pid>0){
    //wait until child finishes exec call
    wait(NULL);

    //store end time in tvP
    gettimeofday(&tvP, NULL);
    int endTimeSec = tvP.tv_sec;
    int endTimeMicroSec = tvP.tv_usec;

    //read data from pipe and store response in parentEndTime
    read(fd[0],parentReadChild,100);
    
    printf("IN PARENT: data read from pipe is: %u sec and %u microsec\n",parentReadChild[0],parentReadChild[1]);
    printf("IN PARENT: end time is %u sec and %u microsec\n",endTimeSec, endTimeMicroSec);

    int elapsedTime = endTimeMicroSec - parentReadChild[1];
    printf("IN PARENT: elapsed time is %u microsec\n", elapsedTime);
  }

  char message[100];

  //if in child execute the following
  if(pid==0){
    //store start time in tvC
    gettimeofday(&tvC, NULL);
    printf("IN CHILD: start time is %u sec and %u microsec\n",tvC.tv_sec, tvC.tv_usec);
    printf("running command: %s\n", command_);
    //write tvC to pipe
    int childStartTime[2]={tvC.tv_sec, tvC.tv_usec};
    write(fd[1],childStartTime,100);

    //execute command specified in command line argument then exit
    
    execlp(relPath,command_,NULL);
  }
  
}



  


