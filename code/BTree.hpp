#ifndef BTREE_H
#define BTREE_H

#include "Tree.hpp"
#include "BPlusTree.hpp"
#include <cstring>
using namespace std;

class BTree : public Tree
{
protected:
    BPlusTree *database = nullptr;
    // virtual functions
    virtual CommonTreeNode *btree_create();
    virtual CommonTreeNode *btree_node_new();
    virtual int btree_split_child(CommonTreeNode *parent, int pos, CommonTreeNode *child);
    virtual void btree_merge_child(CommonTreeNode *root, int pos, CommonTreeNode *y, CommonTreeNode *z);
    virtual void btree_shift_to_left_child(CommonTreeNode *root, int pos, CommonTreeNode *y, CommonTreeNode *z);
    virtual void btree_shift_to_right_child(CommonTreeNode *root, int pos, CommonTreeNode *y, CommonTreeNode *z);

    // real functions
    void btree_insert_nonfull(CommonTreeNode *node, Person *target);
    void btree_delete_nonone(CommonTreeNode *root, Person *target);
    string btree_search_successor(CommonTreeNode *root);
    string btree_search_predecessor(CommonTreeNode *root);
    CommonTreeNode *btree_insert(CommonTreeNode *root, Person *target);
    CommonTreeNode *btree_delete(CommonTreeNode *root, Person *target);
    void btree_inorder_print(CommonTreeNode *root);
    void btree_level_display(CommonTreeNode *root);

public:
    void del(Person *target) { roots = btree_delete(roots, target); };
    void insert(Person *target) { roots = btree_insert(roots, target); };
    void find(string name);
    void print() { btree_inorder_print(roots); };

    BTree(void);
    ~BTree(void);
    // 通过名字比较，但存储ID
    BTree(BPlusTree &Bplustree)
    {
        roots = btree_create();
        database = &Bplustree;
    }
};

#endif /* BTREE_H */
