#pragma once
#include<string>
using namespace std;

class Process{
    public: 

    string id;
    int burst;
    int start;
    int end;
    int wait;
    int priority;

    
    
    Process(string id, int b, int s, int p);
    Process(string id);
    Process();
    
    void incrementWait();
    void decrementBurst();
    void display();
};