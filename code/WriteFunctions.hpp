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
    void writeFunctionTrivial(ofstream& outFile, char* data);
    void writeFunctionID(ofstream& outFile, char* data, Person person);
    void writeFunctionName(ofstream& outFile, char* data, Person person);
    void writeFunctionContactDetails(ofstream& outFile, char* data, Person person);
    void writeFunctionProfession(ofstream& outFile, char* data, Person person);
    void writeFunctionDateOfBirth(ofstream& outFile, char* data, Person person);
    void writeFunctionMedicalRiskStatus(ofstream& outFile, char* data, Person person);
}