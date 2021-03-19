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
  string getName(void) {return name;}
  string getID(void) {return ID;}
  string getContactDetails(void) {return contactDetails;}
  tm getBirthdate(void) {return birthDate;}
  tm getTimestamp(void) {return timeStamp;}
  professionSet getProfession(void) {return profession;}
  riskStatusSet getRiskStatus(void) {return riskStatus;}
  locationSet getLocation(void) {return location;}

  void setID(char* data);
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
  string ID;
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