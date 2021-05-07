#ifndef BLOCK_H
#define BLOCK_H
#include <cstring>
#include <iostream>
using namespace std;

class Person
{
public:
    Person() {}
    // temp function !!!
    Person(const Person &src) {ID = src.getID();}
    int setID(int data) {ID = data; return 0;}
    int getID(void) const {return ID;}

private:
    int ID;
};

// ---------------------------------
/**
 * @brief The storage unit of block.
 * 
 */
class record
{
friend class block;
private:
    int tombstone;
    Person* datum_ptr;
private:
    /**
     * @brief Construct a new record object.
     * 
     */
    record(): 
        tombstone{1},
        datum_ptr{NULL}
    {};
    int mark_tombstone(void) {tombstone = 1; return 0;}
    int unmark_tombstone(void) {tombstone = 0; return 0;}
public:
    int get_tombstone(void) const {return tombstone;}
    int get_key(void) const {return datum_ptr->getID();}
};

/**
 * @brief Use ID as primary key. Assumption: all tuple has unique ID. 
 * 
 */
class block
{
private:
    int mainblock_occupied = 0;
    int overflow_occupied = 0;
    // tombstones_number indicate the number of tombstones in mainblock
    int tombstones_number = 0;
    // fill factor between 1/2 and 2/3. Choose 6/10 after testing.
    // fill_threshold + overflow_size <= mainblock_size
    int const fill_threshold = 7; 
    // Choose 1/10 after testing. 
    int const merge_threshold = 2;
    // mainblock_size = 10;
    int const mainblock_size = 10;
    record mainblock[10];
    
    // overflow_size = 3. Choose 1/10 after testing.
    int const overflow_size = 3;
    record overflow[3]; 

    block* prev = NULL;
    block* next = NULL;
private:
    int clear();
    int sort(void);
    block* split(void);
    block* merge(void);
public:
    Person* find(int ID);
    block* insert(Person* tuple);
    block* remove(int ID);
    int maximum(void);
    int display(void);
    block* get_prev(void) {return prev;}
    block* get_next(void) {return next;}
};
// ---------------------------------

#endif