#include<iostream>
#include<fstream>
#include<list>
#include<sstream>
#include<vector>
#include "Process.cpp"
using namespace std;

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