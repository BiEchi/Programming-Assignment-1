#ifndef STRUCT_H
#define STRUCT_H
#include "block.h"
#include <vector>
#include <string>
using namespace std;
// the degree of btree
#define M 2

typedef struct btree_nodes
{
	// one value, one biggest value in the last below
	string labelArray[2 * M];
	// if it is the none leaf node, use this
	struct btree_nodes *ptrArray[2 * M];
	// if it is the leaf node, use this
	vector<block *> BlockPtrarray;
	int num;
	bool is_leaf;
	// struct btree_nodes *prev; // use one struct just for simple,Õâ2¸ö£¬¹©B+Tree used
	// struct btree_nodes *next; // ¹©B+Tree used

} btree_node;

typedef struct StorageNode
{
	btree_node bnode;
	int index[M]; // Ë÷Òý¼¯ºÏ:index_set
} storage_node;

typedef struct StorageStruct
{
	storage_node *snode;
	int len;
} storage_struct;

#endif