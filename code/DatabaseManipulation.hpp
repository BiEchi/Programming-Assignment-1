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
    int receiver;
    vector<Person *> peopleVector = *people.converter();
    cout << "the insert Process will start in 3 seconds" << endl;
    sleep(3);
    for (int i = 0; i < people.getLength(); i++)
    {
        database.DatabaseInsert(peopleVector[i]);
    }
    cout << "Insert successfully, display the information of BPlusTree" << endl;
    cout << "enter random key to print the block list" << endl;
    cin >> receiver;
    database.returnBplus()->linear_print();
    cout << "please enther random key to print hash table" << endl;
    cin >> receiver;
    cout << "display the information of HashTable" << endl;
    database.returnHash()->display();
    cout << "please enter random key to finish database Operation" << endl;
    cin >> receiver;
    return;
}

#endif /* DatabaseManipulation_hpp */
