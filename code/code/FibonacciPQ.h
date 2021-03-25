#include "Person.hpp"
#include "PeopleLocalQueue.cpp"
using namespace std;

class FibonacciPQ
{
    // API functions
public:
    FibonacciPQ()
    {
        PQlength = 0;
        BucketLength = 10;
        Minptr = NULL;
        Rootlist = list<Person *>();
        Degreebucket = vector<Person *>(10, NULL);
        Rootsize = 0;
    }
    int  returnLength();
    bool isEmpty();
    bool inSert(Person *handle);
    bool eatPeople(PeopleLocalQueue* local_queue);
    Person *remove(Person *handle);
    Person *popMin();
    Person *decreaseKey(Person *handle, int k);

private:
    Person *link(Person *a_prt, Person *b_ptr);
    void rebalance();
    void addSonPerson(Person *sonPerson, Person *parentPerson);
    void cut(Person *sonPerson, Person *parentPerson);
    void newPerson(Person *newroot);
    bool cascadingCut(Person *parent);

    int PQlength;
    int BucketLength;
    int Rootsize;
    Person *Minptr; // the ptr pointing to the root having min Key in the list.
    // 初始时造个空的
    list<Person *> Rootlist; //creating a Rootlist to store the root
    vector<Person *> Degreebucket;
};

