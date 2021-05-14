
#include "./operationRoutineForMain.hpp"

using namespace std;

// global variables
time_t startTime = time(NULL);
block blockList;
BPlusTree bPlusTree(&blockList);
BTree bTree;
HashMap hashMap;
hospitalDatabase database(bPlusTree, bTree, hashMap);
blackList blackListRegister = blackList();
FibonacciPQ central_Queue = FibonacciPQ();
PeopleLocalQueue people;
withdrawProcess withdrawProm;

int main() {
    people.init();
    queueManger localHospitals;  // appointment queues
    
    /* Introduction Part */
    
    sleep(1);
    cout << "This is the presentation code for Computing Assignment 2, with "
    "authors Hao BAI, Liyang QIAN, Jiahao WEI and Yihong JIN."
    << endl;
    sleep(1);
    system(
           "echo '\033[41m\033[37m\033[1m\033[4m ### The presentation starts in 1 "
           "second... ### \33[0m' ");
    sleep(1);
    
    /* Operation Routine for Treatment Type 1 */

    system(
           "echo '\033[41m\033[37m\033[1m\033[4mReading the input CSV file into "
           "People Local Queue...\33[0m' ");
    sleep(1);
    
    operationRoutine(startTime, blockList, database
                     , blackListRegister, central_Queue, people
                     , withdrawProm, localHospitals, "Emergency1.csv");
    
    operationRoutine(startTime, blockList, database
                     , blackListRegister, central_Queue, people
                     , withdrawProm, localHospitals, "Inbed2.csv");
    
    operationRoutine(startTime, blockList, database
                     , blackListRegister, central_Queue, people
                     , withdrawProm, localHospitals, "Vaccine3.csv");
    
    system("echo '\33[32mGenerating monthly report to report.txt ...\33[0m' ");
    Reporting_monthly(localHospitals.treated_list,
                      central_Queue.returnStorePeople(),
                      localHospitals.assignment_list, blackListRegister);
    sleep(1);
    system(
           "echo '\33[32mSuccessfully generated the report file. "
           "Go to ./report.txt to check.\33[0m' ");
    sleep(1);
    
    /* Query Operations */
    
    system(
           "echo '\033[41m\033[37m\033[1m\033[4m ### Query for Exercise 4 "
           "starting... ### \33[0m' ");
    sleep(1);
    query(hashMap);
    sleep(1);
    system(
           "echo '\33[32mSuccessfully generated the query about thresholds.\33[0m' ");
    
    system(
           "echo '\033[32m\033[37m\033[1m\033[4mThe programme ends with exit flag "
           "EXIT_SUCCESS\33[0m' ");
    sleep(1);
    return EXIT_SUCCESS;
}
