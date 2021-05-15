#ifndef database_h
#define database_h
#include <math.h>
#include <stdio.h>

#include <ctime>
#include <iostream>
#include <list>
#include <vector>

using namespace std;
enum processStage { nonebuffer, buffer, centralQueue, appointment, Finish };
class Person {
 public:
  friend class FibonacciPQ;
  Person() {
    name = string();
    contactDetails = string();
    profession = 0;
    ageGroup = 0;
    riskStatus = 0;
    reassigned = 0;
    currentStage = nonebuffer;
  }

  string getName(void) { return name; }
  string getID(void) { return ID; }
  string getContactDetails(void) { return contactDetails; }
  tm getBirthdate(void) { return birthDate; }
  tm getTimestamp(void) { return timeStamp; }
  int getProfession(void) { return profession; }
  int getRiskStatus(void) { return riskStatus; }
  int getAgeGroup(void) { return ageGroup; }
  processStage getcurrentStage(void) { return currentStage; }

  void setID(string data);
  void setName(string data);
  void setContactDetails(string data);
  void setBirthYear(string data);
  void setBirthMonth(string data);
  void setBirthDay(string data);
  void setTimestamp(string data);
  void setProfession(string data);
  void setRiskStatus(string data);
  void setCurrentStage(processStage data);
  void setTreatmentType(string treatmentType);

  void display();

  // Jiahao
  bool assignTime(tm *atime) {
    appointmentTime = *atime;
    return true;
  }
  bool assignLocation(int thePlace) {
    appointmentLocation = thePlace;
    return true;
  }
  // int getLocation(void) {return location;}
  int markReassigned(void) {
    reassigned = 1;
    return 1;
  }
  int getReassigned(void) { return reassigned; }
  int getAssignedLocation(void) { return appointmentLocation; }
  tm getAssignedTime(void) { return appointmentTime; }
  int getTreatmentType(void) { return treatmentType; }
  // baihao
  bool init();
  // yi_hong
  bool isLargerThan(Person person);

 private:
  string ID;
  string name;
  string contactDetails;
  tm birthDate;
  tm timeStamp;
  // int location;
  int ageGroup;
  int profession, riskStatus;
  // Jiahao
  int treatmentType;
  tm appointmentTime;
  int appointmentLocation;
  int reassigned;  // Indicate that whether a person has been assigned to
                   // another hospital different from his/her contact detail.
  // added by Liyang in 3.19
  bool Store = true;
  int Degree = 0;
  bool CutMark = false;
  list<Person *> Son = list<Person *>();
  Person *Parent = nullptr;
  // added by Liyang
  processStage currentStage;
};
#endif
