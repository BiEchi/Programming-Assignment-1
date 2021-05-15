#ifndef DATABASS_HPP
#define DATABASS_HPP

#include "HashMap.hpp"
#include "BPlusTree.hpp"
#include "BTree.hpp"
using namespace std;

class hospitalDatabase
{
private:
    BPlusTree *BplusDatabase = nullptr;
    BTree*  BTreeDatabase = nullptr;
    HashMap *HashMapDatabase = nullptr;
public:
    hospitalDatabase(){return;}
    hospitalDatabase(BPlusTree &bplus, BTree &btree, HashMap &hashMap)
    {
        BplusDatabase = &bplus;
        BTreeDatabase = &btree;
        HashMapDatabase = &hashMap;
    }
    Person *DatabaseInsert(Person *target);
    void DatabaseDelete(string ID);
    BPlusTree *returnBplus(){return BplusDatabase;}
    BTree *returnBtree(){return BTreeDatabase;}
    HashMap *returnHash(){return HashMapDatabase;}
};
#endif
