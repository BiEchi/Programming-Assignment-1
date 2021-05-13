#include "Database.hpp"
using namespace std;

Person *hospitalDatabase::DatabaseInsert(Person *target)
{
    if (nullptr == target)
        cout << "emtpy person cannot be inserted into the database" << endl;
    else
    {
        BplusDatabase->bPlustree_insert(BplusDatabase->returnRoot(), target);
        HashMapDatabase->insert(target);
        BTreeDatabase->insert(target);
    }
    return target;
}

void hospitalDatabase::DatabaseDelete(string ID)
{
    Person *targetPerson = BplusDatabase->find(ID);
    if (nullptr == targetPerson)
        cout << "we do not find the person " << ID << endl;
    else
    {
        BTreeDatabase->del(targetPerson);
        HashMapDatabase->del(targetPerson);
        BplusDatabase->bPlustree_delete(BplusDatabase->returnRoot(), ID);
    }
    return;
}
