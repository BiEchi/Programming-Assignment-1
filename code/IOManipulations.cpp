#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdio>
#include <sstream>
#include "./IOManipulations.hpp"
#include "./Person.hpp"

using namespace std;

void IOManipulations::openTemporaryDataWithWriteMode(ofstream& outFile)
{
   outFile.open("temporaryData.dat", ios::app); // open in APPEND mode
   return;
}

void IOManipulations::writeFunctional(ofstream& outFile, char* data)
{
   cin.getline(data, 100);
   outFile << data << endl;
   return;
}

void IOManipulations::writeTemporaryDataWithWriteMode(char* data, ofstream& outFile)
{
   cout << endl << endl << endl << endl << endl << endl;
   cout << "### Register Sheet ###" << endl;
   cout << endl << endl << endl << endl;

   // TODO buggy, this line will NOT show.
   writeFunctional(outFile, data);

   cout << endl << "Enter your ID number." << endl;
   cout << "Example. 330382200002280763" << endl;
   cout << "Sign here. ";
   writeFunctionalID(outFile, data);

   cout << endl << "Enter your name." << endl; 
   cout << "Example. Jack BAI" << endl;
   cout << "Sign here. ";
   writeFunctional(outFile, data);

   cout << endl << "Enter your Contact Details from A to G." << endl;
   cout << "Example. D" << endl;
   cout << "Sign here. ";
   writeFunctional(outFile, data);

   cout << endl << "Enter your Profession from I to VIII." << endl;
   cout << "Example. VI" << endl;
   cout << "Sign here. ";
   writeFunctional(outFile, data);

   cout << endl << "Enter your DOB (Date of Birth) using format YYYY-MM-DD" << endl;
   cout << "Example. 2002-02-28" << endl;
   cout << "Sign here. ";
   writeFunctional(outFile, data);

   cout << endl << "Enter your MRS (Medical Risk Status) within {no, low, middle, high}: " << endl;
   cout << "Example. low" << endl;
   cout << "Sign here. ";
   writeFunctional(outFile, data);

   cout << "Your register is recorded." << endl << endl;
   
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