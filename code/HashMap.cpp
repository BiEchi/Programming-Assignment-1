//
//  HashMap.cpp
//  B_BPlus_Hashing_Block_Structures
//
//  Created by Jack's Macbook Pro on 2021/5/12.
//

#include <vector>
#include "HashMap.hpp"
using namespace std;

void HashMapForProfession::insert(Person *person)
{
    hmap.insert(pair<string, Person*>(to_string(person->getProfession()), person));
}

void HashMapForProfession::del(Person *person)
{
    for (auto ite = hmap.begin(); ite != hmap.end(); ite++) {
        if (ite->second == person) {
            hmap.erase(ite);
        }
    }
}

void HashMapForProfession::display()
{
    cout << "Displaying all elements in the hashing multimap." << endl;
    for (auto ite = hmap.begin(); ite != hmap.end(); ite++) {
        cout << "key: " << ite->first << ", value: " << ite->second << endl;
    }
}

void HashMapForProfession::findAll(string profession)
{
    cout << "there are " << hmap.count(profession)
      << " people with profession " << profession << "." << endl;
    for (auto ite = hmap.begin(); ite != hmap.end(); ite++) {
        if (ite->first == profession) {
            cout << "Profession: " << profession << ", ID: " << ite->second->getID() << endl;
        }
    }
}

vector<Person *> HashMapForProfession::query(int address)
{
    vector<Person*> people;
    string normalizedAddress = to_string(address);
    for (auto iter = hmap.begin(); iter != hmap.end(); iter++) {
        if (iter->first == to_string(address)) {
            people.push_back(iter->second);
        }
    }
    
    return people;
}

HashMapForProfession::HashMapForProfession() { }
HashMapForProfession::~HashMapForProfession() { }
