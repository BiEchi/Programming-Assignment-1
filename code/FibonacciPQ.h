#include "Person.hpp"
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
    int  ReturnLength();
    bool Isempty();
    bool Insert(Person *handle);
    Person *Remove(Person *handle);
    Person *Popmin();
    Person *DecreaseKey(Person *handle, int k);

private:
    Person *Link(Person *a_prt, Person *b_ptr);
    void Rebalance();
    void AddSonPerson(Person *sonPerson, Person *parentPerson);
    void Cut(Person *sonPerson, Person *parentPerson);
    void NewPerson(Person *newroot);
    bool Cascadingcut(Person *parent);

    int PQlength;
    int BucketLength;
    int Rootsize;
    Person *Minptr; // the ptr pointing to the root having min Key in the list.
    // 初始时造个空的
    list<Person *> Rootlist; //creating a Rootlist to store the root
    vector<Person *> Degreebucket;
};

