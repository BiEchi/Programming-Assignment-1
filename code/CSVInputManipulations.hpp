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
#include "./PeopleLocalQueue.hpp"

using namespace std;

string Trim(string& str)
{
    str.erase(0, str.find_first_not_of(" \t\r\n"));
    str.erase(str.find_last_not_of(" \t\r\n") + 1);
    return str;
}

void readTheInputCSVIntoPeople(PeopleLocalQueue& localpeople, string type)
{
    cout << "Opening ../database/" << type << endl;
    ifstream inFile("../database/Registration" + type);
    string line;
    
    cout << "Retrieving tuples in database into programme in 3 seconds..." << endl;
    sleep(3);
    
    int i = -1;
    while (getline(inFile, line))
    {
        i++;
        if (i == 0) continue; // escape the schema
        
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
        person.setTreatmentType(Trim(fields[8]));
        
        usleep(10000);
        cout << endl << "Printed the " << i << " person's info:" << endl;
        person.display();
        localpeople.pushBack(&person);
    }
    
    sleep(1);
    cout << endl;
    system("echo '\33[32mSuccessfully retrieved tuples in database into programme.\33[0m' ");
    cout << endl;
    sleep(3);
    
    inFile.close();
    return;
}

#endif /* CSVInputManipulations_hpp */
