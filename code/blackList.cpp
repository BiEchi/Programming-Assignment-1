#include "blackList.hpp"

// hash finding
Person *blackList::popPersonWithID(Person *popped_person)
{
    int index = hash_for_id(popped_person->getID()) % length;
    Person *poppedPersonPtr = nullptr;
    for (auto pos = blackList_Hashing_table[index].begin(); pos != blackList_Hashing_table[index].end(); pos++)
    {
        if ((*pos)->getID() == popped_person->getID())
        {
            poppedPersonPtr = (*pos);
            break;
        }
    }
    if (nullptr == poppedPersonPtr)
        cout << "there is not such a person!" << endl;
    else
        cout << "successfully delete " << popped_person->getID() << endl;
    return poppedPersonPtr;
}

// add new person
Person *blackList::appendPerson(Person *Withdraw_person)
{
    int index = hash_for_id(Withdraw_person->getID()) % length;
    blackList_Hashing_table[index].push_back(Withdraw_person);
    cout << "successfully add a person" << endl;
    return Withdraw_person;
}