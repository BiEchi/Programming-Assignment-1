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
    system("cp ../database/People.csv ../database/Registration.csv");
    sleep(2);
    
    system("echo '\33[32mSuccessfully wrote information to the Registration Relation.\33[0m' ");
    sleep(1);
    
    cout << "You can now go to ../database to find the updated version of Registration.csv file" << endl;
    sleep(1);

    cout << "Retrieving tuples in database into programme in 3 seconds..." << endl;
    sleep(3);
    
    int i = -1;
    while (getline(inFile, line))
    {
        i++;
        if (i == 0) continue; // escape the schema
        
        cout << "The initial string is: " << line << endl; // print the original line
        istringstream inString(line);
        vector<string> fields;
        string field;
        while (getline(inString, field, ','))
            fields.push_back(field);
        
        Person person;
        person.setID(Trim(fields[0]));
        person.setName(Trim(fields[1]));
        person.setContactDetails(Trim(fields[2]));
        person.setProfession(Trim(fields[3]));
        person.setBirthYear(Trim(fields[4]));
        person.setBirthMonth(Trim(fields[5]));
        person.setBirthDay(Trim(fields[6]));
        person.setRiskStatus(Trim(fields[7]));
        
        usleep(10000);
        cout << endl << "Printed the " << i << "/500 person's info:" << endl;
        person.display();
        people.pushBack(&person);
    }

    sleep(1);
    cout << endl;
    system("echo '\33[32m ### Successfully retrieved tuples in database into programme. ### \33[0m' ");
    cout << endl;
    sleep(3);
    
    inFile.close();
    return;
}

#endif /* CSVInputManipulations_hpp */
