#include<iostream>
#include<list>
#include<vector>
#include<string>
#include "./Process.cpp"
#include "./Mem.cpp"
using namespace std;

int main(int argc, char* argv[]){
    
    if(argc != 2){
        cout << "must provide initial capacity of memory. (Enter 1048576)" << endl;
        exit(3);
    }
    string capacity(argv[1]);
    Mem mem{stoi(capacity)};
    mem.start();
}