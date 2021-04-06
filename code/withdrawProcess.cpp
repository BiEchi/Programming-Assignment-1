#include "withdrawProcess.hpp"
#include <regex>
using namespace std;
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
        int pos = int(patientRecord.find(ID));
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

void withdrawProcess::askUserWithdraw_inPeople(blackList &blackList, PeopleLocalQueue &people, string &filename)
{
    int choice;
    // 用户交互
    do
    {
        cout << "do you want to withdraw?\n1:yes\t2:no" << endl;
        cin >> choice;
        Person *target_person = nullptr;
        switch (choice)
        {
        case 1:
            cout << "=======hello buffer!=========" << endl;
            // loadFileAndFindData(filename, askForID(), recordDataBase, target_person);
            if (nullptr == target_person)
                break;
            // Withdraw the person in people local queue.
            if (people.doWithdraw(target_person))
            {
                blackList.appendPerson(target_person);
            }
            break;
        case 2:
            cout << "you choose to quit the withdraw operation" << endl;
            return;
        default:
            cout << "please press the right number" << endl;
            break;
        }
    } while (choice != 2);
}

void withdrawProcess::askUserWithdraw_inFibonacciPQ(blackList &blackList, FibonacciPQ &centrallist, string &filename)
{
    int choice;
    do
    {
        cout << "do you want to withdraw?\n1:yes\t2:no" << endl;
        cin >> choice;
        Person *target_person = new Person;
        switch (choice)
        {
        case 1:
            cout << "==========hello central Queue========" << endl;
            target_person = loadFileAndFindData(filename, askForID(), recordDataBase);
            if (nullptr == target_person)
                break;

            cout << "the person's ID " << target_person->getID() << endl;
            // Withdraw the person in people central queue.
            centrallist.withdrawInCentral(target_person, blackList);
            delete target_person;
            break;
        case 2:
            cout << "you choose to quit the withdraw operation" << endl;
            return;
        default:
            cout << "please press the right number" << endl;
            break;
        }
    } while (choice != 2);
    return;
}

void withdrawProcess::askUserWithdraw_inHospital(blackList &blacklist, queueManger &hospital, string &filename)
{
    int choice;
    do
    {
        cout << "do you want to withdraw?\n1:yes\t2:no" << endl;
        cin >> choice;
        Person *target_person = nullptr;
        switch (choice)
        {
        case 1:
            cout << "=========hello appointment!========" << endl;
            target_person = loadFileAndFindData(filename, askForID(), recordDataBase);
            if (nullptr == target_person)
                break;

            // Withdraw the person in assignment queues.
            if (hospital.doWithdraw(target_person))
            {
                blacklist.appendPerson(target_person);
            }
            break;
        case 2:
            cout << "you choose to quit the withdraw operation" << endl;
            return;
        default:
            cout << "please press the right number" << endl;
            break;
        }
    } while (choice != 2);
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

// void withdrawProcess::loadFileAndFindData(string &filename, string ID, ifstream &recordfile, Person *target_person)
// {
//     readFile(filename);
//     target_person = findAndReturnPersonPointer(ID, recordDataBase);
//     closeFile(filename);
//     return;
// }

Person* withdrawProcess::loadFileAndFindData(string &filename, string ID, ifstream &recordfile)
{
    Person *target_person = nullptr;
    readFile(filename);
    target_person = findAndReturnPersonPointer(ID, recordDataBase);
    closeFile(filename);
    return target_person;


    // if(nullptr == target_person)
    //     return nullptr;
    // else
    // {
    //     // Person *return_ptr = new Person;
    //     Person *return_ptr = nullptr;
    //     return_ptr = target_person;
    //     return return_ptr;
    // }
}

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
