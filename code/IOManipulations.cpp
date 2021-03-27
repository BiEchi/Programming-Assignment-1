#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdio>
#include <sstream>
#include "./IOManipulations.hpp"
#include "./Person.hpp"
#include "WriteFunctions.hpp"

using namespace std;

void IOManipulations::openTemporaryDataWithWriteMode(ofstream& outFile)
{
   outFile.open("temporaryData.dat", ios::app); // open in APPEND mode
   return;
}

void IOManipulations::writeTemporaryDataWithWriteMode(char* data, ofstream& outFile)
{
   cout << endl << endl << endl << endl << endl << endl;
   cout << "### Register Sheet ###" << endl;
   cout << endl << endl << endl << endl;

   // TODO buggy, this line will NOT show.
   Person person;
   // 第一个数据有关
   WriteFunctions writefunction;
   
   // 到这里为止没有看到给data赋值的语句
   writefunction.writeFunctionTrivial(outFile, data);

   cout << endl << "Enter your ID number." << endl;
   cout << "Example. 330382200002280763" << endl;
   cout << "Sign here. ";
   // 尝试给data赋值
   data = "330382200002280763";
   writefunction.writeFunctionID(outFile, data, person);

   cout << endl << "Enter your name." << endl; 
   cout << "Example. Jack BAI" << endl;
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
    
    cout << endl << "Enter your DOB (Day of Birth) using format YYYY" << endl;
    cout << "Example. 2002" << endl;
    cout << "Sign here. ";
    writefunction.writeFunctionDayOfBirth(outFile, data, person);

   cout << endl << "Enter your MRS (Medical Risk Status) within {0 (no), 1(low), 2(medium), 3(high)}: " << endl;
   cout << "Example. 1" << endl;
   cout << "Sign here. ";
   writefunction.writeFunctionMedicalRiskStatus(outFile, data, person);

   cout << "Your register is recorded." << endl << endl;
   // TODO add person into people (local queue)
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

void IOManipulations::readFunctional(ifstream& inFile, char* data)
{
   inFile.getline(data, 100);
   cout << data << endl;
   return;
}

void IOManipulations::readTemporaryDataWithReadMode(char* data, ifstream& inFile)
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

void IOManipulations::readContentAsVariables(ifstream& inFile, char* data)
{
   return;
}

void IOManipulations::buildTheVectorOfPersonInformationWithIO(char* data)
{
   openTemporaryDataWithReadMode(inFile);
   readContentAsVariables(inFile, data);
   closeTemporaryDataWithReadMode(inFile);
}

void IOManipulations::dumpTemporaryRegisterRecord(char* data)
{
   system(" echo "" > 'temporaryData.dat' ");
   return;
}
