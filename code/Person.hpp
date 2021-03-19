#ifndef person_hpp
#define person_hpp

#include <cstring>
#include <ctime>
#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;

enum professionSet { I, II, III, IV, V, VI, VII, VIII };
enum riskStatusSet { no, low, middle, high };
enum locationSet {A, B, C, D, E, F, G};

class Person {
public:
  string getname(void) {return name;}
  string getcontactDetails(void) {return contactDetails;}
  tm getbirthDate(void) {return birthDate;}
  tm gettimeStamp(void) {return timeStamp;}
  professionSet getprofession(void) {return profession;}
  riskStatusSet getriskStatus(void) {return riskStatus;}
  locationSet getlocation(void) {return location;}

  //Jiahao
  bool assignTime(void);
  //liyang
  bool withdraw(vector<Person> *blacklist_ptr);
  //baihao
  bool init();
private:
  string name;
  string contactDetails;
  tm birthDate;
  tm timeStamp;
  professionSet profession;
  riskStatusSet riskStatus;
  locationSet location;
  //Jiahao
  tm appointmentTime;
};

#endif