/*
Assume priority values range from 1 to 10, inclusive
*/

#include"Process.h"
#include<list>
#include<iostream>
using namespace std;


Process* getHighestPrio(list<Process*> processes){
    if(processes.empty()){
        cout << "Cannot call getHighestPrio on empty list" << endl;
        exit(3);
    }
    Process* ret;
    int highest = 0;
    for(auto p: processes){
        if(p->priority > highest){
            highest = p->priority;
            ret = p;
        }
    }
    return ret;
}