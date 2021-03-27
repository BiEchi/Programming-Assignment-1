#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdio>
#include <sstream>
#include "./IOManipulations.hpp"
#include "./Person.hpp"
#include "./WriteFunctions.hpp"

using namespace std;

void WriteFunctions::writeFunctionTrivial(ofstream& outFile, char* data)
{
    cin.getline(data, 100);
    outFile << data << endl;
    return; 
}

void WriteFunctions::writeFunctionID(ofstream& outFile, char* data, Person person)
{
    cin.getline(data, 100);
    outFile << data << endl;
    person.setID(data);
    return;
}

void WriteFunctions::writeFunctionName(ofstream& outFile, char* data, Person person)
{
    cin.getline(data, 100);
    outFile << data << endl;
    person.setName(data);
    return;
}

void WriteFunctions::writeFunctionContactDetails(ofstream& outFile, char* data, Person person)
{
    cin.getline(data, 100);
    outFile << data << endl;
    person.setContactDetails(data);
    return;
}

void WriteFunctions::writeFunctionProfession(ofstream& outFile, char* data, Person person)
{
    cin.getline(data, 100);
    outFile << data << endl;
    person.setProfession(data);
    return;
}

void WriteFunctions::writeFunctionYearOfBirth(ofstream& outFile, char* data, Person person)
{
    cin.getline(data, 100);
    outFile << data << endl;
    person.setBirthYear(data);
    return;
}

void WriteFunctions::writeFunctionMonthOfBirth(ofstream& outFile, char* data, Person person)
{
    cin.getline(data, 100);
    outFile << data << endl;
    person.setBirthMonth(data);
    return;
}

void WriteFunctions::writeFunctionDayOfBirth(ofstream& outFile, char* data, Person person)
{
    cin.getline(data, 100);
    outFile << data << endl;
    person.setBirthDay(data);
    return;
}

void WriteFunctions::writeFunctionMedicalRiskStatus(ofstream& outFile, char* data, Person person)
{
    cin.getline(data, 100);
    outFile << data << endl;
    person.setRiskStatus(data);
    return;
}
