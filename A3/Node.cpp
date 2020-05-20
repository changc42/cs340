#pragma once
#include<iostream>
#include<fstream>
#include<list>
#include<sstream>
#include<vector>
#include "Process.cpp"
using namespace std;

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