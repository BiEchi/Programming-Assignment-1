//
//  HashMap.hpp
//  B_BPlus_Hashing_Block_Structures
//
//  Created by Jack's Macbook Pro on 2021/5/12.
//

#ifndef HashMap_hpp
#define HashMap_hpp

#include <iostream>
#include <unordered_map>
#include <map>
#include <cstring>
#include <vector>
#include "block.hpp"
#include "Person.hpp"
using namespace std;

class HashMap
{
private:
    unordered_multimap<string, Person*> hmap;
    
public:
    void insert(Person* person);
    void del(Person* person);
    void findAll(string profession);
    void display(void);
    vector<Person *> query(int address);
    
    HashMap(void);
    ~HashMap(void);
};

#endif /* HashMap_hpp */
