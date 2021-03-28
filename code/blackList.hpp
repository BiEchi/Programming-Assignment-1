#ifndef blackList_hpp
#define blackList_hpp

#include "Person.hpp"
#include <cstdlib>

// 通过指针加入person和通过弹出person
class blackList
{
public:
    blackList()
    {
        length = 5;
        blackList_Hashing_table = vector<list<Person *>>(length, list<Person *>());
    }

    // API
    Person *popPersonWithID(Person *popped_person);
    Person *appendPerson(Person *Withdraw_person);

private:
    int length;
    vector<list<Person *>> blackList_Hashing_table;
    hash<string> hash_for_id;
};

#endif
