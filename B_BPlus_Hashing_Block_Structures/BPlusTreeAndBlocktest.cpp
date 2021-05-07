#include "BPlusTree.h"
#include "BPlusTree.cpp" // delete when make
#include "block.h"
#include "block.cpp" // delete when make
#include "struct.h"
#include "Tree.h"
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
       testTree.bPlustree_insert(testTree.returnRoot(), &people[i]);
    }
    testTree.linear_print();
    cout << "test for right direction delete " << endl;
    for (int i = 0; i < num; i++)
    {
        testTree.bPlustree_delete(testTree.returnRoot(), people[i].getID());
    }

    testTree.linear_print();

    cout << "Test for insert. " << endl;
    for (int i = 0; i < num; i++)
    {
        testTree.bPlustree_insert(testTree.returnRoot(), &people[i]);
    }
    testTree.linear_print();
    cout << "test for deletision in inverse direction " << endl;
    for (int i = num - 1; i >= 0; i--)
    {
        testTree.bPlustree_delete(testTree.returnRoot(), people[i].getID());
    }
    testTree.linear_print();
    return 0;
}

Person *BPlusTree::find(string ID)
{
    return nullptr;
}
