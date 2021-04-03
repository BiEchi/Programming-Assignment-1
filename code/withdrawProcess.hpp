#ifndef WITHDRAWPROCESS_hpp
#define WITHDRAWPROCESS_hpp

#include <iostream>
#include <fstream>
#include "FibonacciPQ.hpp"
#include "assignment_queue.hpp"
#include "Person.hpp"
#include "blackList.hpp"
#include "PeopleLocalQueue.hpp"

class withdrawProcess
{
public:
    void readFile(string filename);
    void askUserWithdraw_inPeople(blackList &blackList, PeopleLocalQueue &people);
    void askUserWithdraw_inFibonacciPQ(blackList &blackList, FibonacciPQ &centralist);
    void askUserWithdraw_inHospital(blackList &blacklist, queueManger &hospital);
    void closeFile(string filename);

private:
    enum dataClass{id,name,Address,Profession,YOB,MOB,DOB,MAR};
    ifstream recordDataBase;
    string askForID();
    Person *findAndReturnPersonPointer(string ID, ifstream &recordfile);
    bool decideAndOperateWithdraw(Person *person, blackList &blackList, FibonacciPQ &centralList, PeopleLocalQueue& people, queueManger &hospitals);
    vector<string> s_split(const string &in, const string &delim);
};

#endif