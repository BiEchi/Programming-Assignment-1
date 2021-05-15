#include "blackList.hpp"

// hash finding
void blackList::popPersonWithID(string ID)
{
    int index = hash_for_id(ID) % length;
    string returnID = "0";
    for (auto pos = blackList_Hashing_table[index].begin(); pos != blackList_Hashing_table[index].end(); pos++)
    {
        if ((*pos) == ID)
        {
            returnID = (*pos);
            blackList_Hashing_table[index].erase(pos);
            break;
        }
    }
    if ("0" == returnID)
        cout << "there is not such a person!" << endl;
    else
    {
        cout << "successfully delete " << ID << endl;
        num--;
    }
    return;
}

// add new person
void blackList::appendPerson(string ID)
{
    int index = hash_for_id(ID) % length;
    blackList_Hashing_table[index].push_back(ID);
    cout << "successfully add the person " << ID << "in the blackList" << endl;
    num++;
    return;
}

void blackList::display(void)
{
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
    cout << "Black list info: " << endl;
    for (auto itor = blackList_Hashing_table.begin(); itor != blackList_Hashing_table.end(); itor++)
    {
        for (auto itor2 = (*itor).begin(); itor2 != (*itor).end(); itor2++)
        {
            cout << "The person with ID " << (*itor2) << " is in the black list. " << endl;
        }
    }
    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
    return;
}
