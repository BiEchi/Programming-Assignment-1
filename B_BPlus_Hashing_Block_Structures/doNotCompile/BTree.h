#ifndef BTREE_H
#define BTREE_H

#include "Tree.h"
#include <cstring>
using namespace std;

class BTree : public Tree
{
protected:
    // virtual functions
	virtual CommonTreeNode *btree_create();
    virtual CommonTreeNode *btree_node_new();
	virtual int btree_split_child(CommonTreeNode *parent, int pos, CommonTreeNode *child);
    virtual void btree_merge_child(CommonTreeNode *root, int pos, CommonTreeNode *y, CommonTreeNode *z);
    virtual void btree_shift_to_left_child(CommonTreeNode *root, int pos, CommonTreeNode *y, CommonTreeNode *z);
    virtual void btree_shift_to_right_child(CommonTreeNode *root, int pos, CommonTreeNode *y, CommonTreeNode *z);
    
    // real functions
    void btree_insert_nonfull(CommonTreeNode *node, Person* target);
    void btree_delete_nonone(CommonTreeNode *root, string target);
    string btree_search_successor(CommonTreeNode *root);
    string btree_search_predecessor(CommonTreeNode *root);
    void btree_inorder_print(CommonTreeNode *root);
    void btree_level_display(CommonTreeNode *root);

public:
    CommonTreeNode *returnRoot();
    CommonTreeNode *btree_insert(CommonTreeNode *root, Person* target);
    CommonTreeNode *btree_delete(CommonTreeNode *root, string target);
    BTree(void);
    ~BTree(void);
};

#endif /* BTREE_H */
