// #include "Person.cpp"
// #include "FibonacciPQ.cpp"
// #include "PeopleLocalQueue.cpp"
// #include "blackList.cpp"
// #include "withdrawProcess.cpp"
// #include "assignment_queue.cpp"

#include "../assignment_queue.hpp"
#include "../Person.hpp"
#include "../FibonacciPQ.hpp"
#include "../PeopleLocalQueue.hpp"
#include "../blackList.hpp"
#include "../withdrawProcess.hpp"
#include "../TimePredef.hpp"

using namespace std;
time_t startTime = time(NULL);

int main()
{
   int num = 10;
    Person people[num];
    // queueManger hospital;
    PeopleLocalQueue loadingList;
    FibonacciPQ centralist;
    queueManger hospital;
    blackList demoBlackList;
    withdrawProcess withdrawDemo;
    for (int i = 0; i < num; i++)
    {
        people[i].setID(to_string(100 + i));
    }

    for (int i = 0; i < num; i++)
    {
        people[i].setProfession(to_string(rand() % 9));
    }

    for (int i = 0; i < num; i++)
    {
        loadingList.pushBack(&people[i]);
    }
    withdrawDemo.LoadingDemoData(loadingList);
    withdrawDemo.PeopleWithdrawDemo(demoBlackList,loadingList);
    // centralist loads data
    centralist.eatPeople(loadingList);
    
    withdrawDemo.CentraListWithdrawDemo(demoBlackList,centralist);
    /*  */
    // hospital.reassign(&centralist);
    // withdrawDemo.HospitalWithdrawDemo(demoBlackList,hospital);
    demoBlackList.display();
    cout << endl
    << endl;
    cout << "pass the test successfully!" << endl;
    cout << endl
    << endl;
    return 0;
}