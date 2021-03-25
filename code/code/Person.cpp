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
    profession = (int) *data;
    return;
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
