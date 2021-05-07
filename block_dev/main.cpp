#include <iostream>
#include "block.hpp"
using namespace std;

// Used for testing. 
int test_insert(void)
{
    int num = 10;
    block block0;
    Person people[num];
    for (int i = 0; i < num; i++)
    {
        people[i].setID(i);
    }

    cout << "Test for insert. " << endl;
    cout << "Block0 before insert. " << endl;
    block0.display();
    cout << "Insert tuple with ID 2, 6." << endl;
    block0.insert(&people[2]);
    block0.insert(&people[6]);
    block0.display();
    cout << "Insert tuple with ID 9, 1, 0." << endl;
    block0.insert(&people[9]);
    block0.insert(&people[1]);
    block0.insert(&people[0]);
    block0.display();
    cout << "Insert tuple with ID 5." << endl;
    block0.insert(&people[5]);
    block0.display();
    return 1;
}

int test_remove(void)
{
    int num = 10;
    block block0;
    Person people[num];
    for (int i = 0; i < num; i++)
    {
        people[i].setID(i);
    }

    for (int i = 0; i < 8; i++)
    {
        // Insert tuple_ptr.
        block0.insert(&people[i]);
    }
    cout << "Test for remove. " << endl;
    cout << "Block0 before remove: " << endl;
    block0.display();
    cout << "Remove tuples with ID 2, 4, and 6. " << endl;
    cout << block0.remove(2) << endl;
    cout << block0.remove(4) << endl;
    cout << block0.remove(6) << endl;
    cout << "Block0 after remove. " << endl;
    block0.display();
    return 1;  
}

int test_find()
{
    int num = 10;
    block block0;
    Person people[num];
    for (int i = 0; i < num; i++)
    {
        people[i].setID(i);
    }

    block0.insert(&people[2]);
    block0.insert(&people[6]);
    block0.insert(&people[9]);
    block0.insert(&people[1]);
    block0.insert(&people[0]);
    block0.remove(3);
    block0.remove(2);
    cout << "Test for find. " << endl;
    cout << "Block0 before find. " << endl;
    block0.display();
    Person* temp;
    for (int i = 0; i < num; i++)
    {
        if((temp = block0.find(i)))
        {
            cout << "Find the person with ID: " << temp->getID() << endl;
        }
        else 
        {
            cout << "Did not find the person with ID " << i << ". \n" << endl;
        }
    }
    return 1;     
}

int test_split()
{
    int num = 10;
    block block0;
    Person people[num];
    for (int i = 0; i < num; i++)
    {
        people[i].setID(i);
    }

    // Insert enough tuples to reach the threshold. 
    for (int i = 0; i < 8; i++)
    {
        block0.insert(&people[i]);
    }
    cout << "Test for split. " << endl;
    cout << "Block0 before split. " << endl;
    block0.display();
    cout << "Block0 after insert tuple with ID 9 and split. " << endl;
    block0.insert(&people[9]);
    block0.display();
    cout << "Block1 after split block0. " << endl;
    if (block0.get_next()) {block0.get_next()->display();}
    return 1;
}

int test1_merge()
{
    int num = 10;
    block block0;
    Person people[num];
    for (int i = 0; i < num; i++)
    {
        people[i].setID(i);
    }

    for (int i = 0; i < 9; i++)
    {
        block0.insert(&people[i]);
    }
    cout << "Test 1 for merge: total_num_tuples <= fill_threshold." << endl;
    block0.remove(1);
    block0.insert(&people[0]);
    block0.remove(0);
    block0.insert(&people[1]);
    block0.remove(3);
    block0.get_next()->remove(5);
    block0.get_next()->remove(7);
    block0.get_next()->insert(&people[5]);
    block0.get_next()->insert(&people[7]);

    // Remove engough tuple to reach the threshold. 
    cout << "Block0 before merge. " << endl;
    block0.display();
    cout << "Block1 before merge. " << endl;
    block0.get_next()->display();
    cout << "Remove tuple with ID 1 in block0 should not trigger merge. " << endl;
    block0.remove(1);
    cout << "Block0 after remove. " << endl;
    block0.display();
    cout << "Block1 after remove. " << endl;
    block0.get_next()->display();
    cout << "Remove tuple with ID 2 in block0 to trigger merge. " << endl;
    block0.remove(2);
    cout << "Block0 after merge. " << endl;
    block0.display();
    cout << "The pointer to block1 after merge is " << block0.get_next() << endl;

    return 1;
}

int test2_merge()
{
    int num = 10;
    block block0;
    Person people[num];
    for (int i = 0; i < num; i++)
    {
        people[i].setID(i);
    }

    for (int i = 0; i < 9; i++)
    {
        block0.insert(&people[i]);
    }
    cout << "Test 2 for merge: total_num_tuples > fill_threshold. " << endl;
    // Remove enough tuple to reach the threshold. 
    block0.remove(0);
    block0.remove(1);
    // Insert enough tuple in block1 to make total_num_tuples > fill_threshold. 
    block0.insert(&people[0]);
    block0.get_next()->insert(&people[9]);
    block0.get_next()->insert(&people[1]);
    cout << "Block0 before merge. " << endl;
    block0.display();
    cout << "Block1 before merge. " << endl;
    block0.get_next()->display();
    cout << "Remove tuple with ID 3 in block0 to trigger merge. " << endl;
    block0.remove(3);
    cout << "Block0 after remove. " << endl;
    block0.display();
    cout << "Block1 after remove. " << endl;
    block0.get_next()->display();

    return 1;
}

int test_maximum()
{
    int num = 10;
    block block0;
    Person people[num];
    for (int i = 0; i < num; i++)
    {
        people[i].setID(i);
    }
    cout << "Test for maximum. " << endl;
    block0.insert(&people[5]);
    block0.insert(&people[2]);
    block0.insert(&people[4]);
    block0.insert(&people[1]);
    block0.insert(&people[3]);
    cout << "Block0 before call maximum. " << endl;
    block0.display();
    cout << "The maximum ID in the block is " << block0.maximum() << ". \n";
    block0.remove(1);
    block0.insert(&people[7]);
    cout << "Block0 after insertion and deletion. " << endl;
    block0.display();
    cout << "The maximum ID in the block is " << block0.maximum() << ". \n";

    return 1;
}

int main() {
    // test_insert();
    // test_remove();
    // test_find();
    // test_split();
    // test1_merge();
    // test2_merge();
    // test_maximum();

    return 0;
}