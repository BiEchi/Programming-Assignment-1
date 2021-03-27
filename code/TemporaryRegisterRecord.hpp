#ifndef temporaryregisterrecord_hpp
#define temporaryregisterrecord_hpp

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdio>
#include <sstream>
#include "./IOManipulations.hpp"

using namespace std;

class TemporaryRegisterRecord
{
private:
   ofstream outFile;
   ifstream inFile;

public:
   void buildTemporaryRegisterRecord(int userCommandType, char* data);
   void getCommandTypeFromUser(int& userCommandType);
   void chooseTheCorrectCommand(int userCommandType, char* data, bool& exitFlag);
   void writeRoutine(ofstream& outFile, char* data);
   void readRoutine(ifstream& inFile, char* data);
};

#endif
