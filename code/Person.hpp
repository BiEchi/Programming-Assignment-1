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

class Person
{
public:
  friend class FibonacciPQ;
  Person()
  {
    name = string();
    contactDetails = string();
    location = 0;
    profession = 0;
    ageGroup = 0;
    riskStatus = 0;
  }

  string getName(void) { return name; }
  string getID(void) { return ID; }
  string getContactDetails(void) { return contactDetails; }
  tm getBirthdate(void) { return birthDate; }
  tm getTimestamp(void) { return timeStamp; }
  int getProfession(void) { return profession; }
  int getRiskStatus(void) { return riskStatus; }

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
  bool assignLocation(int thePlace) {appointmentLocation = thePlace; return true;}
  int getAssignedLocation(void) {return appointmentLocation;}
  //liyang
  bool withdraw(vector<Person> *blacklist_ptr);
  //baihao
  bool init();
  // yi_hong
  bool isLargerThan(Person person);

private:
  string ID;
  string name;
  string contactDetails;
  tm birthDate;
  tm timeStamp;
  int location;
  int ageGroup;
  int profession, riskStatus;
  //Jiahao
  tm appointmentTime;
  int appointmentLocation;
  // added by Liyang in 3.19
  bool Store = true;
  int Degree = 0;
  bool CutMark = false;
  list<Person *> Son = list<Person *>();
  Person *Parent = nullptr;
  // added by Li_yang in 3.25
  int Key = 0;
};
#endif
