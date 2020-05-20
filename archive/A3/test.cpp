#include<iostream>
using namespace std;


int main(int argc, char** argv){
    cout << argc << endl;
    for( int i =0; i< 3; i++){
        cout << argv[i] << endl;
    }
}