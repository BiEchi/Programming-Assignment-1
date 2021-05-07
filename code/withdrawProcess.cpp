#include "withdrawProcess.hpp"
#include <regex>
#include <unistd.h>
using namespace std;

// split the string by some signs and store it in the vector object and then return that
// in: the string object
// delim: spliting sings

// string withdrawProcess::askForID()
// {
//     string ID;
//     cout << "please enter the ID to be withdrawed " << endl;
//     cin >> ID;
//     return ID;
// }

// bool withdrawProcess::askUserWithdraw_inPeople(blackList &blackList, PeopleLocalQueue &people, Person *finding_obj)
// {
//     // cout << "================hello people================" << endl;
//     Person *targetPerson = people.isIn(finding_obj->getID());
//     if (nullptr == targetPerson)
//     {
//         // cout << "we do not find the person in people" << endl;
//         return false;
//     }
//     people.doWithdraw(targetPerson);
//     blackList.appendPerson(targetPerson);
//     return true;
// }

// bool withdrawProcess::askUserWithdraw_inFibonacciPQ(blackList &blackList, FibonacciPQ &centrallist, Person *finding_obj)
// {
//     // cout << "==========hello central Queue========" << endl;
//     list<Person *> start = centrallist.getRootlist();
//     Person *targetPerson = centrallist.find(finding_obj, start);
//     if (nullptr == targetPerson)
//     {
//         // cout << "sorry we do not find the person in central Queue" << endl;
//         return false;
//     }
//     // Withdraw the person in people central queue.
//     centrallist.withdrawInCentral(targetPerson, blackList);
//     return true;
// }

// bool withdrawProcess::askUserWithdraw_inHospital(blackList &blacklist, queueManger &hospital, Person *finding_obj)
// {
//     // cout << "==============hello hospital=============" << endl;
//     Person *targetPerson = hospital.isIn(finding_obj->getID());
//     if (nullptr == targetPerson)
//     {
//         // cout << "sorry we do not find the person in hospital queue" << endl << endl;
//         return false;
//     }
//     blacklist.appendPerson(targetPerson);
//     return true;
// }

// void withdrawProcess::withdrawAdvanced(blackList &blackList, PeopleLocalQueue &people, FibonacciPQ &centralList, queueManger &hospital, string &filename)
// {
//     int choice;
//     do
//     {
//         cout << "do you want to withdraw ?" << endl;
//         cout << "1:yes 2:no" << endl;
//         cin >> choice;
//         switch (choice)
//         {
//         case 1:
//         {
//             Person *target_Person = loadFileAndFindData(filename, askForID());
//             if (nullptr == target_Person)
//                 break;
//             askUserWithdraw_inFibonacciPQ(blackList, centralList, target_Person);
//             askUserWithdraw_inPeople(blackList, people, target_Person);
//             askUserWithdraw_inHospital(blackList, hospital, target_Person);
//             break;
//         }
//         case 2:
//             cout << "you chooose to quit" << endl;
//             return;
//         default:
//             cout << "please enter the right number" << endl;
//             break;
//         }
//     } while (choice != 2);
// }

vector<string> withdrawProcess::s_split(const string &in, const string &delim)
{
    regex re{delim};
    return vector<string>{
        sregex_token_iterator(in.begin(), in.end(), re, -1),
        sregex_token_iterator()};
}

// 从perment文件中读取数据并存储到内存中
Person *withdrawProcess::findAndReturnPersonPointer(string &ID)
{
    Person *blacklistMember = new Person;
    vector<string> recordinfo;
    // string newID, newName, newContactDetails,newBirthYear,newBirthMonth,newBirthDay,newProfession,newRiskStatus;
    string patientRecord;
    if (!recordDataBase.is_open())
        return nullptr;
    while (getline(recordDataBase, patientRecord))
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

Person *withdrawProcess::loadFileAndFindData(string &filename, string ID)
{
    Person *targetPerson = nullptr;
    readFile(filename);
    targetPerson = findAndReturnPersonPointer(ID);
    closeFile(filename);
    return targetPerson;
}

void withdrawProcess::withdrawDemo(blackList &blackList, PeopleLocalQueue &people, FibonacciPQ &centralList, queueManger &hospital, string &filename)
{
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
    cout << "this is the demo part for withdraw operation" << endl;
    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
    cout << "Here we will withdraw the five patients in the data base" << endl;
    // cout << "1 in local queue, 3 in central queue and 1 in assignment queue" << endl;
    vector<string> IDset;
    string record;

    // 加载信息
    readFile(filename);
    for (int i = 0; i < 4; i++)
    {
        if (getline(recordDataBase, record))
            IDset.push_back(s_split(record, " ")[id]);
        else
        {
            cout << "do not have enough data" << endl;
            break;
        }
    }
    closeFile(filename);

    // 显示将要删除的ID的信息
    cout << "the id is ";
    for (auto i = IDset.begin(); i != IDset.end(); i++)
    {
        cout << (*i) << " ";
    }
    cout << endl;
    // 显示withdraw前的各结构数量
    cout << "local queue has record " << people.getLength();
    cout << " central list has record " << centralList.returnLength();
    cout << " assignment queue has record " << hospital.getlength();
    // 在三个结构中查找id并withdraw
    Person *targetPerson = nullptr;
    list<Person *> start = centralList.getRootlist();
    for (auto i = IDset.begin(); i != IDset.end(); i++)
    {
        if (targetPerson = people.isIn((*i)))
            people.doWithdraw(targetPerson);
        else if (!(start.empty()) && (targetPerson = centralList.find((*i), start)))
            centralList.withdrawInCentral(targetPerson, blackList);
        else if (targetPerson = hospital.isIn((*i)))
            hospital.doWithdraw(targetPerson);
        else
        {
            cout << "we don't find the person with id " << (*i) << " in the database" << endl;
            continue;
        }
        blackList.appendPerson(targetPerson);
    }
    cout << "after withdrawing, each structure has the record number: " << endl;
    cout << "local queue has record " << people.getLength();
    cout << " central list has record " << centralList.returnLength();
    cout << " assignment queue has record " << hospital.getlength();
    return;
}