#ifndef database_h
#define database_h
#include <cstring>
#include <ctime>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <list>
#include <math.h>
using namespace std;

class Person {
public:
  friend class FibonacciPQ;

    string getName(void) {return name;}
    string getID(void) {return ID;}
    string getContactDetails(void) {return contactDetails;}
    tm getBirthdate(void) {return birthDate;}
    tm getTimestamp(void) {return timeStamp;}
    int getProfession(void) {return profession;}
    int getRiskStatus(void) {return riskStatus;}

    void setID(string data);
    void setName(string data);
    void setContactDetails(string data);
    void setBirthYear(string data);
    void setBirthMonth(string data);
    void setBirthDay(string data);
    void setTimestamp(string data);
    void setProfession(string data);
    void setRiskStatus(string data);
    
    void display();

  //Jiahao
  bool assignTime(void);
  //liyang
  bool withdraw(vector<Person> *blacklist_ptr);
  //baihao
  bool init();
  // yi_hong
  bool isLargerThan(Person person);

  string ID;
 private:
  string name;
  string contactDetails;
  tm birthDate;
  tm timeStamp;
  int profession, riskStatus;
  int location;
  //Jiahao
  tm appointmentTime;
  // added by Liyang in 3.19
  bool Store = true;
  int Degree = 0;
  bool CutMark = false;
  list<Person*> Son = list<Person*>();
  Person *Parent = nullptr;
  // added by Li_yang in 3.25
  int Key = 0;
};

class FibonacciPQ
{
    // API functions
public:
    FibonacciPQ()
    {
        PQlength = 0;
        BucketLength = 10;
        Minptr = NULL;
        Rootlist = list<Person *>();
        Degreebucket = vector<Person *>(10, NULL);
        Rootsize = 0;
    }
    int  returnLength();
    bool isEmpty();
    bool inSert(Person *handle);
    Person *remove(Person *handle);
    Person *popMin();
    Person *decreaseKey(Person *handle, int k);

private:
    Person *link(Person *a_prt, Person *b_ptr);
    void rebalance();
    void addSonPerson(Person *sonPerson, Person *parentPerson);
    void cut(Person *sonPerson, Person *parentPerson);
    void newPerson(Person *newroot);
    bool cascadingCut(Person *parent);

    int PQlength;
    int BucketLength;
    int Rootsize;
    Person *Minptr; // the ptr pointing to the root having min Key in the list.
    // 初始时造个空的
    list<Person *> Rootlist; //creating a Rootlist to store the root
    vector<Person *> Degreebucket;
};

#endif
