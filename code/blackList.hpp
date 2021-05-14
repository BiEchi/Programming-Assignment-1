#ifndef blackList_hpp
#define blackList_hpp

#include <cstdlib>

#include "Person.hpp"

// 通过指针加入person和通过弹出person
class blackList
{
public:
    blackList()
    {
        length = 5;
        blackList_Hashing_table = vector<list<string>>(length, list<string>());
    }
    
    // API
    void popPersonWithID(string ID);
    void appendPerson(string ID);
    // print the list
    void display(void);
    // need to be added
    int size() { return num; };
    
private:
    int num = 0;
    int length = 0;
    vector<list<string>> blackList_Hashing_table;
    hash<string> hash_for_id;
};

#endif
