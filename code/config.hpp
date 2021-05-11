#ifndef config_hpp
#define config_hpp

#include <unordered_map>
using namespace std;
int nodeNum = 1;
int node1[] = {0, 1};
int node2[] = {1, 2};
int node3[] = {1, 3};
int node4[] = {2, 5};
int node5[] = {3, 7};
int node6[] = {0, 9};
int node7[] = {10, 0};
int node8[] = {1, 12};

unordered_map<int, int*> forwardtable{{1, node1}, {2, node2}, {3, node3},
                                      {4, node4}, {5, node5}, {6, node6},
                                      {7, node7}, {8, node8}};
#endif

int threshold = 1;