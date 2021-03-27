#include "blackList.hpp"
#include <random>

int main()
{
    vector<Person> test_list = vector<Person>();
    blackList blackList_test = blackList();
    // load list
    for (int i = 0; i < 10; i++)
    {
        Person test;
        char ID = (char)random();
        char *IDptr = &ID;
        test.setID(IDptr);
        test_list.push_back(test);
    }
    for (auto pos = test_list.begin(); pos != test_list.end(); pos++)
    {
        blackList_test.appendPerson(&(*pos));
        cout << "the id is " << (*pos).getID() << endl;
    }
    return 0;
}