#ifndef BLOCK_H
#define BLOCK_H
#include <iostream>
#include "Person.hpp"
using namespace std;


// ---------------------------------
/**
 * @brief The storage unit of block.
 * 
 */
class record
{
friend class block;
// compare for sorting
friend bool cmp4sort(const record &record1, const record &record2);
private:
    int tombstone; // either 1 or 0, refering to true or false
    Person* datum_ptr;
    string key;
private:
    record(): tombstone{1}, datum_ptr{NULL} {};
    int mark_tombstone(void) {tombstone = 1; return 0;}
    int unmark_tombstone(void) {tombstone = 0; return 0;}
    static string compute_key(Person *tuple) {return tuple->getID();}
    int get_tombstone(void) const {return tombstone;}
    string get_key(void) const {return key;}
public:
    record& operator=(const record& src);
};

/**
 * @brief Use ID as primary key.
 * @note We assume that all tuples have unique ID.
 */
class block
{
private:
    int mainblock_occupied = 0;
    int overflow_occupied = 0;
    // #tombstones in mainblock
    // Note that no tombstones are allowed in overflow block
    int tombstones_number = 0;
    // the maximum size of mainblock is 10
    static int const mainblock_size = 100; //  change this!
    // fill factor between 1/2 and 2/3. Choose 6/10 after testing.
    // fill_threshold + overflow_size <= mainblock_size
    int const fill_threshold = mainblock_size*6/10 + 1;
    // Choose 1/10 after testing.
    int const merge_threshold = mainblock_size*1/10 + 1;
    record mainblock[mainblock_size];
    
    // overflow_size = 3. Choose 1/10 of all after testing.
    static int const overflow_size = mainblock_size*1/10 + 1;
    record overflow[overflow_size];
    
    block* prev = NULL;
    block* next = NULL;
private:
    int clear();
    int sort(void);
    block* split(void);
    block* merge(void);
public:
    Person* find(string ID);
    block* insert(Person* tuple);
    block* remove(string ID);
    string maximum(void);
    int display(void);
    block* prevPointer(void) {return prev;}
    block* nextPointer(void) {return next;}
};

#endif
