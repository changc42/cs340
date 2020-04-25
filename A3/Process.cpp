#pragma once
#include<string>
#include "Process.h"
using namespace std;



Process::Process(string id, int b, int s, int p)
    :id{id}, burst{b}, start{s}, end{-1}, wait{0}, priority{p}{

}

Process::Process()
    :Process{"default", -1, -1, -1}{
}

void Process::incrementWait(){
    wait++;
}

void Process::decrementBurst(){
    if(burst==0){
        cout << "ERROR. burst is already 0. cannot decrement" << endl;
        exit(3);
    }
    burst--;
}

void Process::display(){
    printf("{   id: %s\n"
            "   Burst: %d\n"
            "   start: %d\n"
            "   end: %d\n"
            "   wait: %d\n"
            "   priority: %d    }\n\n",
            id.c_str(), burst, start, end, wait, priority);
}