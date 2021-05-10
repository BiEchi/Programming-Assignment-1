#include "BPlusTree.h"
// #include "BPlusTree.cpp" // delete when GNU making
#include "block.h"
// #include "block.cpp" // delete when GNU making
#include "BTree.h"
// #include "BTree.cpp" // delete when GNU making
#include "Tree.h"

#include <unistd.h>
#include <iostream>
#include <stdlib.h>

// Used for testing.
int main()
{
    cout << "Initializing people data..." << endl;
    
    int num = 40;
    block data;
    BPlusTree testBPlusTree = BPlusTree(&data);
    BTree testBTree = BTree();
    Person people[num];
    
    sleep(2);
    for (int i = 0; i < num; i++)
    {
        people[i].setID(to_string(100 + i));
    }
    srand(1);
    for (int i = 0; i < num; i++)
    {
        people[i].setProfession(to_string(rand() % 9));
    }
   
    cout << "Now we go into B+ Tree test in 1 second..." << endl;
    sleep(1);

    cout << "Test for insert. " << endl;
    for (int i = 0; i < num; i++)
    {
        testBPlusTree.bPlustree_insert(testBPlusTree.returnRoot(), &people[i]);
    }
    testBPlusTree.linear_print();
    
    cout << "Test for delete. " << endl;
    for (int i = 0; i < num; i++)
    {
        testBPlusTree.bPlustree_delete(testBPlusTree.returnRoot(), people[i].getID());
    }

    testBPlusTree.linear_print();
    cout << "Test for inverse insert. " << endl;
    for (int i = num - 1; i >= 0; i--)
    {
        testBPlusTree.bPlustree_insert(testBPlusTree.returnRoot(), &people[i]);
    }
    testBPlusTree.linear_print();
    
    cout << "test for inverse delete." << endl;
    sleep(1);
    for (int i = num - 1; i >= 0; i--)
    {
        testBPlusTree.bPlustree_delete(testBPlusTree.returnRoot(), people[i].getID());
    }
    testBPlusTree.linear_print();
    cout << endl;
    cout << "Pass the B+ test successfully." << endl;
    cout << endl << endl;
    
    cout << "Now we go into B Tree test in 1 second..." << endl;
    sleep(1);
    
    cout << "Test for insert." << endl;
    sleep(1);
    for (int i = 0; i < num; i++) {
        usleep(100000);
        testBTree.btree_insert(testBTree.returnRoot(), &people[i]);
    }
    testBTree.level_display();
    
    
    return 0;
}
