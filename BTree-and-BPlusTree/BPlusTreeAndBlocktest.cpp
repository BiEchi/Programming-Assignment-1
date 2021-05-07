#include "BPlusTree.h"
#include "BPlusTree.cpp"
#include "block.h"
#include "block.cpp"
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
        cout << "the insert person's ID is " << testTree.bPlustree_insert(testTree.returnRoot(), &people[i])->getID() << endl;
    }

    cout << "test for right direction delete " << endl;
    for (int i = 0; i < num; i++)
    {
        testTree.bPlustree_delete(testTree.returnRoot(), people[i].getID())->getID();
    }

    testTree.linear_print();

    cout << "Test for insert. " << endl;
    for (int i = 0; i < num; i++)
    {
        testTree.bPlustree_insert(testTree.returnRoot(), &people[i])->getID();
    }
    cout << "test for inverse direction " << endl;
    for (int i = num - 1; i >= 0; i--)
    {
        testTree.bPlustree_delete(testTree.returnRoot(), people[i].getID())->getID();
    }
    return 0;
}