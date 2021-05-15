//
//  HashMap.cpp
//  B_BPlus_Hashing_Block_Structures
//
//  Created by Jack's Macbook Pro on 2021/5/12.
//

#include "HashMap.hpp"

#include <unistd.h>

#include <vector>

using namespace std;

void HashMap::insert(Person *person) {
  hmap.insert(
      pair<string, string>(to_string(person->getProfession()), person->getID()));
}

void HashMap::del(Person *person) {
  for (auto ite = hmap.begin(); ite != hmap.end(); ite++) {
    if (ite->second == person->getID()) {
      hmap.erase(ite);
    }
  }
}

void HashMap::display() {
  cout << "Displaying all elements in the hashing multimap." << endl;
  for (auto ite = hmap.begin(); ite != hmap.end(); ite++) {
    cout << "key: " << ite->first << ", value: " << ite->second << endl;
  }
}

void HashMap::findAll(string address, BPlusTree &primaryIndex) {
  cout << "there are " << hmap.count(address) << " people with address "
       << address << "." << endl;
  for (auto ite = hmap.begin(); ite != hmap.end(); ite++) {
    if (ite->first == address) {
      primaryIndex.find(ite->second)->display();
      usleep(50000);
      cout << endl;
    }
  }
}

vector<Person *> HashMap::query(int address, BPlusTree &primaryIndex) {
  vector<Person *> people;
  string normalizedAddress = to_string(address);
  for (auto iter = hmap.begin(); iter != hmap.end(); iter++) {
    if (iter->first == to_string(address)) {
      people.push_back(primaryIndex.find(iter->second));
    }
  }

  return people;
}

HashMap::HashMap() {}
HashMap::~HashMap() {}
