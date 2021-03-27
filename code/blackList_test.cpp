#include "blackList.hpp"
#include "Person.hpp"
#include <random>

int main()
{
    vector<Person> test_list = vector<Person>();
    blackList blackList_test = blackList();
    // load list
    Person black1, black2, black3;
    string ID1("172756172364");
    string ID2("2385571823875");
    string ID3("23857172384857");
    black1. = ID1;
    black2. = ID2;
    black3. = ID3;
    blackList_test.appendPerson(&black1);
    blackList_test.appendPerson(&black2);
    blackList_test.appendPerson(&black3);
    return 0;
}