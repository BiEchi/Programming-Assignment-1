#include "withdrawProcess.hpp"
#include <regex>
using namespace std;

// split the string by some signs and store it in the vector object and then return that
// in: the string object
// delim: spliting sings
vector<string> withdrawProcess::s_split(const string &in, const string &delim)
{
    regex re{delim};
    return vector<string>{
        sregex_token_iterator(in.begin(), in.end(), re, -1),
        sregex_token_iterator()};
}

string withdrawProcess::askForID()
{
    string ID;
    cout << "please enter the ID to be withdrawed " << endl;
    cin >> ID;
    return ID;
}

// 从perment文件中读取数据并存储到内存中
Person *withdrawProcess::findAndReturnPersonPointer(string &ID, ifstream &recordFile)
{
    Person *blacklistMember = new Person;
    vector<string> recordinfo;
    // string newID, newName, newContactDetails,newBirthYear,newBirthMonth,newBirthDay,newProfession,newRiskStatus;
    string patientRecord;
    if (!recordFile.is_open())
        return nullptr;
    while (getline(recordFile, patientRecord))
    {
        int pos = patientRecord.find(ID);
        if (pos > -1)
        {
            cout << "succefully find the patient " << ID << " in the database" << endl;
            // 从一行中读取数据
            recordinfo = s_split(patientRecord, " ");
            blacklistMember->setID(recordinfo[id]);
            blacklistMember->setName(recordinfo[name]);
            blacklistMember->setContactDetails(recordinfo[Address]);
            blacklistMember->setProfession(recordinfo[Profession]);
            blacklistMember->setBirthYear(recordinfo[YOB]);
            blacklistMember->setBirthMonth(recordinfo[MOB]);
            blacklistMember->setBirthDay(recordinfo[DOB]);
            blacklistMember->setRiskStatus(recordinfo[MAR]);
            cout << "finish loading the data" << endl;
            return blacklistMember;
        }
    }
    cout << "We do not find the person " << ID << endl;
    return nullptr;
}

void withdrawProcess::askUserWithdraw_inPeople(blackList &blackList, PeopleLocalQueue &people, Person *finding_obj)
{
    return;
}

void withdrawProcess::askUserWithdraw_inFibonacciPQ(blackList &blackList, FibonacciPQ &centrallist, Person *finding_obj)
{
    cout << "==========hello central Queue========" << endl;
    list<Person *> start = centrallist.getRootlist();
    Person *targetPerson = centrallist.find(finding_obj, start);
    if (nullptr == targetPerson)
    {
        cout << "sorry we do not find the person in central Queue" << endl;
        return;
    }
    // Withdraw the person in people central queue.
    centrallist.withdrawInCentral(targetPerson, blackList);
    return;
}

void withdrawProcess::askUserWithdraw_inHospital(blackList &blacklist, queueManger &hospital, Person *finding_obj)
{
    return;
}

void withdrawProcess::readFile(string &filename)
{
    recordDataBase.open(filename, ios::in);
    if (!recordDataBase.is_open())
    {
        cout << "open file in withdraw operation failed" << endl;
        return;
    }
    return;
}

void withdrawProcess::closeFile(string &filename)
{
    recordDataBase.close();
    return;
}

Person *withdrawProcess::loadFileAndFindData(string &filename, string ID, ifstream &recordfile)
{
    Person *targetPerson = nullptr;
    readFile(filename);
    targetPerson = findAndReturnPersonPointer(ID, recordDataBase);
    closeFile(filename);
    return targetPerson;
}

void withdrawProcess::withdrawAdvanced(blackList &blackList, PeopleLocalQueue &people, FibonacciPQ &centralList, queueManger &hospital, string &filename)
{
    int choice;
    do
    {
        cout << "do you want to withdraw ?" << endl;
        cout << "1:yes 2:no" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            Person *targetPerson = loadFileAndFindData(filename, askForID(), recordDataBase);
            askUserWithdraw_inFibonacciPQ(blackList, centralList, targetPerson);
            askUserWithdraw_inPeople(blackList);
            askUserWithdraw_inHospital(blackList);
            break;
        case 2:
            break;
        default:
            cout << "please enter the right number" << endl;
            break;
        }
    } while (choice != 2);
}
