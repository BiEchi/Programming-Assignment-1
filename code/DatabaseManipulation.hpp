//
//  DatabaseManipulation.hpp
//  code
//
//  Created by Jack's Macbook Pro on 2021/5/12.
//

#ifndef DatabaseManipulation_hpp
#define DatabaseManipulation_hpp

#include <iostream>
#include <vector>
#include "PeopleLocalQueue.hpp"
#include "./Database.hpp"

using namespace std;

void readPeopleIntoDatabase(PeopleLocalQueue& people, hospitalDatabase database)
{
    cout << "Adding People into Database..." << endl;
    sleep(1);
    
    vector<Person*> peopleVector = *people.converter();
    for (int i = 0; i < people.getLength(); i++) {
        database.DatabaseInsert(peopleVector[i]);
    }
    
    database.returnBplus()->linear_print();
    database.returnHash()->display();
    
}



#endif /* DatabaseManipulation_hpp */
