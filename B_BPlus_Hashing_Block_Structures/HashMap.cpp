//
//  HashMap.cpp
//  B_BPlus_Hashing_Block_Structures
//
//  Created by Jack's Macbook Pro on 2021/5/12.
//

#include "HashMap.hpp"

void HashMapForProfession::insert(Person *person)
{
    hmap.insert(pair<string, Person*>(person->getProfession(), person));
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

HashMapForProfession::HashMapForProfession() { }
HashMapForProfession::~HashMapForProfession() { }
