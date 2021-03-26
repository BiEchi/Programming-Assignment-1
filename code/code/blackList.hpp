#include "Person.hpp"
#include <cstdlib>

class blackList
{
public:
    blackList()
    {
        length = 100;
        blackList_Hashing_table = vector<list<Person *>>(length, list<Person *>());
    }
    Person *popPersonWithID(string Person_id);
    bool appendPerson(Person *Withdraw_person);

private:
    int length;
    vector<list<Person *>> blackList_Hashing_table;
    hash<string> hash_for_id;
};
// hash finding
Person *blackList::popPersonWithID(string Person_id)
{
    int index = hash_for_id(Person_id) % length;
    Person *poppedPersonPtr = nullptr;
    for (auto pos = blackList_Hashing_table[index].begin(); pos != blackList_Hashing_table[index].end(); pos++)
    {
        if ((*pos)->ID == Person_id)
        {
            poppedPersonPtr = (*pos);
            break;
        }
    }
    if(nullptr == poppedPersonPtr)
        cout << "there is not a person!" << endl;
    else
        cout << "successfully delete " << Person_id << endl;
    return poppedPersonPtr;
}

// add new person
bool blackList::appendPerson(Person *Withdraw_person)
{
    int index = hash_for_id(Withdraw_person->ID) % length;
    blackList_Hashing_table[index].push_back(Withdraw_person);
    cout << "successfully add a person" << endl;
    return true;
}