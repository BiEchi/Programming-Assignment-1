#include "Person.hpp"

/**
 * @brief Compare the distance of two people, decide whether the distance is within the threshold. 
 * 
 * @param address the address of the person to be compared with the fixed point person, 
 * where address is int arrary of length two. The first component is x coordinate, the second component is y coordinate. 
 * @param center the address of the fixed point person. 
 * @param threshold 
 * @return true if the distance is less or equal than the threshold, false otherwise. 
 */
bool distance(int *address, int *center, int threshold)
{
    double compare_x, compare_y, center_x, center_y;
    double distanceS;
    compare_x = address[0]; compare_y = address[1];
    center_x = center[0]; center_y = center[1];
    distanceS = (compare_x - center_x)*(compare_x - center_x) + (compare_y - center_y)*(compare_y - center_y);
    return distanceS <= threshold*threshold ? true : false;
}