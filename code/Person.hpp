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

enum professionSet { I, II, III, IV, V, VI, VII, VIII };
enum riskStatusSet { no, low, middle, high };
enum locationSet {A, B, C, D, E, F, G};

class Person {
public:
  friend class FibonacciPQ;

  string getName(void) {return name;}
  string getContactDetails(void) {return contactDetails;}
  tm getBirthdate(void) {return birthDate;}
  tm getTimestamp(void) {return timeStamp;}
  professionSet getProfession(void) {return profession;}
  riskStatusSet getRiskStatus(void) {return riskStatus;}
  locationSet getLocation(void) {return location;}

  void setName(char* data);
  void setContactDetails(char* data);
  void setBirthdate(char* data);
  void setTimestamp(char* data);
  void setProfession(char* data);
  void setRiskStatus(char* data);
  void setLocation(char* data);

  //Jiahao
  bool assignTime(void);
  //liyang
  bool withdraw(vector<Person> *blacklist_ptr);
  //baihao
  bool init();
 private:
  string name = "";
  string contactDetails = "";
  tm birthDate;
  tm timeStamp;
  professionSet profession;
  riskStatusSet riskStatus;
  locationSet location;
  //Jiahao
  tm appointmentTime;
  // added by Liyang in 3.19
  bool Store = true;
  int Degree = 0;
  bool CutMark = false;
  list<Person*> Son = list<Person*>();
  Person *Parent = nullptr;
};


#endif