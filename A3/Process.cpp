#pragma once
#include<iostream>
#include<fstream>
#include<list>
#include<sstream>
using namespace std;

class Process{
    public: 

    string id;
    int burst;//time needed to execute program. decreases as process is running
    int start;
    int end;
    int wait;
    int priority;
    int timeQuantum;

    
    
    Process(string id, int b, int s, int p)
        :id{id}, burst{b}, start{s}, end{-1}, wait{0}, priority{p}, timeQuantum{0}{
    }
    Process()
        :Process{"default", -1, -1, -1}{
    }
    Process(string id)
        :Process{id, -1, -1, -1}{

        }
    
    void incrementWait(){
        wait++;
    }
    void decrementBurst(){
        if(burst==0){
            cout << "ERROR. burst is already 0. cannot decrement" << endl;
            exit(3);
        }
        burst--;
    }
    void display(){ //used for debugging
        printf("{   id: %s\n"
                "   Burst: %d\n"
                "   start: %d\n"
                "   end: %d\n"
                "   wait: %d\n"
                "   priority: %d\n"
                "   timeQuantum: %d }\n\n",
                id.c_str(), burst, start, end, wait, priority, timeQuantum);
    }
};