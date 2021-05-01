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
    // bool askUserWithdraw_inPeople(blackList &blackList, PeopleLocalQueue &people, Person *finding_obj);
    // bool askUserWithdraw_inFibonacciPQ(blackList &blackList, FibonacciPQ &centrallist, Person *finding_obj);
    // bool askUserWithdraw_inHospital(blackList &blacklist, queueManger &hospital, Person *finding_obj);
    // void withdrawAdvanced(blackList &blackList, PeopleLocalQueue &people, FibonacciPQ &centralList, queueManger &hospital, string &filename);
    void withdrawDemo(blackList &blackList, PeopleLocalQueue &people, FibonacciPQ &centralList, queueManger &hospital, string &filename);
    // private:
    enum dataClass
    {
        id,
        name,
        Address,
        Profession,
        YOB,
        MOB,
        DOB,
        MAR
    };
    ifstream recordDataBase;
    // string askForID();
    void readFile(string &filename);
    void closeFile(string &filename);
    Person *loadFileAndFindData(string &filename, string ID);
    Person *findAndReturnPersonPointer(string &ID);
    vector<string> s_split(const string &in, const string &delim);
};

#endif