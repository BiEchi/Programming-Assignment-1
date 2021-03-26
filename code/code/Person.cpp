#include "Person.hpp"

#include <stdio.h>

#include <cstring>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

void Person::setID(char *data)
{
  ID = data; // automatically convert char* to string
  return;
}

void Person::setName(char *data)
{
  name = data;
  return;
}

void Person::setContactDetails(char *data)
{
  contactDetails = data;
  return;
}

/// set the year of birth
/// @param data char* YYYY
void Person::setBirthYear(char *data)
{
  birthDate.tm_year = (int)*data;
  return;
}

/// set the month of birth
/// @param data char* MM
void Person::setBirthMonth(char *data)
{
  birthDate.tm_mon = (int)*data;
  return;
}

/// set the day of birth
/// @param data char* DD
bool Person::withdraw(vector<Person> *blacklist_ptr)
{
  if (nullptr == blacklist_ptr)
    blacklist_ptr = &vector<Person>();
  switch (arrangeStage)
  {
  case buffer:
  {
    break;
  }
  case treatment:
  {
    break;
  }
  case appointment:
  {
    break;
  }
  default:
  {
    cout << "the patient is in wrong stage" << endl;
    return false;
  }
  }
  return true;
}
void Person::setBirthDay(char *data)
{
  birthDate.tm_mday = (int)*data;
  return;
}

void Person::setProfession(char *data)
{
  profession = (int)*data;
  return;
}

void Person::setRiskStatus(char *data)
{
  profession = (int)*data;
  return;
}

void Person::setLocation(char *data)
{
  location = (int)*data;
  return;
}

void Person::setTimestamp(char *data) { return; }

bool Person::isLargerThan(Person person)
{
  if (this->riskStatus = 3 && person.riskStatus != 3)
  {
    return false;
  }

  if (this->profession < person.profession)
  {
    return false;
  }
  else if (this->profession > person.profession)
  {
    return true;
  }

  if (this->ageGroup < person.ageGroup)
  {
    return false;
  }
  else if (this->ageGroup > person.ageGroup)
  {
    return true;
  }

  if (this->timeStamp.tm_year < person.timeStamp.tm_year)
  {
    return false;
  }
  else if (this->timeStamp.tm_year > person.timeStamp.tm_year)
  {
    return true;
  }

  if (this->timeStamp.tm_mon < person.timeStamp.tm_mon)
  {
    return false;
  }
  else if (this->timeStamp.tm_mon > person.timeStamp.tm_mon)
  {
    return true;
  }

  if (this->timeStamp.tm_mday < person.timeStamp.tm_mday)
  {
    return false;
  }
  else if (this->timeStamp.tm_mday > person.timeStamp.tm_mday)
  {
    return true;
  }

  if (this->timeStamp.tm_min < person.timeStamp.tm_min)
  {
    return false;
  }
  else if (this->timeStamp.tm_min > person.timeStamp.tm_min)
  {
    return true;
  }

  if (this->timeStamp.tm_sec < person.timeStamp.tm_sec)
  {
    return false;
  }
  else if (this->timeStamp.tm_sec > person.timeStamp.tm_sec)
  {
    return true;
  }

  return true;
}