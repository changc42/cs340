/*
compilation instructions(for Windows):
g++ Chang_Caleb_Project3.cpp
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
using namespace std;

class Process{
    public: 

    string id;
    int burst;      //time needed to execute program. decreases as process is running
    int start;      //time the process arrives
    int end;        //time the process finishes executing
    int wait;
    int priority;
    int timeQuantum;//keeps track of how much of round robin time quantum has been used

    
    
    Process(string id, int b, int s, int p)
        :id{id}, burst{b}, start{s}, end{-1}, wait{0}, priority{p}, timeQuantum{0}{
    }

    //used to create a null process
    Process()
        :Process{"default", -1, -1, -1}{
    }

    //for debugging purposes
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

/*
given an input file, returns a list of the processes which the input file represents.
input file must have 4 columns, where the columns are ordered in the following manner:
id, priority, burst, and arrival
*/
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
        

        getline(ss, nextToken, '\t');
        id = nextToken;

        getline(ss, nextToken, '\t');
        p = stoi(nextToken);

        getline(ss, nextToken, '\t');
        b = stoi(nextToken);

        getline(ss, nextToken, '\t');
        s = stoi(nextToken);

        processes.push_back(new Process(id,b,s,p));
    }
    return processes;
}

//node used in SinglyLinkedList
class Node{
    public:
    Process* p;
    Node* next;

    Node(Process* p_arg)
        :p{p_arg}, next{nullptr}{

    }
    Node(string id, int b, int s, int prio)
        :p{nullptr}, next{nullptr}{
            p = new Process(id, b, s, prio);
        }

    Node(string id)
        :Node{id, -1, -1, -1}{
        }

    Node()
        :Node{"default", -1, -1, -1}{
        }

    void display(){
        p->display();
    }
};

class SLinkedList{
    public:

    Node* head;
    Node* tail;

    SLinkedList()
        :head{nullptr}, tail{nullptr}{
            head = new Node("default", -1, -1, -1);
            tail = head;
        }

    void addFirst(Process* p){
        Node* n = new Node(p);
        Node* temp = head->next;
        head->next = n;
        n->next = temp;
        if(head==tail) tail = n;
    }

    void push_back(Process* p){
        Node* n = new Node(p);
        tail->next = n;
        tail = n;
    }

    //returns true is specified process was removed. returns false otherwise(process does not exist in list)
    bool remove(Process* p){
        Node* a{head};
        Node* b{nullptr};
        Node* c{nullptr};
        while(a->next != nullptr){
            b = a->next;
            if(b->p == p){
                c = b->next;
                a->next = c;
                if(c==nullptr) tail = a;
                return true;
            }
            a=a->next;
        }
        return false;
    }

    bool empty(){
        if(head==tail){
            return true;
        }
        return false;
    }

    void display(){
        if(empty()) cout << "empty" << endl;
        else{
            Node* curr = head->next;
            while(curr!=nullptr){
                curr->display();
                curr = curr->next;
            }
        }
        
    }

    //searches list for the process with the highest priority and returns it. if list has multiple processes with the highest priority, the first occurence is returned
    Process* getHighestPrio(){
        if(empty()){
            cout << "ERROR. Cannot call getHighestPrio on empty list" << endl;
            exit(3);
        }
        Process* ret;
        int highest = 0;
        
        Node* curr = head->next;
        while(curr!=nullptr){
            if(curr->p->priority > highest){
                highest = curr->p->priority;
                ret = curr->p;
            }
            curr=curr->next;
        }
        return ret;
    }
};

int main(int argc, char* argv[]){

    list<Process*> processes{};
    processes = parseInput("input.txt");
    
    Process* nullProcess = new Process(); //create a dummy null process to initialize running state
    Process* running = nullProcess;
    SLinkedList readyQ{};

    for(int t=0; t<=96; t++){
        bool displayedTime = false; //flag used for output formatting

        for(auto p: processes){
            if(p->start == t)readyQ.push_back(p);
        }

        //check readyQ for proccesses with higher priority than the running process
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

        //if running process used up time quantum, see if there are any processes with same priority who will preempt the running process due to round robin rules
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

        //increase wait counter on all proccesses in ready queue
        //decrease burst counter on running process
        //increment timeQuantum counter on running process
        Node* curr = readyQ.head->next;
        while(curr!=nullptr){
            curr->p->incrementWait();
            curr = curr->next;
        }
        if(running!=nullProcess) running->decrementBurst();
        running->timeQuantum++;

        //if running process completes, remove from running state
        //if readyQ is empty, set running to the null/dummy process
        //if readyQ not empty, run process with highest priority
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

/*
output on my computer

t=0: 
P1 now running

t=14:
P1 finished.
P2 will run next

t=20:
P2 moved to front of ready queue. There is process with higher priority
P3 now running

t=30: 
P3 moved to back of ready queue. Round robin time quantum used
P4 now running

t=40:
P4 moved to back of ready queue. Round robin time quantum used
P3 now running

t=45:
P3 moved to front of ready queue. There is process with higher priority
P5 now running

t=49:
P5 finished.
P3 will run next

t=54:
P3 finished.
P4 will run next

t=55:
P4 moved to front of ready queue. There is process with higher priority
P6 now running

t=69:
P6 finished.
P4 will run next

t=79:
P4 finished.
P2 will run next

t=94:
P2 finished.


Finished running processes

P1, Turnaround: 15, Wait: 0
P2, Turnaround: 95, Wait: 75
P3, Turnaround: 35, Wait: 15
P4, Turnaround: 55, Wait: 35
P5, Turnaround: 5, Wait: 0
P6, Turnaround: 15, Wait: 0
*/

/*
WRITE UP:

I had to spend some time thinking about how I would structure the program and what classes I would create. I thought about creating a class to represent the CPU, but decided not to because we are using a loop to mimic feeding a cpu processes, as opposed to running a server and sending it processes. 

Originally, I used STL:list to implement the readyQ, but I later discovered you wanted us to write our own singly linked list. This came with some challenges and debugging. Primarily, keeping track of the head and tail nodes whenever a Node was added or removed was difficult.

Parsing the input file was tedious. Originally, my texteditor was configured so that every time I push tab, it would enter 2 spaces instead of the tab character. Because of this, I wrote a parser which expected "space" character delimiters. Later, I discovered I could configure my text editor the insert "tab" characters when I push tab instead of inserting "spaces". I then had to change the parser. 

It's been a long time since I last wrote C++ classes, so I had to review initialization lists.

Originally, I did not know that a processes timeQuantum is not reset when it is preempted. I had to think about how to keep track of each processes time quantums, and how to implement the ready queue such that both round robin and preemption were accounted for. I decided to add a process to the front of the queue if it were preempted by a process with higher priority, and to add a process to the back of the queue if it used up its time quantum and was replaced by a process with the same priority. This way, I did not have to change my getHighestPrio() function.
*/