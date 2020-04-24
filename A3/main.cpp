#include<iostream>
#include<fstream>
#include<list>
#include<sstream>
#include "Process.cpp"
#include "parseInput.cpp"
#include "getHighestPrio.cpp"
#include<vector>
using namespace std;

int main(){
    list<Process*> processes{};
    processes = parseInput("input.txt");
    
    Process* running;
    list<Process*> readyQ;
    for(Process* p: processes){
            cout << "hi" << endl;
        }
    vector<int> test;
    test.push_back(2);
    test.push_back(42);
    test.push_back(3);
    test.push_back(2);
    for(auto i: test){
        cout << i << endl;
    }

    for(int t=0; t<=96; t++){
        cout << to_string(t) << endl;
        for(auto p: processes){
            if(p->start == t) readyQ.push_back(p);
        }

        if(!readyQ.empty()){
            Process* potential = getHighestPrio(readyQ);
            if(potential->priority > running->priority){
                cout << "t=" << t << ": " << running->id << " replaced by " << potential->id << endl;
                readyQ.remove(potential);
                readyQ.push_back(running);
                running = potential;
            }
        }

        cout << "t=" << t << ": " << running->id << " running" << t << endl;

        for(auto p: readyQ) p->incrementWait();
        running->decrementBurst();

        if(running->burst == 0){
            running->end = t;
            if(!readyQ.empty()){
                Process* replacement = getHighestPrio(readyQ);
                readyQ.remove(replacement);
                running = replacement;
            }
        }
    }

    cout << "\nFinished running processes\n" << endl;

    for(auto p: processes){
        cout << p->id << ", Turnaround: " << to_string(p->end - p->start + 1) << ", Wait: " << to_string(p->wait) << endl;
    }
    
}