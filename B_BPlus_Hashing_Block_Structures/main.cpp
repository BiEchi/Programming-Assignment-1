#include "BPlusTree.h"
#include "block.h"
#include "BTree.h"
#include "Tree.h"
#include "HashMap.hpp"

#include <unistd.h>
#include <iostream>
#include <stdlib.h>

// Used for testing.
int main()
{
    cout << "Initializing people data..." << endl;
    
    int num = 40;
    block data;
    BTree testBTree = BTree();
    HashMapForProfession testHashMap = HashMapForProfession();
    Person people[num];
    
    cout << "### Now we go into B Tree test ###" << endl;
    
    cout << "Test for insert." << endl;
    for (int i = 0; i < num; i++) {
        people[i].setName(to_string(i));
        testBTree.insert(&people[i]);
    }
    testBTree.print();
    
    cout << "Test for insert passed." << endl;
    
    cout << "Test for delete." << endl;
    for (int i = 0; i < num; i++)
        testBTree.del(&people[i]);
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
