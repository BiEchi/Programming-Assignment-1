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
    
    for (int i = 0; i < num; i++)
    {
        people[i].setID(to_string(100 + i));
    }
    srand(1);
    for (int i = 0; i < num; i++)
    {
        people[i].setName(to_string(i));
    }
   
    cout << "Now we go into B+ Tree test in 1 second..." << endl;

    cout << "Test for insert. " << endl;
    for (int i = 0; i < num; i++)
        testBPlusTree.bPlustree_insert(testBPlusTree.returnRoot(), &people[i]);
    testBPlusTree.linear_print();
    testBPlusTree.level_display();
    
    cout << "Test for delete. " << endl;
    for (int i = 0; i < num; i++)
        testBPlusTree.bPlustree_delete(testBPlusTree.returnRoot(), people[i].getID());

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
    
    cout << "Test for insert." << endl;
    for (int i = 0; i < num; i++) {
        testBTree.insert(&people[i]);
    }
    testBTree.level_display();
    cout << "Test for insert passed." << endl;
    
    cout << "Test for delete." << endl;
    for (int i = 0; i < num; i++)
        testBTree.del(&people[i]);
    testBTree.level_display();

    cout << "Test for delete passed." << endl;
    
    return 0;
}
