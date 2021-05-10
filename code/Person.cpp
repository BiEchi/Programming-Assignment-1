#include "Person.hpp"

#include <stdio.h>

#include <cstring>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

void Person::setID(string data) {
    ID = data;  // automatically convert char* to string
    return;
}

void Person::setName(string data) {
    name = data;
    return;
}

void Person::setContactDetails(string data) {
    contactDetails = data;
    return;
}

/// set the year of birth
/// @param data char* YYYY
void Person::setBirthYear(string data) {
    birthDate.tm_year = stoi(data);
    int age = 2021 - birthDate.tm_year;
    
    if (age < 12) ageGroup = 0;
    if (age < 18) ageGroup = 1;
    if (age < 35) ageGroup = 2;
    if (age < 50) ageGroup = 3;
    if (age < 65) ageGroup = 4;
    if (age < 75) ageGroup = 5;
    else ageGroup = 6;
    
  return;
}

/// set the month of birth
/// @param data char* MM
void Person::setBirthMonth(string data) {
  birthDate.tm_mon = stoi(data);
  return;
}

/// set the day of birth
/// @param data char* DD
void Person::setBirthDay(string data) {
  birthDate.tm_mday = stoi(data);
  return;
}

void Person::setProfession(string data) {
  profession = stoi(data);
  return;
}

void Person::setRiskStatus(string data) {
  riskStatus = stoi(data);
  return;
}

void Person::setTimestamp(string data) { return; }

void Person::display() {
  cout << "The person's Name is " << getName() << endl;
  cout << "The person's ID is " << getID() << endl;
  cout << "The person's Contact Detail is " << getContactDetails() << endl;
  cout << "The person's Birth Date is " << getBirthdate().tm_year << ":"
       << getBirthdate().tm_mon << ":" << getBirthdate().tm_mday << endl;
  cout << "The person's Profession is " << getProfession() << endl;
  cout << "The person's Risk Status is " << getRiskStatus() << endl;
}

// 优先级更高
bool Person::isLargerThan(Person person) {
  if (this->riskStatus == 3 && person.riskStatus != 3) {
    return false;
  }

  if (this->profession <= person.profession) {
    return false;
  } else if (this->profession > person.profession) {
    return true;
  }

  if (this->ageGroup <= person.ageGroup) {
    return false;
  } else if (this->ageGroup > person.ageGroup) {
    return true;
  }

  if (this->timeStamp.tm_year <= person.timeStamp.tm_year) {
    return false;
  } else if (this->timeStamp.tm_year > person.timeStamp.tm_year) {
    return true;
  }

  if (this->timeStamp.tm_mon <= person.timeStamp.tm_mon) {
    return false;
  } else if (this->timeStamp.tm_mon > person.timeStamp.tm_mon) {
    return true;
  }

  if (this->timeStamp.tm_mday <= person.timeStamp.tm_mday) {
    return false;
  } else if (this->timeStamp.tm_mday > person.timeStamp.tm_mday) {
    return true;
  }

  if (this->timeStamp.tm_min <= person.timeStamp.tm_min) {
    return false;
  } else if (this->timeStamp.tm_min > person.timeStamp.tm_min) {
    return true;
  }

  if (this->timeStamp.tm_sec <= person.timeStamp.tm_sec) {
    return false;
  } else if (this->timeStamp.tm_sec > person.timeStamp.tm_sec) {
    return true;
  }

  return true;
}

void Person::setCurrentStage(processStage data) {
  currentStage = data;
  return;
}
