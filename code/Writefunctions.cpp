#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdio>
#include <sstream>
#include "./IOManipulations.hpp"
#include "./Person.hpp"
#include "./WriteFunctions.hpp"

using namespace std;

void WriteFunctions::writeFunctionID(ofstream& outFile, string data, Person& person)
{
    cin >> data;
    outFile << data << endl;
    person.setID(data);
    return;
}

void WriteFunctions::writeFunctionName(ofstream& outFile, string data, Person& person)
{
    cin >> data;
    outFile << data << endl;
    person.setName(data);
    return;
}

void WriteFunctions::writeFunctionContactDetails(ofstream& outFile, string data, Person& person)
{
    cin >> data;
    outFile << data << endl;
    person.setContactDetails(data);
    return;
}

void WriteFunctions::writeFunctionProfession(ofstream& outFile, string data, Person& person)
{
    cin >> data;
    outFile << data << endl;
    person.setProfession(data);
    return;
}

void WriteFunctions::writeFunctionYearOfBirth(ofstream& outFile, string data, Person& person)
{
    cin >> data;
    outFile << data << endl;
    person.setBirthYear(data);
    return;
}

void WriteFunctions::writeFunctionMonthOfBirth(ofstream& outFile, string data, Person& person)
{
    cin >> data;
    outFile << data << endl;
    person.setBirthMonth(data);
    return;
}

void WriteFunctions::writeFunctionDayOfBirth(ofstream& outFile, string data, Person& person)
{
    cin >> data;
    outFile << data << endl;
    person.setBirthDay(data);
    return;
}

void WriteFunctions::writeFunctionMedicalRiskStatus(ofstream& outFile, string data, Person& person)
{
    cin >> data;
    outFile << data << endl;
    person.setRiskStatus(data);
    return;
}
