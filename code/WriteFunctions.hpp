#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdio>
#include <sstream>
#include "./Person.hpp"

using namespace std;

class WriteFunctions
{
public:
    void writeFunctionID(ofstream& outFile, string data, Person& person);
    void writeFunctionName(ofstream& outFile, string data, Person& person);
    void writeFunctionContactDetails(ofstream& outFile, string data, Person& person);
    void writeFunctionProfession(ofstream& outFile, string data, Person& person);
    void writeFunctionYearOfBirth(ofstream& outFile, string data, Person& person);
    void writeFunctionMonthOfBirth(ofstream& outFile, string data, Person& person);
    void writeFunctionDayOfBirth(ofstream& outFile, string data, Person& person);
    void writeFunctionMedicalRiskStatus(ofstream& outFile, string data, Person& person);
};
