#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdio>
#include <sstream>
#include "./TemporaryRegisterRecord.hpp"
#include "./Notifications.hpp"
#include "PeopleLocalQueue.hpp"

using namespace std;


void TemporaryRegisterRecord::buildTemporaryRegisterRecord(string data, PeopleLocalQueue& people)
{
    int userCommandType;
    bool exitFlag = false;
    while (exitFlag == false)
    {
       Notifications notification;
       notification.notifyUser();
       getCommandTypeFromUser(userCommandType);
       chooseTheCorrectCommand(userCommandType, data, exitFlag, people);
    }
    return;
}

void TemporaryRegisterRecord::getCommandTypeFromUser(int& userCommandType)
{
   cout << "Your choice is: ";
   cin >> userCommandType;

   return;
}

void TemporaryRegisterRecord::chooseTheCorrectCommand(int userCommandType, string data, bool& exitFlag, PeopleLocalQueue& people)
{
   enum choices {REGISTER=1, READ, FINISH};
   switch (userCommandType)
   {
   case REGISTER:
      cout << "You choose to write in data" << endl;
      writeRoutine(outFile, data, people);
      break;
   case READ:
      cout << "You choose to read from the summary" << endl;
      readRoutine(inFile, data);
      break;
   case FINISH:
      cout << "You choose to finish this part" << endl;
      exitFlag = true;
      break;
   default:
      cout << "You are required to enter a number ranging in [1,3]." << endl;
      exitFlag = true;
      break;
   }

   return;
}

void TemporaryRegisterRecord::writeRoutine(ofstream& outFile, string data, PeopleLocalQueue& people)
{
   IOManipulations writeManipulation;
   writeManipulation.openTemporaryDataWithWriteMode(outFile);
   writeManipulation.writeTemporaryDataWithWriteMode(data, outFile, people);
   writeManipulation.closeTemporaryDataWithWriteMode(outFile);

   return;
}

void TemporaryRegisterRecord::readRoutine(ifstream& inFile, string data)
{
   IOManipulations readManipulation;
   readManipulation.openTemporaryDataWithReadMode(inFile);
   readManipulation.readTemporaryDataWithReadMode(data, inFile);
   readManipulation.closeTemporaryDataWithReadMode(inFile);

   return;
}