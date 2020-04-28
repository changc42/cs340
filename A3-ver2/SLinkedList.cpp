#pragma once
#include<iostream>
#include<fstream>
#include<list>
#include<sstream>
#include<vector>
#include "Process.cpp"
using namespace std;

class SLinkedList{
    public:

    Node* head;
    Node* tail;

    SLinkedList()
        :head{nullptr}, tail{nullptr}{
            head = new Node("default", -1, -1, -1);
            tail = head;
        }

    // void addFirst(string id, int b, int s, int p){
    //     Node* n = new Node(id, b, s, p);
    //     Node* temp = head->next;
    //     head->next = n;
    //     n->next = temp;
    //     if(head==tail) tail = n;
    // }
    // void addFirst(string id){
    //     Node* n = new Node(id);
    //     Node* temp = head->next;
    //     head->next = n;
    //     n->next = temp;
    //     if(head==tail) tail = n;
    // }
    void addFirst(Process* p){
        Node* n = new Node(p);
        Node* temp = head->next;
        head->next = n;
        n->next = temp;
        if(head==tail) tail = n;
    }

    // void addLast(string id, int b, int s, int p){
    //     Node* n = new Node(id, b, s, p);
    //     tail->next = n;
    //     tail = n;
    // }
    // void addLast(string id){
    //     Node* n = new Node(id);
    //     tail->next = n;
    //     tail = n;
    // }
    void push_back(Process* p){
        Node* n = new Node(p);
        tail->next = n;
        tail = n;
    }

    // void remove(string id){
    //     Node* a{head};
    //     Node* b{nullptr};
    //     Node* c{nullptr};
    //     while(a != nullptr){
    //         b = a->next;
    //         if(b!=nullptr && b->p.id.compare(id) == 0){
    //             c = b->next;
    //             a->next = c;
    //             break;
    //         }
    //     }
    // }

    //returns true is specified process was removed. returns false otherwise(process does not exist in list)
    bool remove(Process* p){
        Node* a{head};
        Node* b{nullptr};
        Node* c{nullptr};
        while(a != nullptr){
            b = a->next;
            if(b->p == p){
                if(b!=nullptr) c = b->next;
                a->next = c;
                return true;
            }
        }
        return false;
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