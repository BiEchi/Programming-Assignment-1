//
//  CSVInputManipulations.hpp
//  code
//
//  Created by Jack's Macbook Pro on 2021/5/1.
//

#ifndef CSVInputManipulations_hpp
#define CSVInputManipulations_hpp

#include <iostream>
#include <fstream>
#include <unistd.h>
#include "PeopleLocalQueue.hpp"

using namespace std;

void readTheInputCSVIntoPeople(PeopleLocalQueue& people)
{
    istream& inFile;
    cout << "Opening ../database/People.csv" << endl;
    sleep(1);
    inFile.open("../database/People.csv", ios::app); // open in READ mode
    
    cout << "Writing information to the Registration Relation..." << endl;
    sleep(2);
    system("cp ../database/People.csv ../database/Registration.csv");
    
    cout << "Successfully wrote information to the Registration Relation" << endl;
    sleep(1);
    cout << "You can now go to ../database to find the updated version of Registration.csv file" << endl;
    sleep(1);

    cout << "Retrieving tuples in database into programme..." << endl;
    sleep(3);
    
    // TODO: read CSV file into PeopleLocalQueue people line by line
    for (int i = 0; i < linesInCSVFile; i++)
    {
        string data;
        Person person;
        person.setID(data);
        person.setName(data);
        person.setContactDetails(data);
        person.setProfession(data);
        person.setBirthYear(data);
        person.setBirthMonth(data);
        person.setBirthDay(data);
        person.setRiskStatus(data);
        
        people.pushBack(&person);
    }

    cout << "Successfully retrieved tuples in database into programme." << endl;
    sleep(3);
    
    inFile.close();
    return;
}



#endif /* CSVInputManipulations_hpp */
