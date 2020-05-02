#include<iostream>
#include<string>
#include<list>
#include<vector>
#include "./Process.cpp"

class Mem{
    list<Process*> processes;
    int capacity;

    Mem(int c)
        :capacity{c}{

    }

    vector<int> findBestFit(Process* p){
        int pSize = p->end - p->start + 1;
        vector<int> bestFitSpace;
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

        int min = capacity+1;
        for(auto hole: holes){
            int holeSize = hole.at(2) - hole.at(1) + 1;
            if(holeSize<min && holeSize>=pSize){
                if(holeSize==pSize) return hole;
                min = holeSize;
                bestFitSpace = hole;
            }
        }
        return bestFitSpace;
    }

    void allocate(Process* p){

    }

    void display(){
        for(auto p: processes){
            p->display();
        }
    }
};