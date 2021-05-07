#include "Person.hpp"

// Use ID as primary key.
class block
{
private:
    int mainblock_occupied = 0;
    int overflow_occupied = 0;
    int tombstones_number = 0;
    int fill_threshold = 7;

    // mainblock_size = 10;
    int mainblock_size = 10;
    Person mainblock[10];
    
    // overflow_size = 3;
    int overflow_size = 3;
    Person overflow[3]; 
public:
    int sort(void);
    Person* find(string ID);
    int insert(Person* tuple);
    block* split(void);
    Person* remove(string ID);
    block* merge(void);
    int display(void);
};