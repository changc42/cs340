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
using namespace std;

class Process{
    public: 

    string id;
    int burst;//time needed to execute program. decreases as process is running
    int start;
    int end;
    int wait;
    int priority;

    
    
    Process(string id, int b, int s, int p)
        :id{id}, burst{b}, start{s}, end{-1}, wait{0}, priority{p}{
    }
    Process()
        :Process{"default", -1, -1, -1}{
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
                "   priority: %d    }\n\n",
                id.c_str(), burst, start, end, wait, priority);
    }
};

//searches list for the process with the highest priority and returns it
Process* getHighestPrio(list<Process*> processes){
    if(processes.empty()){
        cout << "ERROR. Cannot call getHighestPrio on empty list" << endl;
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

//given an input file, returns a list of the processes which the input file represent.
//input file must have 4 columns, where the columns are ordered in the following manner:
//id, priority, burst, and arrival
list<Process*> parseInput(string fileName){
    ifstream input;
    input.open(fileName);

    if(input.fail()){
        cout << "ERROR: File \'" << fileName << "\' does not exist" << endl;
        exit(3);
    }

    list<Process*> processes{};
    while(!input.eof()){
        string id;
        int p;
        int b;
        int s;
        string nextToken;

        string line;
        getline(input, line);
        stringstream ss(line);
        

        do{
            getline(ss, nextToken, ' ');
        }while(nextToken=="");
        id = nextToken;

        do{
            getline(ss, nextToken, ' ');
        }while(nextToken=="");
        p = stoi(nextToken);

        do{
            getline(ss, nextToken, ' ');
        }while(nextToken=="");
        b = stoi(nextToken);

        do{
            getline(ss, nextToken, ' ');
        }while(nextToken=="");
        s = stoi(nextToken);

        processes.push_back(new Process(id,b,s,p));
    }
    return processes;
}

int main(int argc, char* argv[]){

    if(argc < 2){
        cout << "ERROR: must provide input file" << endl;
        exit(3);
    }

    list<Process*> processes{};
    processes = parseInput(argv[1]);
    
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