#ifndef DATABASS_HPP
#define DATABASS_HPP

#include "HashMap.hpp"
#include "BPlusTree.h"
#include "BTree.h"
using namespace std;

class hospitalDatabase
{
private:
    BPlusTree *BplusDatabase = nullptr;
    BTree*  BTreeDatabase = nullptr;
    HashMapForProfession *HashMapDatabase = nullptr;
public:
    hospitalDatabase(){return;}
    hospitalDatabase(BPlusTree &bplus, BTree &btree, HashMapForProfession &hashMap)
    {
        BplusDatabase = &bplus;
        BTreeDatabase = &btree;
        HashMapDatabase = &hashMap;
    }
    Person *DatabaseInsert(Person *target);
    void DatabaseDelete(string ID);
};
#endif