//
//  MULTITHREAD.hpp
//  code
//
//  Created by Jack's Macbook Pro on 2021/4/4.
//

#ifndef MULTITHREAD_hpp
#define MULTITHREAD_hpp

#include <stdio.h>

#include <ctime>

#include "blackList.hpp"
// FibonacciPQ for 治疗队列
void forwardToCentralQueue(PeopleLocalQueue &people,
                           FibonacciPQ &centralQueue) {
  cout << endl;
  cout << "-------------CentralQueueStart---------------" << endl;
  cout << "Forwarding temporary record to central queue because half a day is "
          "gone."
       << endl
       << endl;

  // readPeopleIntoCentralQueue();
  // withdraw?
  centralQueue.eatPeople(people);
  // delete &people;

  cout << "now there is " << centralQueue.returnLength()
       << " people in the central queue" << endl;
  cout << "Successfully forwarded your information to the Central Queue."
       << endl;
  cout << endl
       << "-------------CentralQueueFinish--------------" << endl
       << endl;

  return;
}

/// set up the timer
/// @param id the id number of the timer
/// @param msec the number of milli-seconds you want to lapse in one epoch
void settimer(unsigned int id, int msec, PeopleLocalQueue &people,
              FibonacciPQ &centralQueue) {
  if (msec < 0)  // 判断时间段是否满足 >=0
  {
    return;
  }
  clock_t start, finish;
  start = clock();       // 计时函数
  double totaltime = 0;  // 定义时间变量
  while (1) {
    finish = clock();
    totaltime = (double)(finish - start);
    if (totaltime > msec) {
      forwardToCentralQueue(people, centralQueue);
      break;
    }
  }

  return;
}

void MULTITHREAD_forwardToCentralQueueAtNoon(PeopleLocalQueue &people,
                                             FibonacciPQ &centralQueue) {
  settimer(1, 2000000, people, centralQueue);
}

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
  if (personType > 3 || personType < 0) {
    cout << "personType ERROR" << endl;
    return;
  }
  if (sortType > 3 || sortType < 0) {
    cout << "sortType ERROR" << endl;
    return;
  }
  if (personType == 0) {
    if (sortType == 0) {
      quick_sort_name(treatedPeople, 0, treatedPeople.size() - 1);
    } else if (sortType == 1) {
      quick_sort_profession(treatedPeople, 0, treatedPeople.size() - 1);
    } else {
      quick_sort_age(treatedPeople, 0, treatedPeople.size() - 1);
    }
    for (auto iter = treatedPeople.begin(); iter != treatedPeople.end();
         iter++) {
      tm TimeRrgister = (*iter).getTimestamp();
      tm TimeAssigned = (*iter).getAssignedTime();
      cout << (*iter).getName() << (*iter).getProfession() << " "
           << (*iter).getAgeGroup() << (*iter).getRiskStatus() << " "
           << difftime(mktime(&TimeRrgister), mktime(&TimeAssigned)) << " "
           << endl;
    }
  }
  if (personType == 1) {
    if (sortType == 0) {
      quick_sort_name(centralQueue, 0, centralQueue.size() - 1);
    } else if (sortType == 1) {
      quick_sort_profession(centralQueue, 0, centralQueue.size() - 1);
    } else {
      quick_sort_age(centralQueue, 0, centralQueue.size() - 1);
    }
    for (auto iter = centralQueue.begin(); iter != centralQueue.end(); iter++) {
      tm TimeRrgister = (*iter).getTimestamp();
      time_t now = time(0);
      cout << (*iter).getName() << (*iter).getProfession() << " "
           << (*iter).getAgeGroup() << (*iter).getRiskStatus() << " "
           << difftime(mktime(&TimeRrgister), now) << " " << endl;
    }
  }
  if (personType == 2) {
    if (sortType == 0) {
      quick_sort_name(assignmentQueue, 0, assignmentQueue.size() - 1);
    } else if (sortType == 1) {
      quick_sort_profession(assignmentQueue, 0, assignmentQueue.size() - 1);
    } else {
      quick_sort_age(assignmentQueue, 0, assignmentQueue.size() - 1);
    }
    for (auto iter = assignmentQueue.begin(); iter != assignmentQueue.end();
         iter++) {
      tm TimeRrgister = (*iter).getTimestamp();
      time_t now = time(0);
      cout << (*iter).getName() << (*iter).getProfession() << " "
           << (*iter).getAgeGroup() << (*iter).getRiskStatus() << " "
           << difftime(mktime(&TimeRrgister), now) << " " << endl;
    }
  }
}

void Reporting_monthly(vector<Person> treatedPeople,
                       vector<Person> centralQueue,
                       vector<Person> assignmentQueue, blackList blackList) {
  cout << "There are "
       << treatedPeople.size() + centralQueue.size() + assignmentQueue.size()
       << " people have registered" << endl;
  cout << "There are " << centralQueue.size() + assignmentQueue.size()
       << " people are waiting" << endl;
  cout << "There are " << treatedPeople.size() << " treatment have brrn made"
       << endl;
  cout << "The average waiting time is "
       << "?" << endl;
  cout << "There are " << blackList.size()
       << " people who withdraw their registration" << endl;
}

#endif /* MULTITHREAD_hpp */