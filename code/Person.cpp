#include <cstring>
#include <ctime>
#include <iostream>
#include <stdio.h>
#include <vector>
#include "Person.hpp"

using namespace std;

void Person::setID(char* data)
{
    ID = data; // automatically convert char* to string
    return;
}

void Person::setName(char* data)
{
    name = data;
    return;
}

void Person::setContactDetails(char* data)
{
    contactDetails = data;
    return;
}

void Person::setBirthdate(char* data)
{

    return;
}

void Person::setProfession(char* data)
{
    string stringData = data;
    bool flag = false;
    switch (stringData)
    {
    case "I":
        profession = professionSet(I);
        flag = true;
        break;

    case "II":
        profession = professionSet(II);
        flag = true;
        break;

    case "III":
        profession = professionSet(III);
        flag = true;
        break;

    case "IV":
        profession = professionSet(IV);
        flag = true;
        break;

    case "V":
        profession = professionSet(V);
        flag = true;
        break;

    case "VI":
        profession = professionSet(VI);
        flag = true;
        break;

    case "VII":
        profession = professionSet(VII);
        flag = true;
        break;

    case "VIII":
        profession = professionSet(VIII);
        flag = true;
        break;
    
    default:
        cout << "Please enter a number ranging from I to VIII." << endl;
        cout << "Do the sheet again." << endl;
        break;
    }
    
    return;
}

// 如何判断person处于哪个阶段？
bool Person::withdraw(vector<Person> *blacklist_ptr)
{
    
}

void Person::setRiskStatus(char* data)
{
    return;
}

void Person::setLocation(char* data)
{
    return;
}

void Person::setTimestamp(char* data)
{
    return;
}