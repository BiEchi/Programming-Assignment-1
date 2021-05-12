#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include "block.h"
#include "Tree.h"
#include <string>

class BPlusTree : public Tree
{
private:
	block *begin = nullptr;
	string dynamicIDForMaintain = "0";
	 // personIndex is used to record the deleted person 
    Person *personIndex = nullptr;
	// vector
    
protected:
	virtual CommonTreeNode *btree_create();
	virtual CommonTreeNode *btree_node_new();
	// split and merge interior nodes
	virtual int btree_split_child(CommonTreeNode *parent, int pos, CommonTreeNode *child);
	virtual void btree_merge_child(CommonTreeNode *root, int pos, CommonTreeNode *y, CommonTreeNode *z);
	virtual void btree_shift_to_left_child(CommonTreeNode *root, int pos, CommonTreeNode *y, CommonTreeNode *z);
	virtual void btree_shift_to_right_child(CommonTreeNode *root, int pos, CommonTreeNode *y, CommonTreeNode *z);
	Person *bPlustree_insert_nonfull(CommonTreeNode *node, Person *target);
	Person *bPlustree_delete_nonone(CommonTreeNode *root, string target);
	virtual void btree_level_display(CommonTreeNode *root);
	void btree_linear_print(CommonTreeNode *root);

public:
	BPlusTree(void);
	~BPlusTree(void);
	BPlusTree(block *doubleBlockHead);

	void linear_print();
	CommonTreeNode *returnRoot();
	
	Person *bPlustree_delete(CommonTreeNode *root, const string target);
	Person *bPlustree_insert(CommonTreeNode *root, Person *target);
	Person *find(string ID);
};

#endif /* BPLUSTREE_H */
