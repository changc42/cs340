/*
compilation instructions(for Windows):
g++ main.cpp
a

checkout other files before reading main.
*/

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
    
    Process* nullProcess = new Process(); //create a dummy null process to
    Process* running = nullProcess;
    list<Process*> readyQ;

    int continuousTime{0};
    for(int t=0; t<=96; t++){
        bool displayedTime = false;

        for(auto p: processes){
            if(p->start == t) readyQ.push_back(p);
        }

        if(!readyQ.empty()){
            
            Process* potential = getHighestPrio(readyQ);
            if(potential->priority > running->priority){
                cout << "t=" << t << ": " << endl;
                displayedTime = true;
                continuousTime = 0;

                readyQ.remove(potential);
                if(running->id!="default"){
                    readyQ.push_back(running);
                    cout << running->id << " moved to ready queue. There is process with higher priority" << endl;
                }
                cout << potential->id << " now running" << endl;
                running = potential;
            }

            if(continuousTime == 10){
                
                for(auto p: readyQ){
                    if(p->priority == running->priority){
                        if(!displayedTime){
                            cout << "t=" << t << ": " << endl;
                            displayedTime = true;
                        }
                        continuousTime = 0;
                        readyQ.push_back(running);
                        readyQ.remove(p);
                        cout << running->id << " moved to ready queue. RR time quantum used up" << endl;
                        running = p;
                        cout << p->id << " now running" << endl;
                        break;
                    }
                }
            }
        }

        for(auto p: readyQ) p->incrementWait();
        if(running!=nullProcess) running->decrementBurst();
        continuousTime++;

        if(running->burst == 0){
            if(!displayedTime){
                cout << "t=" << t << ": " << endl;
                displayedTime = true;
            }
            running->end = t;
            cout << running->id << " finished." << endl;
            if(!readyQ.empty()){
                continuousTime=0;
                Process* replacement = getHighestPrio(readyQ);
                running = replacement;
                readyQ.remove(replacement);
                cout << running->id << " will run next" << endl;
            }
            else running = nullProcess;
        }

        if(displayedTime) cout << endl;
    }

    cout << "\nFinished running processes\n" << endl;

    for(auto p: processes){
        cout << p->id << ", Turnaround: " << to_string(p->end - p->start + 1) << ", Wait: " << to_string(p->wait) << endl;
    }
    
}