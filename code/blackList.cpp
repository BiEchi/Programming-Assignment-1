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
            blackList_Hashing_table[index].erase(pos);
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
    Withdraw_person->setCurrentStage(nonebuffer);
    cout << "successfully add a person" << endl;
    return Withdraw_person;
}

int blackList::display(void)
{
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
    cout << "Black list info: " << endl;
    for (auto itor = blackList_Hashing_table.begin(); itor != blackList_Hashing_table.end(); itor++)
    {
        for (auto itor2 = (*itor).begin(); itor2 != (*itor).end(); itor2++)
        {
            cout << "The person with ID " << (*itor2)->getID() << " is in the black list. " << endl;
        }
    }
    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
    return 0;
}