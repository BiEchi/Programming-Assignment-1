#include "withdrawProcess.hpp"
#include <unistd.h>
using namespace std;

void withdrawProcess::LoadingDemoData(PeopleLocalQueue &people)
{
    for (int i = 0; i < 5; i++)
    {
        string ID = people.returnID(i);
        if ("0" == ID)
        {
            cout << "all the data have been loaded into the database " << endl;
            break;
        }
        else
        {
            IDStoreDatabase.push_back(ID);
        }
    }

    return;
}

void withdrawProcess::PeopleWithdrawDemo(blackList &blackList, PeopleLocalQueue &people)
{
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
    cout << "this is demo for withdraw in People" << endl;
    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
    returnLastID();
    cout << "Before delete, there are " << people.getLength() << " Person in the loading list" << endl;
    Person *targetPerson = people.isIn(ID);
    if (nullptr == targetPerson)
    {
        cout << "not find the person " << ID << endl;
    }
    else
    {
        blackList.appendPerson(targetPerson->getID());
        people.doWithdraw(targetPerson);
    }
    cout << "After delete, there are " << people.getLength() << " Person in the loading list" << endl;
    cout << "Click any key to terminate Withdraw People Demo" << endl;
    getchar();
    return;
}

void withdrawProcess::CentraListWithdrawDemo(blackList &blackList, FibonacciPQ &centralist)
{
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
    cout << "this is demo for withdraw in Centrallist" << endl;
    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;

    returnLastID();

    list<Person *> start = centralist.getRootlist();
    Person *targetPerson = centralist.find(ID, start);
    if (nullptr == targetPerson)
    {
        cout << "not find the person " << ID << endl;
        return;
    }
    else
    {
        blackList.appendPerson(ID);
        centralist.withdrawInCentral(targetPerson);
        return;
    }
}

void withdrawProcess::HospitalWithdrawDemo(blackList &blacklist, queueManger &hospital)
{
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
    cout << "this is demo for withdraw in Centrallist" << endl;
    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;

    returnLastID();

    Person *targetPerson = hospital.isIn(ID);
    if (nullptr == targetPerson)
    {
        cout << "not find the person " << ID << endl;
        return;
    }
    else
    {
        blacklist.appendPerson(ID);
        hospital.doWithdraw(targetPerson);
        return;
    }
}

void withdrawProcess::returnLastID()
{
    if(0== IDStoreDatabase.size())
        cout << "no person" << endl;
    else
    {
        ID = IDStoreDatabase[IDStoreDatabase.size()-1];
        IDStoreDatabase.pop_back();
    }
    return;
}
