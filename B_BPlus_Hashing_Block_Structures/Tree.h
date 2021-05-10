#ifndef TREE_h
#define TREE_h

#include <stdio.h>
#include <vector>
#include <cstring>

#include "block.h"

using namespace std;

#define M 2

/// @brief define the universal arrays for storing the node infomation
typedef struct CommonTreeNodes
{
    vector<Person*> labelArrayForBTree; // labels for B Tree
    vector<string> labelArrayForBPlusTree; // labels for B+ Tree
    vector<CommonTreeNodes*> ptrArray; // for non-leaf nodes
    vector<block*> BlockPtrarray; // for leaf nodes
    
    // number of children
    int num;
    // leaf node?
    bool is_leaf;
} CommonTreeNode;

/// @brief common structure for B Tree and B+ Tree
class Tree
{
protected:
	CommonTreeNode *roots;
	FILE *pfile;
    int btree_node_num;
    
	virtual CommonTreeNode *btree_create() = 0;
	virtual CommonTreeNode *btree_node_new() = 0;
	virtual int btree_split_child(CommonTreeNode *parent, int pos, CommonTreeNode *child) = 0;
	virtual void btree_merge_child(CommonTreeNode *root, int pos, CommonTreeNode *y, CommonTreeNode *z) = 0;
	virtual void btree_shift_to_left_child(CommonTreeNode *root, int pos, CommonTreeNode *y, CommonTreeNode *z) = 0;
	virtual void btree_shift_to_right_child(CommonTreeNode *root, int pos, CommonTreeNode *y, CommonTreeNode *z) = 0;
	virtual void btree_level_display(CommonTreeNode *root) = 0;
    
public:
	Tree(void) { btree_node_num = 0; };
	virtual ~Tree(void)
	{
		btree_node_num = 0;
		delete roots;
	};

	void level_display()
	{
		btree_level_display(roots);
	};

	void NodeNum_print()
	{
		printf("%d\n", btree_node_num);
	};
};

#endif /* TREE_h */
