#ifndef database_h
#define database_h
#include <math.h>
#include <stdio.h>

#include <cstring>
#include <ctime>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

class Person {
 public:
  friend class FibonacciPQ;

  string getName(void) { return name; }
  string getID(void) { return ID; }
  string getContactDetails(void) { return contactDetails; }
  tm getBirthdate(void) { return birthDate; }
  tm getTimestamp(void) { return timeStamp; }
  int getProfession(void) { return profession; }
  int getRiskStatus(void) { return riskStatus; }
  int getLocation(void) { return location; }

  void setID(char *data);
  void setName(char *data);
  void setContactDetails(char *data);
  void setBirthYear(char *data);
  void setBirthMonth(char *data);
  void setBirthDay(char *data);
  void setTimestamp(char *data);
  void setProfession(char *data);
  void setRiskStatus(char *data);
  void setLocation(char *data);

  // Jiahao
  bool assignTime(void);
  // liyang
  bool withdraw(vector<Person> *blacklist_ptr);
  // baihao
  bool init();
  // yihong
  bool isLargerThan(Person person);

 private:
  string ID;
  string name;
  string contactDetails;
  tm birthDate;
  tm timeStamp;
  int profession, riskStatus;
  int location;
  int ageGroup;
  // Jiahao
  tm appointmentTime;
  // added by Liyang in 3.19
  bool Store = true;
  int Degree = 0;
  bool CutMark = false;
  list<Person *> Son = list<Person *>();
  Person *Parent = nullptr;
};

class FibonacciPQ {
  // API functions
 public:
  FibonacciPQ() {
    PQlength = 0;
    BucketLength = 10;
    Minptr = NULL;
    Rootlist = list<Person *>();
    Degreebucket = vector<Person *>(10, NULL);
    Rootsize = 0;
  }
  int returnLength();
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
  Person *Minptr;  // the ptr pointing to the root having min Key in the list.
  // 初始时造个空的
  list<Person *> Rootlist;  // creating a Rootlist to store the root
  vector<Person *> Degreebucket;
};

#endif
