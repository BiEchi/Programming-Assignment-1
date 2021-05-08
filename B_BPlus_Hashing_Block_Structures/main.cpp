#include "BPlusTree.cpp" // delete when making
#include "block.cpp" // delete when making
#include "struct.h"
#include "Tree.h"
#include <unistd.h>

// Used for testing.
int main()
{
    int num = 40;
    block data;
    BPlusTree testTree = BPlusTree(&data);
    Person people[num];
    block *sec_block;
   
    for (int i = 0; i < num; i++)
    {
        people[i].setID(to_string(100 + i));
    }

    // Test for insert.
    cout << "Test for insert. " << endl;
    for (int i = 0; i < num; i++)
    {
        usleep(100000);
        testTree.bPlustree_insert(testTree.returnRoot(), &people[i]);
    }
    testTree.linear_print();
    // testTree.level_display();
    cout << "Test for delete. " << endl;
    for (int i = 0; i < num; i++)
    {
        testTree.bPlustree_delete(testTree.returnRoot(), people[i].getID());
    }

    testTree.linear_print();
    cout << "Test for inverse insert. " << endl;
    for (int i = num - 1; i >= 0; i--)
    {
        usleep(100000);
        testTree.bPlustree_insert(testTree.returnRoot(), &people[i]);
    }
    testTree.linear_print();
    // testTree.level_display();
    cout << "test for inverse delete. " << endl;
    for (int i = num - 1; i >= 0; i--)
    {
        testTree.bPlustree_delete(testTree.returnRoot(), people[i].getID());
    }
    testTree.linear_print();
    cout << endl;
    cout << "pass the test successfully!!!!!!!" << endl;
    cout << endl << endl;
    return 0;
}

Person *BPlusTree::find(string ID)
{
    return nullptr;
}
