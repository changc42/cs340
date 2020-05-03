#pragma once
#include<string>
#include<iostream>
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