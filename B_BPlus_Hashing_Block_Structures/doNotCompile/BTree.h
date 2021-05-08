#ifndef BTREE_H
#define BTREE_H

#include "Tree.h"

class BTree : public Tree
{
protected:
	virtual CommonTreeNode *btree_create();
	virtual CommonTreeNode *btree_node_new();
	virtual int btree_split_child(CommonTreeNode *parent, int pos, CommonTreeNode *child);
	virtual void btree_insert_nonfull(CommonTreeNode *node, int target);
	virtual void btree_merge_child(CommonTreeNode *root, int pos, CommonTreeNode *y, CommonTreeNode *z);
	virtual void btree_delete_nonone(CommonTreeNode *root, int target);
	virtual int btree_search_successor(CommonTreeNode *root);
	virtual int btree_search_predecessor(CommonTreeNode *root);
	virtual void btree_shift_to_left_child(CommonTreeNode *root, int pos, CommonTreeNode *y, CommonTreeNode *z);
	virtual void btree_shift_to_right_child(CommonTreeNode *root, int pos, CommonTreeNode *y, CommonTreeNode *z);
	virtual CommonTreeNode *btree_insert(CommonTreeNode *root, int target);
	virtual CommonTreeNode *btree_delete(CommonTreeNode *root, int target);
	virtual void btree_inorder_print(CommonTreeNode *root);
	virtual void btree_level_display(CommonTreeNode *root);

public:
	BTree(void);
	~BTree(void);
};

#endif /* BTREE_H */
