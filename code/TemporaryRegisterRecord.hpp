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
   void buildTemporaryRegisterRecord(string data, PeopleLocalQueue& people);
   void getCommandTypeFromUser(int& userCommandType);
   void chooseTheCorrectCommand(int userCommandType, string data, bool& exitFlag, PeopleLocalQueue& people);
   void writeRoutine(ofstream& outFile, string data, PeopleLocalQueue& people);
   void readRoutine(ifstream& inFile, string data);
};

#endif
