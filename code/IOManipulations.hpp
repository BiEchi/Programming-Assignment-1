#ifndef iomanipulations_hpp
#define iomanipulations_hpp

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdio>
#include <sstream>

#include "PeopleLocalQueue.hpp"

using namespace std;

class IOManipulations
{
private:
    ifstream inFile;
    ofstream outFile;

public:
    void openTemporaryDataWithWriteMode(ofstream& outFile);
    void writeTemporaryDataWithWriteMode(string data, ofstream& outFile, PeopleLocalQueue& people);
    void closeTemporaryDataWithWriteMode(ofstream& outFile);
    void openTemporaryDataWithReadMode(ifstream& inFile);
    void readFunctional(ifstream& inFile, string data);
    void readTemporaryDataWithReadMode(string data, ifstream& inFile);
    void closeTemporaryDataWithReadMode(ifstream& inFile);
    void readContentAsVariables(ifstream& inFile, string data);
    void buildTheVectorOfPersonInformationWithIO(string data);
    void dumpTemporaryRegisterRecord(string data);
};

#endif
