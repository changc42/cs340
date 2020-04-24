#include<iostream>
#include "Process.cpp"
#include<fstream>
#include<vector>
using namespace std;

int main(){
    ifstream input;
    string line;
    input.open("input.txt");
    vector<Process*> processes{};
    while(!input.eof()){
        string id;
        int b;
        int s;
        int p;
        string nextToken;

        do{
            getline(input, nextToken, ' ');
            cout << nextToken << endl;
        }while(nextToken=="");
        id = nextToken;

        do{
            getline(input, nextToken, ' ');
            cout << nextToken << endl;
        }while(nextToken=="");
        b = stoi(nextToken);

        do{
            getline(input, nextToken, ' ');
            cout << nextToken << endl;
        }while(nextToken=="");
        s = stoi(nextToken);

        do{
            getline(input, nextToken, ' ');
            cout << nextToken << endl;
        }while(nextToken=="");
        p = stoi(nextToken);

        processes.push_back(new Process(id,b,s,p));
        getline(input, nextToken, ' ');
    }
    for(Process* p: processes){
        p->display();
    }
    
}