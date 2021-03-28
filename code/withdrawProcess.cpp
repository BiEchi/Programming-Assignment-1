#include "withdrawProcess.hpp"

string withdrawProcess::askForID()
{
    string ID;
    cout << "please enter the ID to be withdrawed " << endl;
    cin >> ID;
    return ID;
}


// 从perment文件中读取数据并存储到内存中
Person *withdrawProcess::findAndReturnPersonPointer(string ID)
{
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
        people.deleteNode(person); // Withdraw the person in people local queue.
        break;
    case centralQueue:
        centralList.withdrawInCentral(person, blackList);
        break;
    case appointment:
        cout << "hello appointment!" << endl;
        hospitals.doWithdraw(person); // Withdraw the person in assignment queues. 
    case Finish:
        cout << "hello Finish!" << endl;
        break;
    default:
        cout << "stage error, please correct the person's stage" << endl;
        break;
    }
    return true;
}

void withdrawProcess::askUserWhetherWithdraw(blackList &blackList, FibonacciPQ &centralList, PeopleLocalQueue &people, queueManger &hospitals)
{
    int choice;
    do
    {
        cout << "do you want to withdraw?\n1:yes 2:no" << endl;
        cin >> choice;
        Person target_person = Person();
        switch (choice)
        {
        case 1:
            target_person = *(findAndReturnPersonPointer(askForID()));
            decideAndOperateWithdraw(&target_person, blackList, centralList, people, hospitals);
            return;
            break;
        case 2:
            return;
            break;
        default:
            cout << "please press the right number" << endl;
            break;
        }
    } while (choice != 2);
    return;
}
