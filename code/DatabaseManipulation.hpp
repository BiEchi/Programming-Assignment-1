//
//  DatabaseManipulation.hpp
//  code
//
//  Created by Jack's Macbook Pro on 2021/5/12.
//

#ifndef DatabaseManipulation_hpp
#define DatabaseManipulation_hpp

#include <iostream>
#include <type_traits>
#include <unistd.h>
#include <vector>
#include "PeopleLocalQueue.hpp"
#include "./Database.hpp"

using namespace std;

void readPeopleIntoDatabase(PeopleLocalQueue &people, hospitalDatabase database)
{
    cout << "Adding People into Database..." << endl;
    sleep(1);
    vector<Person *> peopleVector = *people.converter();
    cout << "the insert Process will start in 3 seconds" << endl;
    sleep(3);
    for (int i = 0; i < people.getLength(); i++)
        database.DatabaseInsert(peopleVector[i]);
    cout << "Insert successfully, display the information of BPlusTree" << endl;
    cout << "Checkpoint 1. Click any key to print the block list" << endl;
    getchar();
    database.returnBplus()->linear_print();
    cout << "Checkpoint 2. Click any key to print hash table" << endl;
    getchar();
    cout << "displaying the information of HashTable" << endl;
    database.returnHash()->display();
    cout << "Checkpoint 3. Click any key to finish database Operation" << endl;
    getchar();
    return;
}

#endif /* DatabaseManipulation_hpp */
