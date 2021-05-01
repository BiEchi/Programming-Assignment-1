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
#include <sstream>
#include <string>
#include <vector>
#include <unistd.h>
#include "PeopleLocalQueue.hpp"

using namespace std;

string Trim(string& str)
{
    str.erase(0, str.find_first_not_of(" \t\r\n"));
    str.erase(str.find_last_not_of(" \t\r\n") + 1);
    return str;
}

void readTheInputCSVIntoPeople(PeopleLocalQueue& people)
{
    cout << "Opening ../database/People.csv" << endl;
    sleep(1);
    ifstream inFile("../database/People.csv");
    string line;
    
    cout << "Writing information to the Registration Relation..." << endl;
    sleep(2);
    system("cp ../database/People.csv ../database/Registration.csv");
    
    cout << "Successfully wrote information to the Registration Relation" << endl;
    sleep(1);
    cout << "You can now go to ../database to find the updated version of Registration.csv file" << endl;
    sleep(1);

    cout << "Retrieving tuples in database into programme..." << endl;
    sleep(3);
    
    int i = 0;
    while (getline(inFile, line) && i != 0)
    {
        i++;
        cout << "The initial string is: " << line << endl; // print the original line
        istringstream inString(line);
        vector<string> fields;
        string field;
        while (getline(inString, field, ','))
            fields.push_back(field);
        string name = Trim(fields[0]);
        string age = Trim(fields[1]);
        string birthday = Trim(fields[2]);
        
        Person person;
        person.setID(Trim(fields[0]));
        person.setName(Trim(fields[1]));
        person.setContactDetails(Trim(fields[2]));
        person.setProfession(Trim(fields[3]));
        person.setBirthYear(Trim(fields[4]));
        person.setBirthMonth(Trim(fields[5]));
        person.setBirthDay(Trim(fields[6]));
        person.setRiskStatus(Trim(fields[7]));
        
        person.display();
        people.pushBack(&person);
    }

    cout << "Successfully retrieved tuples in database into programme." << endl;
    sleep(3);
    
    inFile.close();
    return;
}

#endif /* CSVInputManipulations_hpp */
