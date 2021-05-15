#include <unistd.h>
#include <iostream>

#include "BPlusTree.hpp"
#include "block.hpp"

using namespace std;

/// @brief create a new B Tree node
CommonTreeNode *BPlusTree::btree_node_new()
{
	CommonTreeNode *node = new CommonTreeNode;
	if (NULL == node)
	{
		cout << "fail to allocate a new memory" << endl;
		return nullptr;
	}

	// initialize vectors
	node->labelArrayForBPlusTree = vector<string>(2 * M, "0");
	node->ptrArray = vector<CommonTreeNode *>(2 * M, nullptr);
	node->BlockPtrarray = vector<block *>(2 * M, nullptr);
	node->num = 0;
	node->is_leaf = true;
	return node;
}

/// @brief create a new B Tree (with the return pointer pointing to the root)
CommonTreeNode *BPlusTree::btree_create()
{
	CommonTreeNode *node = btree_node_new();
	return node;
}

/// @brief split the interior node in B plus Tree
int BPlusTree::btree_split_child(CommonTreeNode *parent, int pos, CommonTreeNode *child)
{
	CommonTreeNode *new_child = btree_node_new();
	if (NULL == new_child)
	{
		cout << "fail to allocate a new memory in split_child" << endl;
		return -1;
	}
	btree_node_num++;
	parent->labelArrayForBPlusTree[pos] = child->labelArrayForBPlusTree[2 * M - 1];
	// 裂节点时的第二个节点（child的兄弟节点）
	new_child->is_leaf = child->is_leaf;
	new_child->num = M;

	// 数据拷贝
	for (int i = 0; i < M; i++)
	{
		new_child->labelArrayForBPlusTree[i] = child->labelArrayForBPlusTree[i + M];
	}

	// 数据拷贝
	if (false == child->is_leaf)
	{
		for (int i = 0; i < M; i++)
		{
			new_child->ptrArray[i] = child->ptrArray[i + M];
			// empty
			child->ptrArray[i + M] = nullptr;
			child->labelArrayForBPlusTree[i + M] = "0";
		}
	}
	else
	{
		for (int i = 0; i < M; i++)
		{
			new_child->BlockPtrarray[i] = child->BlockPtrarray[i + M];
			// empty
			child->BlockPtrarray[i + M] = nullptr;
			child->labelArrayForBPlusTree[i + M] = "0";
		}
	}
	// 插入到父节点

	// 移动label
	for (int i = parent->num - 1; i >= pos; i--)
	{
		parent->labelArrayForBPlusTree[i + 1] = parent->labelArrayForBPlusTree[i];
	}
	parent->labelArrayForBPlusTree[pos] = child->labelArrayForBPlusTree[M - 1];

	// 移动指针
	for (int i = parent->num - 1; i > pos; i--)
	{
		parent->ptrArray[i + 1] = parent->ptrArray[i];
	}
	parent->ptrArray[pos + 1] = new_child;

	child->num = M;
	parent->num += 1;
	return 1;
}

// only call when the node is not full
Person *BPlusTree::bPlustree_insert_nonfull(CommonTreeNode *node, Person *target)
{
	// insert new node
	if (true == node->is_leaf)
	{
		int pos = node->num - 1;
		block *blockPtr = node->BlockPtrarray[pos];
		if (nullptr == blockPtr)
		{
			cout << "this node doesn't have block" << endl;
			return nullptr;
		}
		else
		{
			while (pos > 0 && target->getID() < node->labelArrayForBPlusTree[pos])
			{
				pos--;
			}
			blockPtr = node->BlockPtrarray[pos];
			blockPtr = blockPtr->insert(target);
			if (nullptr != blockPtr)
			{
				// update new node and label
				int arrayIndexPtr = node->num;
				// 向右增长,移项空位置
				while (arrayIndexPtr > pos + 1)
				{
					node->labelArrayForBPlusTree[arrayIndexPtr] = node->labelArrayForBPlusTree[arrayIndexPtr - 1];
					node->BlockPtrarray[arrayIndexPtr] = node->BlockPtrarray[arrayIndexPtr - 1];
					arrayIndexPtr--;
				}
				node->labelArrayForBPlusTree[arrayIndexPtr] = blockPtr->maximum();
				node->BlockPtrarray[arrayIndexPtr] = blockPtr;
				node->labelArrayForBPlusTree[pos] = blockPtr->prevPointer()->maximum();
				node->num++;
			}
			else
			{
				// pos的意义：当前插入的id一定比pos对应的label要大（一定更新），到pos为0（这种情况不一定更新）
				if (target->getID() >= node->BlockPtrarray[pos]->maximum())
					node->labelArrayForBPlusTree[pos] = target->getID();
			}
			return target;
		}
	}
	else
	{
		int pos = node->num - 1;
		while (pos > 0 && target->getID() < node->labelArrayForBPlusTree[pos])
		{
			pos--;
		}

		if (2 * M == node->ptrArray[pos]->num)
		{
			// 子列表满了就裂
			btree_split_child(node, pos, node->ptrArray[pos]);
			// 判断是要插入前半还是后半
			if (target->getID() > node->labelArrayForBPlusTree[pos])
			{
				pos++;
			}
		}
		if (target->getID() > node->labelArrayForBPlusTree[pos])
			node->labelArrayForBPlusTree[pos] = target->getID();
		return bPlustree_insert_nonfull(node->ptrArray[pos], target);
	}
}

/// @brief insert one person into the B+ Tree
Person *BPlusTree::bPlustree_insert(CommonTreeNode *root, Person *target)
{
	if (NULL == root)
	{
		cout << "Error: no such a tree" << endl;
		return NULL;
	}
	// 每个结点能存储2M个
	if (2 * M == root->num)
	{
		CommonTreeNode *node = btree_node_new();
		if (NULL == node)
		{
			cout << "fail to allocate a new memory" << endl;
			return nullptr;
		}
		btree_node_num++;

		node->is_leaf = false;
		node->ptrArray[0] = root;
		node->num++;
		btree_split_child(node, 0, root);
		if (root == roots)
		{
			roots = node;
		}
		return bPlustree_insert_nonfull(node, target);
	}
	else
	{
		return bPlustree_insert_nonfull(root, target);
	}
}

void BPlusTree::btree_merge_child(CommonTreeNode *root, int pos, CommonTreeNode *y, CommonTreeNode *z)
{
	y->num = 2 * (M - 1);
	if (true == y->is_leaf)
	{
		for (int i = M; i < 2 * M - 1; i++)
		{
			y->labelArrayForBPlusTree[i - 1] = z->labelArrayForBPlusTree[i - M];
			y->BlockPtrarray[i - 1] = z->BlockPtrarray[i - M];
		}
	}
	else
	{
		for (int i = M; i < 2 * M - 1; i++)
		{
			y->labelArrayForBPlusTree[i - 1] = z->labelArrayForBPlusTree[i - M];
			y->ptrArray[i - 1] = z->ptrArray[i - M];
		}
	}

	for (int j = pos; j < root->num - 1; j++)
	{
		root->labelArrayForBPlusTree[j] = root->labelArrayForBPlusTree[j + 1];
	}
	for (int i = pos + 1; i < root->num - 1; i++)
	{
		root->ptrArray[i] = root->ptrArray[i + 1];
	}
	root->num -= 1;
	btree_node_num--;
	free(z);
}

Person *BPlusTree::bPlustree_delete(CommonTreeNode *root, const string target)
{
	// 减小树的高度
	if (1 == root->num)
	{
		CommonTreeNode *y = root->ptrArray[0];
		if (NULL != y && M - 1 == y->num)
		{
			// 融合到可以裁剪
			free(root);
			// 这个时候y作为新的root
			if (root == roots)
			{
				roots = y;
			}
			return bPlustree_delete_nonone(y, target);
		}
		else
		{
			return bPlustree_delete_nonone(root, target);
		}
	}
	else
	{
		return bPlustree_delete_nonone(root, target);
	}
}

Person *BPlusTree::bPlustree_delete_nonone(CommonTreeNode *root, string target)
{
	if (true == root->is_leaf)
	{
		int i = 0;
		while (i < root->num - 1 && target > root->labelArrayForBPlusTree[i])
			i++;
		personIndex = root->BlockPtrarray[i]->find(target);
		block *indexPtr = root->BlockPtrarray[i]->remove(target);
		// judge whether the merge happens
		// merge happens, synchronously merge with block
		if (nullptr != indexPtr)
		{
			root->labelArrayForBPlusTree[i] = root->labelArrayForBPlusTree[i + 1];
			root->labelArrayForBPlusTree[i + 1] = "0";
			for (int pos = i + 1; pos < root->num - 1; pos++)
			{
				root->labelArrayForBPlusTree[pos] = root->labelArrayForBPlusTree[pos + 1];
				root->BlockPtrarray[pos] = root->BlockPtrarray[pos + 1];
			}
			root->num--;
		}
		// update the label for returning and maintaining the BPlusTree
		dynamicIDForMaintain = root->BlockPtrarray[i]->maximum();
		if ("" == dynamicIDForMaintain)
		{
			block *previous = root->BlockPtrarray[i]->prevPointer();
			if (nullptr != previous)
			{
				dynamicIDForMaintain = previous->maximum();
				root->BlockPtrarray[i] = nullptr;
				root->num--;
			}
			root->labelArrayForBPlusTree[i] = "0";
		}
		else
			root->labelArrayForBPlusTree[i] = dynamicIDForMaintain;
		return personIndex;
	}
	else
	{
		int i = 0;
		CommonTreeNode *y = nullptr, *z = nullptr, *p = nullptr;
		while (i < root->num && target > root->labelArrayForBPlusTree[i])
			i++;
		// next node's address
		y = root->ptrArray[i];
		if (i < root->num)
		{
			// next
			z = root->ptrArray[i + 1];
		}
		if (i > 0)
		{
			// previous
			p = root->ptrArray[i - 1];
		}
		// time to merge
		if (y->num == M - 1)
		{
			// 做一波数据量平衡
			if (i > 0 && p->num > M - 1)
			{
				// move one ptr from p to y
				btree_shift_to_right_child(root, i - 1, p, y);
			}
			else if (i < root->num && (nullptr != z) && z->num > M - 1)
			{
				// move one ptr from z to y
				btree_shift_to_left_child(root, i, y, z);
			}
			// if both z and p do not have enough number of data, merge them
			else if (i > 0)
			{
				btree_merge_child(root, i - 1, p, y);
				y = p;
				i--;
			}
			else
			{
				btree_merge_child(root, i, y, z);
			}
			Person *deletePerson = bPlustree_delete_nonone(y, target);
			if (target == root->labelArrayForBPlusTree[i])
			{
				root->labelArrayForBPlusTree[i] = dynamicIDForMaintain;
			}
			return deletePerson;
		}
		else
		{
			Person *deletePerson = bPlustree_delete_nonone(y, target);
			if (target == root->labelArrayForBPlusTree[i])
			{
				root->labelArrayForBPlusTree[i] = dynamicIDForMaintain;
			}
			return deletePerson;
		}
	}
}

void BPlusTree::btree_shift_to_right_child(CommonTreeNode *root, int pos,
										   CommonTreeNode *y, CommonTreeNode *z)
{
	z->num++;
	for (int i = z->num - 1; i > 0; i--)
	{
		z->labelArrayForBPlusTree[i] = z->labelArrayForBPlusTree[i - 1];
	}
	z->labelArrayForBPlusTree[0] = root->labelArrayForBPlusTree[pos];
	y->labelArrayForBPlusTree[y->num - 1] = "0";
	// 提取y的倒数第二个label作为新label
	root->labelArrayForBPlusTree[pos] = y->labelArrayForBPlusTree[y->num - 2];

	if (false == z->is_leaf)
	{
		for (int i = z->num - 1; i > 0; i--)
		{
			z->ptrArray[i] = z->ptrArray[i - 1];
		}
		z->ptrArray[0] = y->ptrArray[y->num - 1];
		y->ptrArray[y->num - 1] = nullptr;
	}
	else
	{
		for (int i = z->num - 1; i > 0; i--)
		{
			z->BlockPtrarray[i] = z->BlockPtrarray[i - 1];
		}
		z->BlockPtrarray[0] = y->BlockPtrarray[y->num - 1];
		y->BlockPtrarray[y->num - 1] = nullptr;
	}
	y->num--;
}

void BPlusTree::btree_shift_to_left_child(CommonTreeNode *root, int pos,
										  CommonTreeNode *y, CommonTreeNode *z)
{
	y->num += 1;

	root->labelArrayForBPlusTree[pos] = z->labelArrayForBPlusTree[0];
	y->labelArrayForBPlusTree[y->num - 1] = root->labelArrayForBPlusTree[pos];

	for (int j = 1; j < z->num; j++)
	{
		z->labelArrayForBPlusTree[j - 1] = z->labelArrayForBPlusTree[j];
		z->labelArrayForBPlusTree[j] = "0";
	}

	if (false == z->is_leaf)
	{
		y->ptrArray[y->num - 1] = z->ptrArray[0];
		for (int j = 1; j <= z->num - 1; j++)
		{
			z->ptrArray[j - 1] = z->ptrArray[j];
		}
	}
	else
	{
		y->BlockPtrarray[y->num - 1] = z->BlockPtrarray[0];
		for (int j = 1; j <= z->num - 1; j++)
		{
			z->BlockPtrarray[j - 1] = z->BlockPtrarray[j];
		}
	}
	z->num -= 1;
}

void BPlusTree::btree_linear_print(CommonTreeNode *root)
{
	if (nullptr == begin)
	{
		cout << "there is no block" << endl;
		return;
	}
	else
	{
		block *index = begin;
		int count = 0;
		while (nullptr != index)
		{
			usleep(100000);
			cout << "the " << count + 1 << " th Block" << endl;
			index->display();
			count++;
			index = index->nextPointer();
		}
		return;
	}
}

void BPlusTree::btree_level_display(CommonTreeNode *root)
{
	// just for simplicty, can't exceed 200 nodes in the tree
	CommonTreeNode *queue[200] = {NULL};
	int front = 0;
	int rear = 0;

	queue[rear++] = root;

	while (front < rear)
	{
		CommonTreeNode *node = queue[front++];

		printf("[");
		for (int i = 0; i < node->num; i++)
		{
			cout << node->labelArrayForBPlusTree[i] << " ";
		}
		printf("]");
		for (int i = 0; i <= node->num; i++)
		{
			if (NULL != node->ptrArray[i])
			{
				queue[rear++] = node->ptrArray[i];
			}
		}
	}
	printf("\n");
}

void BPlusTree::linear_print()
{
	btree_linear_print(roots);
}

CommonTreeNode *BPlusTree::returnRoot()
{
	return roots;
}

BPlusTree::BPlusTree(void)
{
	return;
}

BPlusTree::~BPlusTree(void)
{
	return;
}

BPlusTree::BPlusTree(block *doubleBlockHead)
{
	roots = btree_create();
	roots->BlockPtrarray[0] = doubleBlockHead;
	roots->num++;
	btree_node_num++;
	begin = doubleBlockHead;
}

Person *BPlusTree::find(string &ID)
{
	CommonTreeNode *temp = roots;
	while (temp->is_leaf != true)
	{
		for (int i = 0; i < temp->num; i++)
		{
			if (ID <= temp->labelArrayForBPlusTree[i])
			{
				temp = temp->ptrArray[i];
				break;
			}
		}
	}
	// ergodic in blocklist
	for (int i = 0; i < temp->num; i++)
	{
		if (ID <= temp->labelArrayForBPlusTree[i])
			return temp->BlockPtrarray[i]->find(ID);
	}
	cout << "block finding fails!" << endl;
	return nullptr;
}