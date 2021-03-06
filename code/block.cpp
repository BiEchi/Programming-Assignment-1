#include <algorithm>
#include "block.hpp"

/**
 * @brief Clear ALL the data in the block (incl. overflow data) by marking all tuples' tombstones.
 * @return 1 for indication
 */
int block::clear()
{
    mainblock_occupied = 0;
    overflow_occupied = 0;
    tombstones_number = 0;
    
    for (int i = 0; i < mainblock_size; i++)
        mainblock[i].mark_tombstone();
    for (int i = 0; i < overflow_size; i++)
        overflow[i].mark_tombstone();
    return 1;
}

/**
 * @brief Overload operator= (deep copy, viz. deecopy)
 * @param src rvalue of =
 * @return address of record
 */
record& record::operator=(const record& src)
{
    tombstone = src.tombstone;
    datum_ptr = src.datum_ptr;
    key = src.key;
    return *this;
}

/**
 * @brief Compare function for std::sort function.
 * Person with marked tombstone is always greater than Person with unmarked tombstone. 
 *
 * @param record1 record 1
 * @param record2  record 2
 * @returns True if the primary key (ID) of record1 is less than the primary key (ID) of record2, false otherwise. 
 */
bool cmp4sort(const record &record1, const record &record2) 
{
    if (1 == record1.get_tombstone() && 1 == record2.get_tombstone()) {return false;}
    if (0 == record1.get_tombstone() && 1 == record2.get_tombstone()) {return true;}
    if (1 == record1.get_tombstone() && 0 == record2.get_tombstone()) {return false;}
    if (record1.get_key() < record2.get_key()) {return true;}
    else {return false;}
}

/**
 * @brief Sorts all tuples in the main and the overflow block and stores the result only in the main block, leving the overflow block empty.
 * This function use sort function in algorithm library. 
 * After sort, tombstones_number = 0
 * 
 * @return 1 for indication. 
 */
int block::sort(void) 
{
    int first_empty = 0;
    int i, indicator;
    for (i = 0, indicator = 0; i < overflow_size && indicator < overflow_occupied; i++) 
    {
        if (overflow[i].get_tombstone()) // Ignore Person with marked tombstone.
        {continue;}
        for (int j = first_empty; j < mainblock_size; j++) 
        {
            // Find the first empty space in main block.
            if (mainblock[j].get_tombstone())
            {first_empty = j; break;}
        }
        mainblock[first_empty] = overflow[i]; // copy the record !!!
        (overflow + i)->mark_tombstone(); // Remove tuple in the overflow block by marking the tombstone after copy. 
        indicator++;
    }
    std::sort(mainblock, mainblock + (mainblock_occupied + std::max(overflow_occupied, tombstones_number)), cmp4sort);
    mainblock_occupied = mainblock_occupied + overflow_occupied;
    overflow_occupied = 0;
    tombstones_number = 0;
    return 1;
}

/**
 * @brief Combines binary search in a main block with linear search in the overflow block.
 * 
 * @param ID ID
 * @return A pointer to the Person with the input ID.
 * If there is no such person, return NULL. 
 */
Person* block::find(string ID) {
    int low = 0, high = tombstones_number + mainblock_occupied - 1;
    int mid, shift;
    while (high >= low && mainblock_occupied != 0)
    {
        shift = mid = high - (high - low)/2;
        while (mainblock[shift].get_tombstone() && shift <= high)
        {
            shift++;
            if (shift > high) {high = mid - 1;}
        }
        if (shift > high) {continue;}
        if (mainblock[shift].get_key() == ID) {
            return mainblock[shift].datum_ptr;
        }
        if (mainblock[shift].get_key() < ID)
        {
            low = shift + 1;
            continue;
        }
        if (mainblock[shift].get_key() > ID)
        {
            if (shift == high) {high = mid - 1; continue;}
            high = shift - 1;
            continue;
        }
    }
    int i, indicator;
    for (i = 0, indicator = 0; i < overflow_size && indicator < overflow_occupied; i++)
    {
        if (overflow[i].get_tombstone()) {continue;} // Ignore Person with marked tombstone.
        if (overflow[i].get_key() == ID) {return overflow[i].datum_ptr;}
        indicator++;
    }
    return NULL;
}

/**
 * @brief Inserts a new tuple into the overflow block at the first free space. If the overflow block is full, trigger the sorting. 
 * If after the sorting there are too many tuples in the main block, split the block.
 * @param tuple tuple
 * @return The pointer to the new block if split is called, NULL otherwise. 
 */
block* block::insert(Person* tuple)
{
    /// @note Assume that there is always space left in overflow block.
    // we insert into tombstones first
    for (int i = 0; i < overflow_size; i++)
        if (overflow[i].get_tombstone())
        {
            overflow[i].datum_ptr = new Person;
            *(overflow[i].datum_ptr) = *tuple;
            overflow[i].key = record::compute_key(tuple);
            overflow[i].unmark_tombstone();
            break;
        }
    overflow_occupied++;
    if (overflow_size == overflow_occupied)
        sort();
    // After split is called, all the tuples are in mainblock, and there is no tombstone.
    if (mainblock_occupied > fill_threshold)
        return split();
    else return NULL;
}

/**
 * @brief Creates a new block and splits the tuples equally. 
 * @note split will be called by insert only.
 * @return The pointer to the NEW block.
 */
block* block::split(void)
{
    int mid = mainblock_occupied/2;
    block* new_block = new block;
    // Connect new_block
    if (NULL == this->next)
    {
        this->next = new_block;
        new_block->prev = this; // double-linked list
    } else {
        block* temp = this->next;
        this->next = new_block;
        new_block->next = temp;
        temp->prev = new_block;
        new_block->prev = this;
    }
    
    // move content to the new block by half
    for (int i = mid; i < mainblock_occupied; i++)
    {
        new_block->mainblock[(new_block->mainblock_occupied)++] = this->mainblock[i];
        this->mainblock[i].mark_tombstone();
    }
    this->mainblock_occupied = mid;
    return new_block;
}

/**
 * @brief Marks a tuple in the main block or the overflow block by a tombstone.
 *  If after remove there are too few tuples in the main block, merge the block with the next block if the next block exists.
 * @param ID ID
 * @return The pointer to this block if merge happens, NULL otherwise. 
 */
block* block::remove(string ID)
{
    record* toRemove;
    int lowPos = 0,
    highPos = tombstones_number + mainblock_occupied - 1; // all data in block
    int mid, shift;
    while (highPos >= lowPos && mainblock_occupied != 0)
    {
        // assign value to mid first, then assign mid to shift
        shift = mid = highPos - (highPos - lowPos)/2;
        
        // tombstone detected, skip
        while (mainblock[shift].get_tombstone() && shift <= highPos)
        {
            shift++;
            if (shift > highPos) {highPos = mid - 1;}
        }
        if (shift > highPos) {continue;}
        
        // target found, execute delete routine
        if (mainblock[shift].get_key() == ID)
        {
            toRemove = mainblock + shift;
            toRemove->mark_tombstone();
            delete toRemove->datum_ptr;
            mainblock_occupied--;
            tombstones_number++;
            if ((this->mainblock_occupied < merge_threshold) && (nullptr != this->nextPointer()) && (0 < this->nextPointer()->mainblock_occupied))
            {
                return merge();
            }
            else {return NULL;}
        }
        
        // continue to search for the target
        if (mainblock[shift].get_key() < ID)
        {
            lowPos = shift + 1;
            continue;
        }
        if (mainblock[shift].get_key() > ID)
        {
            if (shift == highPos) {highPos = mid - 1; continue;}
            highPos = shift - 1;
            continue;
        }
    }
    
    // ?
    int i, indicator;
    for (i = 0, indicator = 0; i < overflow_size && indicator < overflow_occupied; i++)
    {
        if (overflow[i].get_tombstone()) { continue; }
        toRemove = overflow + i;
        if (toRemove->get_key() == ID) 
        {
            toRemove->mark_tombstone();
            delete toRemove->datum_ptr;
            overflow_occupied--;
            return NULL;
        }
        indicator++;
    }
    return NULL;
}

/**
 * @brief Merges a block with one neighbouring block and either splits the result more equally or removes one block.
 * This function will create a new separation key.
 * @note Assume that merge will be called only when the number of this block is less than the merge_threshold.
 * @WARNING the neighbouring block might be deleted. All the keys in both blocks are pairwise different.
 * @return The new seperation key such that all the tuples' key in this block are strictly less than the seperation key.
 * If the neighbouring block is deleted, return the maximum key after merge operation.
 */
block* block::merge(void)
{
    block* neighbour = this->next;
    if (NULL == this->next) {return NULL;}
    int total_num_tuples = this->mainblock_occupied + this->overflow_occupied + neighbour->mainblock_occupied + neighbour->overflow_occupied;
    int mid4seperate = total_num_tuples/2;
    record arr4tuples[total_num_tuples];
    string seperate_key;
    // Copy all the tuples into arr4tuples. 
    int index4arr = 0;
    int i, indicator;
    for (i = 0, indicator = 0; i < this->mainblock_size && indicator < this->mainblock_occupied; i++)
    {
        if (this->mainblock[i].get_tombstone()) {continue;}
        arr4tuples[index4arr++] = this->mainblock[i];
        indicator++;
    }
    for (i = 0, indicator = 0; i < neighbour->mainblock_size && indicator < neighbour->mainblock_occupied; i++)
    {
        if (neighbour->mainblock[i].get_tombstone()) {continue;}
        arr4tuples[index4arr++] = neighbour->mainblock[i];
        indicator++;
    }
    for (i = 0, indicator = 0; i < this->overflow_size && indicator < this->overflow_occupied; i++)
    {
        if (this->overflow[i].get_tombstone()) {continue;}
        arr4tuples[index4arr++] = this->overflow[i];
        indicator++;
    }
    for (i = 0, indicator = 0; i < neighbour->overflow_size && indicator < neighbour->overflow_occupied; i++)
    {
        if (neighbour->overflow[i].get_tombstone()) {continue;}
        arr4tuples[index4arr++] = neighbour->overflow[i];
        indicator++;
    }
    
    std::sort(arr4tuples, arr4tuples + total_num_tuples, cmp4sort);
    this->clear();
    neighbour->clear();
    // reorganisation
    if (total_num_tuples <= fill_threshold)
    {
        for (i = 0; i < total_num_tuples; i++)
        {
            this->mainblock[this->mainblock_occupied++] = arr4tuples[i];
        }
        // Disconnect block.
        if (neighbour->next) {
            this->next = neighbour->next;
            neighbour->next->prev = this;
        } else {
            this->next = NULL;
        }
        // Delete block. 
        delete neighbour;
        return this;
    } else {
        seperate_key = arr4tuples[mid4seperate].get_key();
        for (i = 0; i < mid4seperate; i++)
        {
            this->mainblock[this->mainblock_occupied++] = arr4tuples[i];
        }
        for (i = mid4seperate; i < total_num_tuples; i++)
        {
            neighbour->mainblock[neighbour->mainblock_occupied++] = arr4tuples[i];
        }
        return this;
    }
}

/**
 * @brief Find the maximum primary key (ID) in the block.
 * @return The maximum ID. 
 */
string block::maximum(void)
{
    string max;
    for (int i = mainblock_occupied + tombstones_number - 1; i > -1 ; i--)
    {
        if (!mainblock[i].get_tombstone()) 
        {
            max = mainblock[i].get_key();
            break;
        }
    }
    int i, indicator;
    for (i = 0, indicator = 0; i < overflow_size && indicator < overflow_occupied; i++)
    {
        if (overflow[i].get_tombstone()) {continue;}
        if (overflow[i].get_key() > max) {max = overflow[i].get_key();}
    }
    return max;
}

/**
 * @brief Display ID of all the tuples in the block.
 * 
 * @return 1 for indication. 
 */
int block::display(void)
{
    record* temp;
    cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
    cout << "Main block has the following tuple: \n";
    for (int i = 0; i < mainblock_occupied + tombstones_number; i++) 
    {
        temp = mainblock + i;
        if (temp->get_tombstone()) {continue;}
        cout << "   ID: " << temp->get_key() << endl;
    }
    cout << "Overflow block has the following tuple: \n";
    int i, indicator;
    for (i = 0, indicator = 0; i < overflow_size && indicator < overflow_occupied; i++)
    {
        temp = overflow + i;
        if (temp->get_tombstone()) {continue;} // Ignore Person with marked tombstone.
        cout << "   ID: " << temp->get_key() << endl;
        indicator++;
    }
    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl << endl;
    return 0;
}
