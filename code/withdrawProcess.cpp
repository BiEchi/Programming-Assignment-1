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
Person *withdrawProcess::findAndReturnPersonPointer(string ID, ifstream &recordFile)
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

bool withdrawProcess::decideAndOperateWithdraw(Person *person, blackList &blackList, FibonacciPQ &centralList, PeopleLocalQueue &people, queueManger &hospitals)
{
    switch (person->getcurrentStage())
    {
    case nonebuffer:
        cout << "you haven't been added into the system" << endl;
        break;
    case buffer:
        cout << "hello buffer!" << endl;
        if (people.doWithdraw(person)) {blackList.appendPerson(person);} // Withdraw the person in people local queue.
        break;
    case centralQueue:
        centralList.withdrawInCentral(person, blackList);
        break;
    case appointment:
        cout << "hello appointment!" << endl;
        if (hospitals.doWithdraw(person)) {blackList.appendPerson(person);}  // Withdraw the person in assignment queues. 
    case Finish:
        cout << "you have finished our service, so you cannot withdraw" << endl;
        break;
    default:
        cout << "stage error, please correct the person's stage" << endl;
        break;
    }
    return true;
}

void withdrawProcess::askUserWhetherWithdraw(blackList &blackList, FibonacciPQ &centralList, PeopleLocalQueue &people, queueManger &hospitals, string filename)
{
    int choice;
    recordDataBase.open(filename, ios::in);
    if (!recordDataBase.is_open())
    {
        cout << "open file in withdraw operation failed" << endl;
        return;
    }
    do
    {
        cout << "do you want to withdraw?\n1:yes 2:no" << endl;
        cin >> choice;
        Person target_person = Person();
        switch (choice)
        {
        case 1:
            target_person = *(findAndReturnPersonPointer(askForID(), recordDataBase));
            decideAndOperateWithdraw(&target_person, blackList, centralList, people, hospitals);
            return;
            break;
        case 2:
            cout << "you choose to quit the withdraw operation" << endl;
            return;
            break;
        default:
            cout << "please press the right number" << endl;
            break;
        }
    } while (choice != 2);
    recordDataBase.close();
    return;
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
