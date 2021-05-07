#ifndef BPLUSTREE_H
#define BPLUSTREE_H
#include "block.h"
#include "struct.h"
#include "Tree.h"
#include <string>

class BPlusTree : public Tree
{
private:
	block *begin = nullptr;
	string dynamicIDForMaintain = "0";
protected:
	virtual btree_node *btree_create();
	virtual btree_node *btree_node_new();
	// split and merge interior nodes
	virtual int btree_split_child(btree_node *parent, int pos, btree_node *child);
	virtual void btree_merge_child(btree_node *root, int pos, btree_node *y, btree_node *z);

	virtual void btree_shift_to_left_child(btree_node *root, int pos, btree_node *y, btree_node *z);
	virtual void btree_shift_to_right_child(btree_node *root, int pos, btree_node *y, btree_node *z);

	// virtual int btree_search_successor(btree_node *root);
	// virtual int btree_search_predecessor(btree_node *root);

	Person *bPlustree_insert_nonfull(btree_node *node, Person *target);
	Person *bPlustree_delete_nonone(btree_node *root, string target);

	// virtual void btree_inorder_print(btree_node *root);
	virtual void btree_level_display(btree_node *root);
	virtual void Save(btree_node *root);
	/**
	 * @brief print tree linearly using prev/next pointer
	 *
	 * @param root: root of tree
	 */
	void btree_linear_print(btree_node *root);

	// // find the Max of BPT
	// int findMax(btree_node *root);
	// // find the Min of BPT
	// int findMin(btree_node *root);
	// btree_node *searchTheDataBlockOfTarget(int target);

public:
	BPlusTree(void);
	~BPlusTree(void);
	BPlusTree(block *doubleBlockHead);

	void linear_print();
	// void findMinAndMax();
	// void findPredecessorAndSuccessor(int target);
	btree_node *returnRoot();
	// 返回删除后block中最大值的指针（用于动态地更新路径）
	// 返回删除的人的指针
	Person *bPlustree_delete(btree_node *root, string target);
	// 返回加入的人的指针
	Person *bPlustree_insert(btree_node *root, Person *target);
};

#endif
