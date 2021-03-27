#include "blackList.hpp"
#include <random>

int main()
{
    vector<Person> test_list = vector<Person>();
    blackList blackList_test = blackList();
    // load list
    Person black1, black2, black3;
    string ID1 = string("172756172364");
    string ID2 = string("2385571823875");
    string ID3 = string("23857172384857");
    black1.setID(ID1);
    black2.setID(ID2);
    black3.setID(ID3);
    blackList_test.appendPerson(&black1);
    blackList_test.appendPerson(&black2);
    blackList_test.appendPerson(&black3);
}