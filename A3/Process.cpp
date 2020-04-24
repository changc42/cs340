#include<string>
using namespace std;

class Process{

    private:

    string id;
    int burst;
    int start;
    int end;
    int wait;
    int priority;

    public:
    Process(string id, int b, int s, int p)
        :id{id}, burst{b}, start{0}, end{-1}, wait{0}, priority{p}{

    }

    void incrementWait(){
        wait++;
    }

    // int getTurnaroundTime(){
    //     if(start>end)
    // }

    void display(){
        printf("{   id: %s\n"
                "   Burst: %d\n"
                "   start: %d\n"
                "   end: %d\n"
                "   wait: %d\n"
                "   priority: %d    }\n\n",
                id.c_str(), burst, start, end, wait, priority);
    }

};