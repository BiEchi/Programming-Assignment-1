#include "BPlusTree.h"
// #include "BPlusTree.cpp" // delete when GNU making
#include "block.h"
// #include "block.cpp" // delete when GNU making
// #include "BTree.h"
// #include "BPlusTree.cpp" // delete when GNU making
#include "struct.h"
#include "Tree.h"

#include <unistd.h>
#include <iostream>

// Used for testing.
int main()
{
    int num = 40;
    block data;
    BPlusTree testTree = BPlusTree(&data);
    Person people[num];
   
    cout << "Now we go into B+ Tree test in 1 second..." << endl;
    sleep(1);
    for (int i = 0; i < num; i++)
    {
        people[i].setID(to_string(100 + i));
    }

    cout << "Test for insert. " << endl;
    sleep(1);
    for (int i = 0; i < num; i++)
    {
        usleep(100000);
        testTree.bPlustree_insert(testTree.returnRoot(), &people[i]);
    }
    testTree.linear_print();
    // testTree.level_display();
    
    cout << "Test for delete. " << endl;
    sleep(1);
    for (int i = 0; i < num; i++)
    {
        testTree.bPlustree_delete(testTree.returnRoot(), people[i].getID());
    }

    testTree.linear_print();
    cout << "Test for inverse insert. " << endl;
    sleep(1);
    for (int i = num - 1; i >= 0; i--)
    {
        usleep(100000);
        testTree.bPlustree_insert(testTree.returnRoot(), &people[i]);
    }
    testTree.linear_print();
    // testTree.level_display();
    
    cout << "test for inverse delete. " << endl;
    sleep(1);
    for (int i = num - 1; i >= 0; i--)
    {
        testTree.bPlustree_delete(testTree.returnRoot(), people[i].getID());
    }
    testTree.linear_print();
    cout << endl;
    cout << "Pass the B+ test successfully." << endl;
    cout << endl << endl;
    
    cout << "Now we go into B Tree test in 1 second..." << endl;
    sleep(1);
    
    
    
    return 0;
}

Person *BPlusTree::find(string ID)
{
    return nullptr;
}
