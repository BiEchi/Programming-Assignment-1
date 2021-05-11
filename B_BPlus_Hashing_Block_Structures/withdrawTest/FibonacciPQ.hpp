#ifndef _FibonacciPQ_H
#define _FibonacciPQ_H
#include "Person.hpp"
#include "PeopleLocalQueue.hpp"
#include "blackList.hpp"
using namespace std;

class FibonacciPQ
{
    // API functions
public:
    FibonacciPQ()
    {
        PQ_length = 0;
        BucketLength = 10;
        Minptr = NULL;
        Rootlist = list<Person *>();
        Degreebucket = vector<Person *>(10, NULL);
        storePeople = vector<Person>();
        Rootsize = 0;
    }
    int returnLength();
    bool isEmpty();
    bool inSert(Person *handle);
    bool eatPeople(PeopleLocalQueue &local_queue);
    Person *withdrawInCentral(Person *withdrawingPerson);
    Person *popMin();
    Person *changeStatus(Person *changingPatient, string profession_status, string riskStatus_status);
    Person* find(string ID, list<Person *> &findingList);
    vector<Person> returnStorePeople();
    list<Person *> getRootlist();

private:
    void removeNode(Person *handle);
    Person *link(Person *a_prt, Person *b_ptr);
    Person *decreaseKey(Person *changeStatusPerson, string &profession_status, string &riskStatus_status);
    void rebalance();
    void addSonPerson(Person *sonPerson, Person *parentPerson);
    void cut(Person *sonPerson, Person *parentPerson);
    void newPerson(Person *newroot);
    bool cascadingCut(Person *parent);
    Person *stand_in(Person *copy_person_ptr);
    bool freeSon(Person *parent_node);

    int PQ_length;
    int BucketLength;
    size_t Rootsize;
    Person *Minptr; // the ptr pointing to the root having min Key in the list.
    // 初始时造个空的
    list<Person *> Rootlist; //creating a Rootlist to store the root
    vector<Person *> Degreebucket;
    vector<Person> storePeople;
};

#endif
