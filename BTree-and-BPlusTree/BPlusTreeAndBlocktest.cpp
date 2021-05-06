#include "BPlusTree.h"
#include "BPlusTree.cpp"
#include "block.h"
#include "block.cpp"
#include "struct.h"
#include "Tree.h"
// Used for testing.
int main()
{
    int num = 400;
    block data;
    BPlusTree testTree = BPlusTree(&data);
    Person people[num];
    block *sec_block;
    for (int i = 0; i < num; i++)
    {
        people[i].setID(to_string(100+i));
    }

    // Test for insert.
    cout << "Test for insert. " << endl;
    for (int i = 0; i < num; i++)
    {
        testTree.bPlustree_insert(testTree.returnRoot(),&people[i]);
    }
    testTree.linear_print();
    return 0;
}