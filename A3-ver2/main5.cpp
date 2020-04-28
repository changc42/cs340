//main5: implementing singly linked list

/*
compilation instructions(for Windows):
g++ main.cpp
a

//given an input file, returns a list of the processes which the input file represent.
//input file must have 4 columns, where the columns are ordered in the following manner:
//id, priority, burst, and arrival

input used for testing:
P1  8  15  0
P2  3  20  0
P3  4  20  20
P4  4  20  25
P5  5  5  45
P6  5  15  55

*/

#include<iostream>
#include<fstream>
#include<list>
#include<sstream>
#include<vector>
#include "Process.cpp"
#include "SLinkedList.cpp"
#include "Node.cpp"
#include "parseInput.cpp"
using namespace std;


int main(int argc, char* argv[]){

    if(argc < 2){
        cout << "ERROR: must provide input file" << endl;
        exit(3);
        
    }

    // list<Process*> processes{};
    // processes = parseInput(argv[1]);
    
    Process* nullProcess = new Process(); //create a dummy null process to initialize running state
    Process* running = nullProcess;
    SLinkedList readyQ{};
    //OLD
    //list<Process*> readyQ;

    // int continuousTime{0};
    // for(int t=0; t<=96; t++){
    //     bool displayedTime = false;

    //     for(auto p: processes){
    //         if(p->start == t) readyQ.push_back(p);
    //     }

    //     if(!readyQ.empty()){
            
    //         Process* potential = getHighestPrio(readyQ);
    //         if(potential->priority > running->priority){
    //             cout << "t=" << t << ": " << endl;
    //             displayedTime = true;
    //             continuousTime = 0;

    //             readyQ.remove(potential);
    //             if(running->id!="default"){
    //                 readyQ.push_back(running);
    //                 cout << running->id << " moved to ready queue. There is process with higher priority" << endl;
    //             }
    //             cout << potential->id << " now running" << endl;
    //             running = potential;
    //         }

    //         if(continuousTime == 10){
                
    //             for(auto p: readyQ){
    //                 if(p->priority == running->priority){
    //                     if(!displayedTime){
    //                         cout << "t=" << t << ": " << endl;
    //                         displayedTime = true;
    //                     }
    //                     continuousTime = 0;
    //                     readyQ.push_back(running);
    //                     readyQ.remove(p);
    //                     cout << running->id << " moved to ready queue. RR time quantum used up" << endl;
    //                     running = p;
    //                     cout << p->id << " now running" << endl;
    //                     break;
    //                 }
    //             }
    //         }
    //     }

    //     for(auto p: readyQ) p->incrementWait();
    //     if(running!=nullProcess) running->decrementBurst();
    //     continuousTime++;

    //     if(running->burst == 0){
    //         if(!displayedTime){
    //             cout << "t=" << t << ": " << endl;
    //             displayedTime = true;
    //         }
    //         running->end = t;
    //         cout << running->id << " finished." << endl;
    //         if(!readyQ.empty()){
    //             continuousTime=0;
    //             Process* replacement = getHighestPrio(readyQ);
    //             running = replacement;
    //             readyQ.remove(replacement);
    //             cout << running->id << " will run next" << endl;
    //         }
    //         else running = nullProcess;
    //     }

    //     if(displayedTime) cout << endl;
    // }

    // cout << "\nFinished running processes\n" << endl;

    // for(auto p: processes){
    //     cout << p->id << ", Turnaround: " << to_string(p->end - p->start + 1) << ", Wait: " << to_string(p->wait) << endl;
    // }
    

}