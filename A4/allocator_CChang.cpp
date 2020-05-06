#include<iostream>
#include<string>
#include<list>
#include<vector>
#include<sstream>
using namespace std;

class Process{
    public:

    string id;
    int start;
    int end;
    int size;

    Process(string id, int start, int e, int size)
        :id{id}, start{start}, end{e}, size{size}{

        }
    
    Process(string id, int size)
        :Process{id, -1, -1, size}{

        }
    Process(string id)
        :Process{id, -1, -1, -1}{

        }

    Process()
        :Process{"default", -1, -1, -1}{

        }

    void display(){
        cout << "Addresses" << "[" << start << " : " << end << "] Process " << id << endl;
    }
};

class Mem{
    public:

    list<Process*> processes;
    int capacity;

    Mem(int c)
        :capacity{c}{
    }

    //returns a list of vector<int> of size 2. first index is start, and second index is end
    //vector<int> represents free region of memory
    list<vector<int>> getHoles(){
        list<vector<int>> holes;

        int holeStart=0;
        int holeEnd=-1;
        for(auto p: processes){
            
            if(p->start > holeStart){
                holeEnd= p->start - 1;
                vector<int> temp;
                temp.push_back(holeStart);
                temp.push_back(holeEnd);
                
                holes.push_back(temp);
            }
            holeStart = p->end + 1;

            
        }

        if(holeStart < capacity-1){
                holeEnd = capacity - 1;
                vector<int> temp;
                temp.push_back(holeStart);
                temp.push_back(holeEnd);
                
                holes.push_back(temp);
            }

        return holes;
    }

    //given a process p, returns the free region corresponding to best fit 
    vector<int> findBestFit(Process* p){
        int pSize = p->size;
        vector<int> bestFitSpace{-1,-1};
        list<vector<int>> holes;
        holes = getHoles();       

        int min = capacity+1;
        for(auto hole: holes){
            int holeSize = hole.at(1) - hole.at(0) + 1;
            if(holeSize<min && holeSize>=pSize){
                if(holeSize==pSize) return hole;
                min = holeSize;
                bestFitSpace = hole;
            }
        }
        return bestFitSpace;
    }

    void allocate(Process* p){
        
        vector<int> bestFit = findBestFit(p);
        
        if(bestFit.at(0) == -1){
            cout << "There is no space to allocate for process " << p->id << endl;
            return;
        }

        p->start = bestFit.at(0);
        p->end = p->start + p->size - 1;
        list<Process*>::iterator it;
        it = processes.begin();

        while(it!=processes.end() && (*it)->start < bestFit.at(1)){
            it++;
        }
        processes.insert(it, p);

    }

    void deallocate(string id){
        list<Process*>::iterator it;
        it = processes.begin();
        while(it != processes.end()){
            if((*it)->id.compare(id)==0) break;
            it++;
        }

        if(it == processes.end()){
            cout << "Process " << id << " not found" << endl;
            return;
        }else{
            processes.erase(it);
            return;
        }
        
    }

    void compact(){
        int start = 0;
        for(auto p: processes){
            if(p->start > start){
                p->start = start;
                p->end = p->start + p->size - 1;
            }
            start = p->end + 1;
        }
    }

    bool isNumber(string str){
        string::iterator it = str.begin();
        while(isdigit(*it) && it!=str.end()) it++;

        return str.size()>0 && it==str.end();
    }

    void display(){
        list<vector<int>> holes = getHoles();

        list<Process*>::iterator it_p = processes.begin();
        list<vector<int>>:: iterator it_h = holes.begin();

        while(it_p!= processes.end() && it_h!=holes.end()){
            if((*it_p)->start < (*it_h).at(0)){
                (*it_p)->display();
                it_p++;
            }else{
                cout << "Addresses" << "[" << (*it_h).at(0) << " : " << (*it_h).at(1) << "] Free" << endl;
                it_h++;
            }
        }
        while(it_p!= processes.end()){
            (*it_p)->display();
            it_p++;
        }
        while(it_h!=holes.end()){
            cout << "Addresses" << "[" << (*it_h).at(0) << " : " << (*it_h).at(1) << "] Free" << endl;
            it_h++;
        }

        cout << endl;
    }

    void start(){
        while(true){
            cout << "allocator>";
            string input;
            getline(cin, input);
        
            stringstream ss(input);
            vector<string> inputVec;
            string token;
            while(getline(ss, token, ' ')){
                inputVec.push_back(token);
            }

            if(inputVec.size()==0){
                cout << "invalid input, try again" << endl;
            }
            else if(inputVec.at(0).compare("RQ")==0){
                if(!isNumber(inputVec.at(2)) ||  inputVec.at(3).compare("B")!=0) cout << "invalid input, try again" << endl;
                else{
                    int size = stoi(inputVec.at(2));
                    string id = inputVec.at(1);
                
                    Process* p = new Process(id, size);
                    allocate(p);
                }
                
            }else if (inputVec.at(0).compare("RL")==0){
                string id = inputVec.at(1);
                deallocate(id);
            }else if (inputVec.at(0).compare("STAT")==0){
                display();
            }else if (inputVec.at(0).compare("C")==0){
                compact();
            }else if (inputVec.at(0).compare("QUIT")==0){
                break;
            }else{
                cout << "invalid input, try again" << endl;
            }
        }
    }
};

int main(int argc, char* argv[]){
    
    if(argc != 2){
        cout << "must provide initial capacity of memory. (Enter 1048576)" << endl;
        exit(3);
    }
    string capacity(argv[1]);
    Mem mem{stoi(capacity)};
    mem.start();
}