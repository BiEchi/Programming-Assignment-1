#include <iostream>
#include "../code/block.cpp"
#include "../code/BPlusTree.cpp"
#include "../code/Person.cpp"
#include "../code/BTree.cpp"

#include "../code/block.hpp"
#include "../code/BPlusTree.hpp"
#include "../code/Person.hpp"
#include "../code/BTree.hpp"

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
    Person people[num];
    BTree testBtree = BTree(testBPlusTree);

    for (int i = 0; i < num; i++)
    {
        people[i].setID(to_string(100 + i));
        people[i].setName(to_string(100 + i));
    }

    cout << "Now we go into B+ Tree test in 1 second..." << endl;


    cout << "Test for inverse insert. " << endl;
    for (int i = num - 1; i >= 0; i--)
    {
        testBPlusTree.bPlustree_insert(testBPlusTree.returnRoot(), &people[i]);
        testBtree.insert(&people[i]);
    }
    testBPlusTree.linear_print();
    testBtree.print();

    cout << "test for inverse delete." << endl;
    for (int i = num - 1; i >= 0; i--)
    {
        testBtree.del(&people[i]);
        testBPlusTree.bPlustree_delete(testBPlusTree.returnRoot(), people[i].getID());
    }
    testBPlusTree.linear_print();
    testBtree.print();

    cout << "waitting for 3 seconds to begin the second test" << endl;
    sleep(3);

    cout << "Test for insert. " << endl;
    for (int i = 0; i < num; i++)
    {
        testBPlusTree.bPlustree_insert(testBPlusTree.returnRoot(), &people[i]);
        testBtree.insert(&people[i]);
    }
    testBPlusTree.linear_print();
    testBtree.print();

    cout << "Test for delete. " << endl;
    for (int i = 0; i < num; i++)
    {
        testBtree.del(&people[i]);
        testBPlusTree.bPlustree_delete(testBPlusTree.returnRoot(), people[i].getID());
    }
    testBPlusTree.linear_print();
    testBtree.print();

    cout << "test for linear finding" << endl;
    cout << endl;
    cout << "Pass the B+ test successfully." << endl;
    cout << endl
         << endl;
    return 0;
}
