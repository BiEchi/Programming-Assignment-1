#include <algorithm>
#include "block.h"

/**
 * @brief compare function for sort function.
 * Person with marked tombstone is always greater than Person with unmarked tombstone. 
 * 
 * @param record1
 * @param record2 
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
        if (overflow[i].get_tombstone()) {continue;} // Ignore Person with marked tombstone.
        for (int j = first_empty; j < mainblock_size; j++) 
        {
            // Find the first empty space in main block.
            if (mainblock[j].get_tombstone()) {first_empty = j; break;}
        }
        mainblock[first_empty].datum = overflow[i].datum; // copy tuple !!!
        mainblock[first_empty].unmark_tombstone();
        (overflow + i)->mark_tombstone(); // Remove tuple in the overflow block. Mark tombstone after copy. 
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
 * @param ID 
 * @return A pointer to the Person with the input ID.
 * If there is no such person, return NULL. 
 */
Person* block::find(string ID) {
    int low = 0, high = tombstones_number + mainblock_occupied - 1;
    int mid;
    while(high >= low)
    {
        mid = high - (high - low)/2;
        if (mainblock[mid].get_key() == ID) {
            if (mainblock[mid].get_tombstone()) {break;}
            return &mainblock[mid].datum;
        }
        if (mainblock[mid].get_key() < ID)
        {
            low = mid + 1;
            continue;
        }
        if (mainblock[mid].get_key() > ID)
        {
            high = mid - 1;
            continue;
        }
    }
    int i, indicator;
    for (i = 0, indicator = 0; i < overflow_size && indicator < overflow_occupied; i++)
    {
        if (overflow[i].get_tombstone()) {continue;} // Ignore Person with marked tombstone.
        if (overflow[i].get_key() == ID) {return &overflow[i].datum;}
        indicator++;
    }
    return NULL;
}

/**
 * @brief Inserts a new tuple into the overflow block at the first free space. If the overflow block is full, trigger the sorting. 
 * If after the sorting there are too many tuples in the main block, split the block.
 * 
 * @param tuple 
 * @return The pointer to the new block if split is called, NULL otherwise. 
 */
block* block::insert(Person* tuple)
{
    // Assume that there is always space left in overflow block.
    for (int i = 0; i < overflow_size; i++)
    {
        if (overflow[i].get_tombstone())
        {
            overflow[i].datum = *tuple;
            overflow[i].unmark_tombstone();
            break;
        }
    }
    overflow_occupied++;
    if (overflow_size == overflow_occupied)
    {
        sort();
    }
    // When split is called, all the tuples are in mainblock, and there is no tombstone. 
    if (mainblock_occupied > fill_threshold)
    {
        return split();
    }
    return NULL;
}

/**
 * @brief Creates a new block and splits the tuples equally. 
 * split will be called by insert only.
 * 
 * @return The pointer to the newly created block. 
 */
block* block::split(void)
{
    int mid = mainblock_occupied/2;
    block* new_block = new block;
    // Connect new_block
    this->next = new_block;
    new_block->prev = this;

    for (int i = mid; i < mainblock_occupied; i++)
    {
        new_block->mainblock[(new_block->mainblock_occupied)++].datum = this->mainblock[i].datum;
        new_block->mainblock[new_block->mainblock_occupied - 1].unmark_tombstone();
        this->mainblock[i].mark_tombstone();
    }
    this->mainblock_occupied = mid;
    return new_block;
}

/**
 * @brief Marks a tuple in the main block or the overflow block by a tombstone.
 * If after remove there are too few tuples in the main block, merge the block with the next block if the next block exists.
 * 
 * @param ID 
 * @return The pointer to this block if merge happens, NULL otherwise. 
 */
block* block::remove(string ID)
{
    record* toRemove;
    int low = 0, high = tombstones_number + mainblock_occupied - 1, mid;
    while(high >= low)
    {
        mid = high - (high - low)/2;
        if (mainblock[mid].get_key() == ID)
        {
            if (mainblock[mid].get_tombstone()) {break;}
            toRemove = mainblock + mid;
            toRemove->mark_tombstone();
            mainblock_occupied--;
            tombstones_number++;
            if (this->mainblock_occupied < merge_threshold) {return merge();}
        }
        if (mainblock[mid].get_key() < ID)
        {
            low = mid + 1;
            continue;
        }
        if (mainblock[mid].get_key() > ID)
        {
            high = mid - 1;
            continue;
        }
    }
    int i, indicator;
    for (i = 0, indicator = 0; i < overflow_size && indicator < overflow_occupied; i++)
    {
        if (overflow[i].get_tombstone()) {continue;} // Ignore Person with marked tombstone.
        toRemove = overflow + i;
        if (toRemove->get_key() == ID) 
        {
            toRemove->mark_tombstone();
            overflow_occupied--;
            return NULL;
        }
        indicator++;
    }
    return NULL;
}

/**
 * @brief Merges a block with one neighbouring block and either splits the result more equally or removes one block.
 * This function will create a new separation key. Assume that merge will be called only when the number of this block is less than the merge_threshold.
 * Important: the neighbouring block might be deleted. All the keys in both blocks are pairwise different. 
 * 
 * @param neighbour The pointer to the neighbouring block.  
 * @return The new seperation key such that all the tuples' key in this block are strickly less than the seperation key.
 * If the neighbouring block is deleted, return the maximum key after merge operation.
 */
block* block::merge(void)
{
    block* neighbour = this->next;
    if (NULL == next) {return NULL;}
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
        arr4tuples[index4arr++].datum = this->mainblock[i].datum;
        indicator++;
    }
    for (i = 0, indicator = 0; i < neighbour->mainblock_size && indicator < neighbour->mainblock_occupied; i++)
    {
        if (neighbour->mainblock[i].get_tombstone()) {continue;}
        arr4tuples[index4arr++].datum = neighbour->mainblock[i].datum;
        indicator++;
    }
    for (i = 0, indicator = 0; i < this->overflow_size && indicator < this->overflow_occupied; i++)
    {
        if (this->overflow[i].get_tombstone()) {continue;}
        arr4tuples[index4arr++].datum = this->overflow[i].datum;
        indicator++;
    }
    for (i = 0, indicator = 0; i < neighbour->overflow_size && indicator < neighbour->overflow_occupied; i++)
    {
        if (neighbour->overflow[i].get_tombstone()) {continue;}
        arr4tuples[index4arr++].datum = neighbour->overflow[i].datum;
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
            this->mainblock[this->mainblock_occupied++].datum = arr4tuples[i].datum;
            this->mainblock[this->mainblock_occupied - 1].unmark_tombstone();
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
            this->mainblock[this->mainblock_occupied++].datum = arr4tuples[i].datum;
            this->mainblock[this->mainblock_occupied - 1].unmark_tombstone();
        }
        for (i = mid4seperate; i < total_num_tuples; i++)
        {
            neighbour->mainblock[neighbour->mainblock_occupied++].datum = arr4tuples[i].datum;
            neighbour->mainblock[neighbour->mainblock_occupied - 1].unmark_tombstone();
        }
        return this;
    }
}

/**
 * @brief Find the maximum primary key (ID) in the block. 
 * 
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

// Operation for B-tree ----------
// -------------------------------

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

// Used for testing. 
int main() {
    int num = 10;
    block data;
    Person people[num];
    block* sec_block;
    for (int i = 0; i < num; i++)
    {
        people[i].setID(to_string(i));
    }

    // Test for insert.
    cout << "Test for insert. " << endl;
    for (int i = 0; i < 8; i++)
    {
        data.insert(&people[i]);
    }
    data.display();

    // Test for remove.
    cout << "Test for remove. " << endl;
    cout << data.remove(to_string(2)) << endl;
    cout << data.remove(to_string(4)) << endl;
    cout << data.remove(to_string(6)) << endl;
    data.display();
    data.insert(&people[4]);
    data.display();
    data.remove(to_string(4));
    data.display();
    data.insert(&people[2]);
    data.display();
    data.insert(&people[4]);
    data.display();

    // Test for find
    cout << "Test for find. " << endl;
    Person* temp;
    data.display();
    for (int i = 0; i < num; i++)
    {
        if((temp = data.find(to_string(i))))
        {
            cout << "Find the person with ID: " << temp->getID() << endl;
        }
        else 
        {
            cout << "Did not find the person with ID " << i << ". \n" << endl;
        }
    }

    // Test for split.
    cout << "Test for split. " << endl;
    data.insert(&people[8]);
    data.insert(&people[9]);
    sec_block = data.insert(&people[6]);
    data.display();
    if (sec_block) {sec_block->display();}

    // Test for merge.
    cout << "Test for merge. " << endl;
    cout << data.merge() << endl;
    data.display();
    sec_block->display();

    // Test for maximum.
    cout << "Test for maximum. " << endl;
    cout << data.maximum() << endl;
    data.remove(to_string(4));
    data.display();
    cout << data.maximum() << endl;
    data.insert(&people[6]);
    data.display();
    cout << data.maximum() << endl;
    data.insert(&people[7]);
    data.display();
    cout << data.maximum() << endl;
    data.remove(to_string(6));
    data.display();
    cout << data.maximum() << endl;

    return 0;
}