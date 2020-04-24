/*
this parser defines a tab as some number of spaces.

first, a line is retrieved from input using getline()
then that line is parsed.
a process is created based on reveived data and pushed to list
repeat until EOF reached

return list containing process objects
*/

#include<iostream>
#include "Process.h"
#include<fstream>
#include<list>
#include<sstream>
using namespace std;

list<Process*> parseInput(string fileName){
    ifstream input;
    input.open(fileName);
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
        

        do{
            getline(ss, nextToken, ' ');
        }while(nextToken=="");
        id = nextToken;

        do{
            getline(ss, nextToken, ' ');
        }while(nextToken=="");
        p = stoi(nextToken);

        do{
            getline(ss, nextToken, ' ');
        }while(nextToken=="");
        b = stoi(nextToken);

        do{
            getline(ss, nextToken, ' ');
        }while(nextToken=="");
        s = stoi(nextToken);

        processes.push_back(new Process(id,b,s,p));
    }
    return processes;
}