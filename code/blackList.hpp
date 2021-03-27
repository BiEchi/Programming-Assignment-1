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
    Person *popPersonWithID(Person *popped_person);
    Person *appendPerson(Person *Withdraw_person);

private:
    int length;
    vector<list<Person *>> blackList_Hashing_table;
    hash<string> hash_for_id;
};
// hash finding
Person *blackList::popPersonWithID(Person *popped_person)
{
    int index = hash_for_id(popped_person->ID) % length;
    Person *poppedPersonPtr = nullptr;
    for (auto pos = blackList_Hashing_table[index].begin(); pos != blackList_Hashing_table[index].end(); pos++)
    {
        if ((*pos)->ID == popped_person->ID)
        {
            poppedPersonPtr = (*pos);
            break;
        }
    }
    if(nullptr == poppedPersonPtr)
        cout << "there is not a person!" << endl;
    else
        cout << "successfully delete " << popped_person->ID << endl;
    return poppedPersonPtr;
}

// add new person
Person* blackList::appendPerson(Person *Withdraw_person)
{
    int index = hash_for_id(Withdraw_person->ID) % length;
    blackList_Hashing_table[index].push_back(Withdraw_person);
    cout << "successfully add a person" << endl;
    return Withdraw_person;
}

#endif
