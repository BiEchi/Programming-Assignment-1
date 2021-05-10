#ifndef WITHDRAWPROCESS_hpp
#define WITHDRAWPROCESS_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "FibonacciPQ.hpp"
#include "assignment_queue.hpp"
#include "Person.hpp"
#include "blackList.hpp"
#include "PeopleLocalQueue.hpp"


// 分阶段演示，分阶段pop！
class withdrawProcess
{
public:
    void LoadingDemoData(string &filename);
    void PeopleWithdrawDemo(blackList &blackList, PeopleLocalQueue &people, string &ID);
    void CentraListWithdrawDemo(blackList &blackList, FibonacciPQ &centrallist, string &ID);
    void HospitalWithdrawDemo(blackList &blacklist, queueManger &hospital, string &ID);
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
    // void loadFileAndFindData(string &filename, string ID, ifstream &recordfile, Person *target_person);
    void readFile(string &filename);
    void closeFile(string &filename);
    Person *loadFileAndFindData(string &filename, string ID, ifstream &recordfile);
    Person *findAndReturnPersonPointer(string &ID, ifstream &recordfile);
    vector<string> s_split(const string &in, const string &delim);
    vector<string>IDStoreDatabase;
};

#endif
