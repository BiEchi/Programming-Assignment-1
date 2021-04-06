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
    void askUserWithdraw_inPeople(blackList &blackList, PeopleLocalQueue &people, string &filename);
    void askUserWithdraw_inFibonacciPQ(blackList &blackList, FibonacciPQ &centralist, string &filename);
    void askUserWithdraw_inHospital(blackList &blacklist, queueManger &hospital, string &filename);

private:
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
    string askForID();
    // void loadFileAndFindData(string &filename, string ID, ifstream &recordfile, Person *target_person);
    void readFile(string &filename);
    void closeFile(string &filename);
    Person *loadFileAndFindData(string &filename, string ID, ifstream &recordfile);
    Person *findAndReturnPersonPointer(string &ID, ifstream &recordfile);
    vector<string> s_split(const string &in, const string &delim);
};

#endif