#include "BPlusTree.h"
#include "BPlusTree.cpp"
#include "block.h"
#include "block.cpp"
#include "BTree.h"
#include "BTree.cpp"
#include "Tree.h"
#include "HashMap.hpp"
#include "HashMap.cpp"
#include "Database.hpp"
#include "Database.cpp"
#include <unistd.h>
#include <iostream>
#include <stdlib.h>

// Used for testing.
int main()
{
    cout << "Initializing people data..." << endl;

    int num = 40;
    block data;
    BPlusTree testBplusTree(&data);
    BTree testBTree = BTree();
    HashMapForProfession testHashMap = HashMapForProfession();
    hospitalDatabase databaseTest(testBplusTree, testBTree, testHashMap);
    Person people[num];

    cout << "### Now we go into B Tree test ###" << endl;

    cout << "Test for insert." << endl;
    for (int i = 0; i < num; i++)
    {
        people[i].setName(to_string(i));
        people[i].setID(to_string(100+i));
        databaseTest.DatabaseInsert(&people[i]);
    }
    testBTree.print();

    cout << "Test for insert passed." << endl;

    cout << "Test for delete." << endl;
    for (int i = 0; i < num; i++)
        databaseTest.DatabaseDelete(people[i].getID());
    testBTree.print();

    cout << "Test for delete passed." << endl;

    cout << "Tests for B Tree passed." << endl;

    /*
    
    cout << "### Now we go to hash table test ###" << endl;
    
    cout << "Test for insert." << endl;
    
    srand(1);
    for (int i = 0; i < num; i++) {
        people[i].setProfession(to_string(rand() % 9));
        people[i].setID(to_string(rand() % 1280));
        testHashMap.insert(&people[i]);
    }
    
    testHashMap.display();
    testHashMap.findAll("4");
    
    cout << "Test for delete." << endl;
    
    for (int i = 0; i < num; i++) {
        people[i].setProfession(to_string(rand() % 9));
        testHashMap.del(&people[i]);
    }
    
    testHashMap.display();
    
    */

    return 0;
}
