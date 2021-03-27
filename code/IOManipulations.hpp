#ifndef iomanipulations_hpp
#define iomanipulations_hpp

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdio>
#include <sstream>

using namespace std;

class IOManipulations
{
private:
    ifstream inFile;
    ofstream outFile;

public:
    void openTemporaryDataWithWriteMode(ofstream& outFile);
    void writeTemporaryDataWithWriteMode(char* data, ofstream& outFile);
    void closeTemporaryDataWithWriteMode(ofstream& outFile);
    void openTemporaryDataWithReadMode(ifstream& inFile);
    void readFunctional(ifstream& inFile, char* data);
    void readTemporaryDataWithReadMode(char* data, ifstream& inFile);
    void closeTemporaryDataWithReadMode(ifstream& inFile);
    void readContentAsVariables(ifstream& inFile, char* data);
    void buildTheVectorOfPersonInformationWithIO(char* data);
    void dumpTemporaryRegisterRecord(char* data);
};

#endif
