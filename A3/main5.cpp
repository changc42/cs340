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

    list<Process*> processes{};
    processes = parseInput("input.txt");
    
    Process* nullProcess = new Process(); //create a dummy null process to initialize running state
    Process* running = nullProcess;
    SLinkedList readyQ{};

    for(int t=0; t<=96; t++){
        bool displayedTime = false;

        for(auto p: processes){
            if(p->start == t)readyQ.push_back(p);
        }

        if(!readyQ.empty()){
            
            Process* potential = readyQ.getHighestPrio();
            
            if(potential->priority > running->priority){
                cout << "t=" << t << ": " << endl;
                displayedTime = true;

                readyQ.remove(potential);
                if(running->id!="default"){
                    readyQ.addFirst(running);
                    cout << running->id << " moved to front of ready queue. There is process with higher priority" << endl;
                }
                cout << potential->id << " now running" << endl;
                running = potential;
            }
        }

        if(running->timeQuantum == 10){
            
            running->timeQuantum = 0;

            if(!readyQ.empty()){
                Node* curr = readyQ.head->next;
                while(curr!=nullptr){
                    if(curr->p->priority == running->priority){
                        if(!displayedTime){
                            cout << "t=" << t << ": " << endl;
                            displayedTime = true;
                        }
                        readyQ.push_back(running);
                        readyQ.remove(curr->p);
                        cout << running->id << " moved to back of ready queue. Round robin time quantum used" << endl;
                        running = curr->p;
                        cout << curr->p->id << " now running" << endl;
                        break;
                    }
                    curr=curr->next;
                }
            }
        }

        Node* curr = readyQ.head->next;
        while(curr!=nullptr){
            curr->p->incrementWait();
            curr = curr->next;
        }
        if(running!=nullProcess) running->decrementBurst();
        running->timeQuantum++;

        if(running->burst == 0){
            if(!displayedTime){
                cout << "t=" << t << ": " << endl;
                displayedTime = true;
            }
            running->end = t;
            cout << running->id << " finished." << endl;
            if(!readyQ.empty()){
                Process* replacement = readyQ.getHighestPrio();
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
        string printTurnaround;
        if(p->start > p->end){
            printTurnaround="never ended";
        }
        else printTurnaround=to_string(p->end - p->start + 1);
        cout << p->id << ", Turnaround: " << printTurnaround << ", Wait: " << to_string(p->wait) << endl;
        
    }
}