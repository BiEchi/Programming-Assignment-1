//
//  HashMap.hpp
//  B_BPlus_Hashing_Block_Structures
//
//  Created by Jack's Macbook Pro on 2021/5/12.
//

#ifndef HashMap_hpp
#define HashMap_hpp

#include <cstring>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include "BPlusTree.hpp"
#include "Person.hpp"
#include "block.hpp"

using namespace std;

class HashMap {
 private:
  unordered_multimap<string, string> hmap;

 public:
  void insert(Person* person);
  void del(Person* person);
  void findAll(string address, BPlusTree &primaryIndex);
  void display(void);
  vector<Person*> query(int address, BPlusTree &primaryIndex);

  HashMap(void);
  ~HashMap(void);
};

#endif /* HashMap_hpp */
