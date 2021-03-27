#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdio>
#include <sstream>
#include "IOManipulations.hpp"
#include "Person.hpp"
#include "WriteFunctions.hpp"
#include "PeopleLocalQueue.hpp"

using namespace std;

void IOManipulations::openTemporaryDataWithWriteMode(ofstream& outFile)
{
   outFile.open("temporaryData.dat", ios::app); // open in APPEND mode
   return;
}

void IOManipulations::writeTemporaryDataWithWriteMode(string data, ofstream& outFile, PeopleLocalQueue people)
{
    cout << endl << endl << endl << endl << endl << endl;
    cout << "### Register Sheet ###" << endl;
    cout << endl << endl << endl << endl;

    Person person;
    WriteFunctions writefunction;

    cout << endl << "Enter your ID number." << endl;
    cout << "Example. 330382200002280763" << endl;
    cout << "Sign here. ";
    writefunction.writeFunctionID(outFile, data, person);

    cout << endl << "Enter your name with underline instead of space." << endl;
    cout << "Example. Jack_BAI" << endl;
    cout << "Sign here. ";
    writefunction.writeFunctionName(outFile, data, person);

    cout << endl << "Enter your Contact Details (Address) from 1 to 7." << endl;
    cout << "Example. 7" << endl;
    cout << "Sign here. ";
    writefunction.writeFunctionContactDetails(outFile, data, person);

    cout << endl << "Enter your Profession from 1 to 8." << endl;
    cout << "Example. 1" << endl;
    cout << "Sign here. ";
    writefunction.writeFunctionProfession(outFile, data, person);

    cout << endl << "Enter your YOB (Year of Birth) using format YYYY" << endl;
    cout << "Example. 2002" << endl;
    cout << "Sign here. ";
    writefunction.writeFunctionYearOfBirth(outFile, data, person);
    
    cout << endl << "Enter your MOB (Month of Birth) using format MM" << endl;
    cout << "Example. 02" << endl;
    cout << "Sign here. ";
    writefunction.writeFunctionMonthOfBirth(outFile, data, person);
    
    cout << endl << "Enter your DOB (Day of Birth) using format DD" << endl;
    cout << "Example. 17" << endl;
    cout << "Sign here. ";
    writefunction.writeFunctionDayOfBirth(outFile, data, person);

    cout << endl << "Enter your MRS (Medical Risk Status) within {0(no), 1(low), 2(medium), 3(high)}: " << endl;
    cout << "Example. 1" << endl;
    cout << "Sign here. ";
    writefunction.writeFunctionMedicalRiskStatus(outFile, data, person);

    
    cout << "Your register is recorded." << endl;
    cout << "Below is the display of all the information of this person." << endl << endl;
    cout << "PERSON DISPLAY CHECK" << endl << endl;
    person.display();
    
    people.pushBack(person);
    
    return;
}

void IOManipulations::closeTemporaryDataWithWriteMode(ofstream& outFile)
{
   outFile.close();
   return;
}

void IOManipulations::openTemporaryDataWithReadMode(ifstream& inFile)
{
   inFile.open("temporaryData.dat");
   return;
}

void IOManipulations::readFunctional(ifstream& inFile, string data)
{
    cin >> data;
   cout << data << endl;
   return;
}

void IOManipulations::readTemporaryDataWithReadMode(string data, ifstream& inFile)
{
   cout << endl << endl;
   cout << "### Summary of Records ###" << endl; 
   cout << endl << endl;

   while(!inFile.eof())
      readFunctional(inFile, data);
   return;
}

void IOManipulations::closeTemporaryDataWithReadMode(ifstream& inFile)
{
   inFile.close();
   return;
}

void IOManipulations::readContentAsVariables(ifstream& inFile, string data)
{
   return;
}

void IOManipulations::buildTheVectorOfPersonInformationWithIO(string data)
{
   openTemporaryDataWithReadMode(inFile);
   readContentAsVariables(inFile, data);
   closeTemporaryDataWithReadMode(inFile);
}

void IOManipulations::dumpTemporaryRegisterRecord(string data)
{
   system(" echo "" > 'temporaryData.dat' ");
   return;
}
