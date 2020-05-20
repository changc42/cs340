//using tab delimiter

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
                "   priority: %d    }\n\n",
                id.c_str(), burst, start, end, wait, priority);
    }
};

class Node{
    public:
    Process p;
    Node* next;

    Node(string id, int b, int s, int p)
        :p{id, b, s, p}, next{nullptr}{

        }

    Node(string id)
        :Node{id, -1, -1, -1}{

        }

    Node()
        :p{"default", -1, -1, -1}, next{nullptr}{

        }

    void display(){
        p.display();
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

    void addFirst(Node* n){
        Node* temp = head->next;
        head->next = n;
        n->next = temp;
        if(head==tail) tail = n;
    }
    void addFirst(string id, int b, int s, int p){
        Node* n = new Node(id, b, s, p);
        Node* temp = head->next;
        head->next = n;
        n->next = temp;
        if(head==tail) tail = n;
    }
    void addFirst(string id){
        Node* n = new Node(id);
        Node* temp = head->next;
        head->next = n;
        n->next = temp;
        if(head==tail) tail = n;
    }

    void addLast(Node* n){
        tail->next = n;
        tail = n;
    }
    void addLast(string id, int b, int s, int p){
        Node* n = new Node(id, b, s, p);
        tail->next = n;
        tail = n;
    }
    void addLast(string id){
        Node* n = new Node(id);
        tail->next = n;
        tail = n;
    }

    void display(){
        Node* curr = head->next;
        while(curr!=nullptr){
            curr->display();
            curr = curr->next;
        }
    }

    bool empty(){
        if(head==tail){
            return true;
        }
        return false;
    }

    // Process* getHighestPrio(){

    // }
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

Process* getHighestPrio(SLinkedList queue){
    if(queue.empty()){
        cout << "ERROR. Cannot call getHighestPrio on empty list" << endl;
        exit(3);
    }
}

//given an input file, returns a list of the processes which the input file represents.
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

int main(int argc, char* argv[]){

    // if(argc < 2){
    //     cout << "ERROR: must provide input file" << endl;
    //     exit(3);
        
    // }

    // list<Process*> processes{};
    // processes = parseInput(argv[1]);
    
    // Process* nullProcess = new Process(); //create a dummy null process to
    // Process* running = nullProcess;
    // list<Process*> readyQ;

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
    
    SLinkedList* myList = new SLinkedList();
    myList->addLast("p1");
    myList->addLast("p3");
    myList->addLast("p2");
    myList->addFirst("p42", 4, 3, 2);
    myList->display();

}