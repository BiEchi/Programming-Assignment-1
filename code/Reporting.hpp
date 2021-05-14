//
//  MULTITHREAD.hpp
//  code
//
//  Created by Jack's Macbook Pro on 2021/4/4.
//

#ifndef REPORTING_hpp
#define REPORTING_hpp

#include <stdio.h>
#include <ctime>
#include <unistd.h>

#include "blackList.hpp"
#include "TimePredef.hpp"

ofstream report;

void quick_sort_name(vector<Person> people, int l, int r) {
  if (l < r) {
    // Swap(s[l], s[(l + r) / 2]); //将中间的这个数和第一个数交换 参见注1
    int i = l, j = r;
    Person x = people[l];
    while (i < j) {
      while (i < j &&
             people[j].getName() >= x.getName())  // 从右向左找第一个小于x的数
        j--;
      if (i < j) people[i++] = people[j];

      while (i < j && people[i].getName() <
                          x.getName())  // 从左向右找第一个大于等于x的数
        i++;
      if (i < j) people[j--] = people[i];
    }
    people[i] = x;
    quick_sort_name(people, l, i - 1);  // 递归调用
    quick_sort_name(people, i + 1, r);
  }
}

void quick_sort_profession(vector<Person> people, int l, int r) {
  if (l < r) {
    // Swap(s[l], s[(l + r) / 2]); //将中间的这个数和第一个数交换 参见注1
    int i = l, j = r;
    Person x = people[l];
    while (i < j) {
      while (i < j && people[j].getProfession() >=
                          x.getProfession())  // 从右向左找第一个小于x的数
        j--;
      if (i < j) people[i++] = people[j];

      while (i < j && people[i].getProfession() <
                          x.getProfession())  // 从左向右找第一个大于等于x的数
        i++;
      if (i < j) people[j--] = people[i];
    }
    people[i] = x;
    quick_sort_profession(people, l, i - 1);  // 递归调用
    quick_sort_profession(people, i + 1, r);
  }
}

void quick_sort_age(vector<Person> people, int l, int r) {
  if (l < r) {
    // Swap(s[l], s[(l + r) / 2]); //将中间的这个数和第一个数交换 参见注1
    int i = l, j = r;
    Person x = people[l];
    while (i < j) {
      while (i < j && people[j].getAgeGroup() >=
                          x.getAgeGroup())  // 从右向左找第一个小于x的数
        j--;
      if (i < j) people[i++] = people[j];

      while (i < j && people[i].getAgeGroup() <
                          x.getAgeGroup())  // 从左向右找第一个大于等于x的数
        i++;
      if (i < j) people[j--] = people[i];
    }
    people[i] = x;
    quick_sort_age(people, l, i - 1);  // 递归调用
    quick_sort_age(people, i + 1, r);
  }
}

void Reporting_weekly(unsigned int personType, unsigned int sortType,
                      vector<Person> treatedPeople, vector<Person> centralQueue,
                      vector<Person> assignmentQueue) {
  // output to file
  report.open("report.txt");
  if (personType == 0) {
    if (sortType == 0) {
      quick_sort_name(treatedPeople, 0, int(treatedPeople.size() - 1));
    } else if (sortType == 1) {
      quick_sort_profession(treatedPeople, 0, int(treatedPeople.size() - 1));
    } else {
      quick_sort_age(treatedPeople, 0, int(treatedPeople.size() - 1));
    }
    for (auto iter = treatedPeople.begin(); iter != treatedPeople.end();
         iter++) {
      tm TimeRrgister = (*iter).getTimestamp();
      tm TimeAssigned = (*iter).getAssignedTime();
      report << (*iter).getName() << (*iter).getProfession() << " "
           << (*iter).getAgeGroup() << (*iter).getRiskStatus() << " "
           << difftime(mktime(&TimeRrgister), mktime(&TimeAssigned)) << " "
           << endl;
    }
  }
  if (personType == 1) {
    if (sortType == 0) {
      quick_sort_name(centralQueue, 0, int(centralQueue.size() - 1));
    } else if (sortType == 1) {
      quick_sort_profession(centralQueue, 0, int(centralQueue.size() - 1));
    } else {
      quick_sort_age(centralQueue, 0, int(centralQueue.size() - 1));
    }
    for (auto iter = centralQueue.begin(); iter != centralQueue.end(); iter++) {
      tm TimeRrgister = (*iter).getTimestamp();
      time_t now = time(0);
      report << (*iter).getName() << (*iter).getProfession() << " "
           << (*iter).getAgeGroup() << (*iter).getRiskStatus() << " "
           << difftime(mktime(&TimeRrgister), now) << " " << endl;
    }
  }
  if (personType == 2) {
    if (sortType == 0) {
      quick_sort_name(assignmentQueue, 0, int(assignmentQueue.size() - 1));
    } else if (sortType == 1) {
      quick_sort_profession(assignmentQueue, 0, int(assignmentQueue.size() - 1));
    } else {
      quick_sort_age(assignmentQueue, 0, int(assignmentQueue.size() - 1));
    }
    for (auto iter = assignmentQueue.begin(); iter != assignmentQueue.end();
         iter++) {
      tm TimeRrgister = (*iter).getTimestamp();
      time_t now = time(0);
      report << (*iter).getName() << (*iter).getProfession() << " "
           << (*iter).getAgeGroup() << (*iter).getRiskStatus() << " "
           << difftime(mktime(&TimeRrgister), now) << " " << endl;
    }
  }
  report.close();
}

void Reporting_monthly(vector<Person> treatedPeople,
                       FibonacciPQ &centralQueue,
                       vector<Person> assignmentQueue, blackList blackList) {
  // output to file
  report.open("report.txt");
  report << "There are "
       << treatedPeople.size() + centralQueue.returnLength() + assignmentQueue.size()
       << " people have registered" << endl;
  report << "There are " << centralQueue.returnLength() + assignmentQueue.size()
       << " people are waiting" << endl;
  report << "There are " << treatedPeople.size() << " treatment have been made"
       << endl;
  // for test
  /* cout << "Size of central queue: " << centralQueue.size() << endl;
  cout << "Size of treated people: " << treatedPeople.size() << endl;
  cout << "Size of assignment queue: " << assignmentQueue.size() << endl; */
  // report << "The average waiting time is "
  //      << "?" << endl;
  report << "There are " << blackList.size()
       << " people who withdraw their registration" << endl;
  report.close();
}

#endif /* REPORTING_hpp */
