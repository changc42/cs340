#include<iostream>
#include<list>
#include<vector>
#include<string>
#include "./Process.cpp"
#include "./Mem.cpp"
using namespace std;

int main(int argc, char* argv[]){
    
    Mem mem{1048576};

    vector<string> input;
    for(int i=0; i<argc; i++){
        input.push_back(argv[i]);
    }

    for(auto s: input){
        cout << s<< endl;
    }
    
    // Process* a = new Process{"p42", 35542};
    // Process* b = new Process{"p69", 42263};
    // Process* c = new Process{"yourMOM", 7898};
    // Process* d = new Process{"yourDAD", 778445};
    // Process* e = new Process{"p100" , 202323};

    // mem.allocate(a);
    // mem.allocate(b);
    // mem.allocate(c);
    // mem.display();

    // mem.deallocate("p69");
    // mem.display();

    // mem.allocate(d);
    // mem.display(); 

    // mem.allocate(e);
    // mem.display();
    // mem.compact();
    // mem.allocate(e);
    // mem.display();

    // string input{""};
    // while(input.compare("QUIT")!=0){
    //     cin << input;
    //     mem.parseInput(input);
    // }


    

}