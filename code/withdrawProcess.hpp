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
    void LoadingDemoData(PeopleLocalQueue &people);
    void PeopleWithdrawDemo(blackList &blackList, PeopleLocalQueue &people);
    void CentraListWithdrawDemo(blackList &blackList, FibonacciPQ &centrallist);
    void HospitalWithdrawDemo(blackList &blacklist, queueManger &hospital);

private:
    void returnLastID();
    vector<string> IDStoreDatabase;
    string ID = "0";
};

#endif
