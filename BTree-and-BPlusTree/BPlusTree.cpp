#include "BPlusTree.h"
#include "struct.h"
#include <unistd.h>
#include <iostream>
using namespace std;

btree_node *BPlusTree::btree_node_new()
{
	btree_node *node = (btree_node *)malloc(sizeof(btree_node));
	if (NULL == node)
	{
		return NULL;
	}

	for (int i = 0; i < 2 * M; i++)
	{
		node->labelArray[i] = "0";
	}

	for (int i = 0; i < 2 * M; i++)
	{
		node->ptrArray[i] = NULL;
	}
	// 数组初始化
	node->BlockPtrarray = vector<block *>(2 * M, 0);
	node->num = 0;
	node->is_leaf = true;
	// node->prev = NULL;
	// node->next = NULL;
	return node;
}

btree_node *BPlusTree::btree_create()
{
	btree_node *node = btree_node_new();
	if (NULL == node)
	{
		return NULL;
	}

	// node->next = node;
	// node->prev = node;

	return node;
}

// split the interior node in Bplus Tree
int BPlusTree::btree_split_child(btree_node *parent, int pos, btree_node *child)
{
	btree_node *new_child = btree_node_new();
	if (NULL == new_child)
	{
		cout << "fail to allocate a new memory in split_child" << endl;
		return -1;
	}
	// 裂节点时的第二个节点（child的兄弟节点）
	new_child->is_leaf = child->is_leaf;
	new_child->num = M;
	child->num = M;

	// 数据拷贝
	for (int i = 0; i < M; i++)
	{
		new_child->labelArray[i] = child->labelArray[i + M];
	}

	// 数据拷贝
	if (false == child->is_leaf)
	{
		for (int i = 0; i < M; i++)
		{
			new_child->ptrArray[i] = child->ptrArray[i + M];
			// empty
			child->ptrArray[i + M] = nullptr;
		}
	}
	else
	{
		for (int i = 0; i < M; i++)
		{
			new_child->BlockPtrarray[i] = child->BlockPtrarray[i + M];
			// empty
			child->BlockPtrarray[i + M] = nullptr;
		}
	}
	// 插入到父节点

	// 移动label
	for (int i = parent->num - 1; i >= pos; i--)
	{
		parent->labelArray[i + 1] = parent->labelArray[i];
	}
	parent->labelArray[pos] = child->labelArray[M - 1];

	// 移动指针
	for (int i = parent->num - 1; i > pos; i--)
	{
		parent->ptrArray[i + 1] = parent->ptrArray[i];
	}
	parent->ptrArray[pos + 1] = new_child;

	parent->num += 1;
	btree_node_num ++;
	return 1;
}

// only call when the node is not full
Person *BPlusTree::bPlustree_insert_nonfull(btree_node *node, Person *target)
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
			while (pos > 0 && target->getID() < node->labelArray[pos])
			{
				pos--;
			}
			blockPtr = node->BlockPtrarray[pos];
			blockPtr = blockPtr->insert(target);
			if (nullptr != blockPtr)
			{
				// update new node and label
				int arrayIndexPtr = node->num;
				node->labelArray[arrayIndexPtr] = blockPtr->maximum();
				node->BlockPtrarray[arrayIndexPtr] = blockPtr;
				node->labelArray[pos] = blockPtr->prevPointer()->maximum();
			}
			else
			{
				if (target->getID() >= node->BlockPtrarray[pos]->maximum())
					node->labelArray[pos] = target->getID();
			}
			cout << "successfully insert the person with ID " << target->getID() << endl;
			return target;
		}
	}
	else
	{
		int pos = node->num - 1;
		while (pos > 0 && target->getID() < node->labelArray[pos])
		{
			pos--;
		}

		if (2 * M == node->ptrArray[pos]->num)
		{
			// 子列表满了就裂
			btree_split_child(node, pos, node->ptrArray[pos]);
			// 判断是要插入前半还是后半
			if (target->getID() > node->labelArray[pos])
			{
				pos++;
			}
		}
		return bPlustree_insert_nonfull(node->ptrArray[pos], target);
	}
}

Person *BPlusTree::bPlustree_insert(btree_node *root, Person *target)
{
	if (NULL == root)
	{
		return NULL;
	}
	// 每个结点能存储2M个
	if (2 * M == root->num)
	{
		btree_node *node = btree_node_new();
		if (NULL == node)
		{
			cout << "fail to allocate a new memory" << endl;
			return nullptr;
		}

		node->is_leaf = false;
		node->ptrArray[0] = root;
		btree_split_child(node, 0, root);

		return bPlustree_insert_nonfull(node, target);
	}
	else
	{
		return bPlustree_insert_nonfull(root, target);
	}
}

void BPlusTree::btree_merge_child(btree_node *root, int pos, btree_node *y, btree_node *z)
{
	y->num = 2 * (M - 1);
	if (true == y->is_leaf)
	{
		for (int i = M; i < 2 * M - 1; i++)
		{
			y->labelArray[i - 1] = z->labelArray[i - M];
			y->BlockPtrarray[i - 1] = z->BlockPtrarray[i - M];
		}
	}
	else
	{
		for (int i = M; i < 2 * M - 1; i++)
		{
			y->labelArray[i - 1] = z->labelArray[i - M];
			y->ptrArray[i - 1] = z->ptrArray[i - M];
		}
	}

	for (int j = pos; j < root->num - 1; j++)
	{
		root->labelArray[j] = root->labelArray[j + 1];
	}
	for (int i = pos + 1; i < root->num - 1; i++)
	{
		root->ptrArray[i] = root->ptrArray[i + 1];
	}
	root->num -= 1;
	btree_node_num --;
	free(z);
}

Person *BPlusTree::bPlustree_delete(btree_node *root, string target)
{
	if (1 == root->num)
	{
		btree_node *y = root->ptrArray[0];
		btree_node *z = root->ptrArray[1];
		if (NULL != y && NULL != z &&
			M - 1 == y->num && M - 1 == z->num)
		{
			// 融合到可以裁剪
			btree_merge_child(root, 0, y, z);
			free(root);
			// 这个时候y作为新的root
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

Person *BPlusTree::bPlustree_delete_nonone(btree_node *root, string target)
{
	if (true == root->is_leaf)
	{
		int i = 0;
		while (i < root->num && target > root->labelArray[i])
			i++;
		block *indexPtr = root->BlockPtrarray[i]->remove(target);
		// judge whether the merge happens
		if (nullptr == indexPtr)
		{
			// update the label if necessary
			if (target == root->labelArray[i])
				root->labelArray[i] = root->BlockPtrarray[i]->maximum();
		}
		// merge happens, synchronously merge with block
		else
		{
			root->labelArray[i] = root->labelArray[i + 1];
			for (int pos = i + 1; pos < root->num - 1; pos++)
			{
				root->labelArray[pos] = root->labelArray[pos + 1];
				root->BlockPtrarray[pos] = root->BlockPtrarray[pos + 1];
			}
		}
		return root->BlockPtrarray[i]->find(target);
	}
	else
	{
		int i = 0;
		btree_node *y = nullptr, *z = nullptr, *p = nullptr;
		while (i < root->num && target > root->labelArray[i])
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
			else if (i < root->num && z->num > M - 1)
			{
				// move one ptr from z to y
				btree_shift_to_left_child(root, i, y, z);
			}
			// if both z and p do not have enough number of data, merge them
			else if (i > 0)
			{
				btree_merge_child(root, i - 1, p, y);
				y = p;
			}
			else
			{
				btree_merge_child(root, i, y, z);
			}
			return bPlustree_delete_nonone(y, target);
		}
		else
		{
			return bPlustree_delete_nonone(y, target);
		}
	}
}

// int BPlusTree::findMin(btree_node *root)
// {
// 	btree_node *z = root;
// 	while (false == z->is_leaf)
// 	{
// 		z = z->ptrArray[0];
// 	}
// 	return z->labelArray[0];
// }

// int BPlusTree::findMax(btree_node *root)
// {
// 	btree_node *y = root;
// 	while (false == y->is_leaf)
// 	{
// 		y = y->ptrArray[y->num];
// 	}
// 	return y->labelArray[y->num - 1];
// }

void BPlusTree::btree_shift_to_right_child(btree_node *root, int pos,
										   btree_node *y, btree_node *z)
{
	z->num++;
	for (int i = z->num - 1; i > 0; i--)
	{
		z->labelArray[i] = z->labelArray[i - 1];
	}
	// if (false == z->is_leaf)
	// {
	z->labelArray[0] = root->labelArray[pos];
	// 提取y的倒数第二个label作为新label
	root->labelArray[pos] = y->labelArray[y->num - 2];
	// else
	// {
	// 	z->labelArray[0] = y->labelArray[y->num - 1];
	// 	root->labelArray[pos] = y->labelArray[y->num - 2];
	// }

	if (false == z->is_leaf)
	{
		for (int i = z->num - 1; i > 0; i--)
		{
			z->ptrArray[i] = z->ptrArray[i - 1];
		}
		z->ptrArray[0] = y->ptrArray[y->num - 1];
	}
	else
	{
		for (int i = z->num - 1; i > 0; i--)
		{
			z->BlockPtrarray[i] = z->BlockPtrarray[i - 1];
		}
		z->BlockPtrarray[0] = y->BlockPtrarray[y->num - 1];
	}
	y->num--;
}

void BPlusTree::btree_shift_to_left_child(btree_node *root, int pos,
										  btree_node *y, btree_node *z)
{
	y->num += 1;

	// if (false == z->is_leaf)
	// {
	y->labelArray[y->num - 1] = root->labelArray[pos];
	root->labelArray[pos] = z->labelArray[0];
	// }
	// else
	// {
	// 	y->labelArray[y->num - 1] = z->labelArray[0];
	// 	root->labelArray[pos] = z->labelArray[0];
	// }

	for (int j = 1; j < z->num; j++)
	{
		z->labelArray[j - 1] = z->labelArray[j];
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

// void BPlusTree::btree_inorder_print(btree_node *root)
// {
// 	if (NULL != root)
// 	{
// 		btree_inorder_print(root->ptrArray[0]);
// 		for (int i = 0; i < root->num; i++)
// 		{
// 			cout << root->labelArray[i] << " ";
// 			// 	fwrite(&root,sizeof(root),1,fp);
// 			btree_inorder_print(root->ptrArray[i + 1]);
// 		}
// 	}
// }

void BPlusTree::btree_linear_print(btree_node *root)
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
			cout << "the " << count + 1 << " th Block" << endl;
			index->display();
			count++;
			index = index->nextPointer();
		}
		return;
	}
}

void BPlusTree::Save(btree_node *root)
{
	//	fwrite(root,sizeof(root),1,pfile);
}

void BPlusTree::btree_level_display(btree_node *root)
{
	// just for simplicty, can't exceed 200 nodes in the tree
	btree_node *queue[200] = {NULL};
	int front = 0;
	int rear = 0;

	queue[rear++] = root;

	while (front < rear)
	{
		btree_node *node = queue[front++];

		printf("[");
		for (int i = 0; i < node->num; i++)
		{
			cout << node->labelArray[i] << " ";
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

// void BPlusTree::findMinAndMax()
// {
// 	cout << "the min is " << findMin(roots) << endl;
// 	cout << "the max is " << findMax(roots) << endl;
// 	return;
// }

// btree_node *BPlusTree::searchTheDataBlockOfTarget(int target)
// {
// 	btree_node *tempPtr = roots;
// 	while (!tempPtr->is_leaf)
// 	{
// 		for (int i = 0; i <= tempPtr->num; i++)
// 		{
// 			// update the pointer if it is the case
// 			if (i == tempPtr->num)
// 			{
// 				tempPtr = tempPtr->ptrArray[tempPtr->num];
// 				break;
// 			}
// 			else
// 			{
// 				if (target <= tempPtr->labelArray[i])
// 				{
// 					tempPtr = tempPtr->ptrArray[i];
// 					break;
// 				}
// 			}
// 		}
// 	}
// 	return tempPtr;
// }

// void BPlusTree::findPredecessorAndSuccessor(int target)
// {
// 	btree_node *datablock = searchTheDataBlockOfTarget(target);
// 	// if the databloclabelArray only have one data, meaning the predecessor is in the previous data bloclabelArray and the successor data bloclabelArray
// 	if (datablock->num == 1)
// 	{
// 		int Predecessor = datablock->prev->labelArray[(datablock->prev->num - 1)];
// 		int Successor = datablock->next->labelArray[0];
// 		// judge the case of Predecessor
// 		if (Predecessor > target)
// 			cout << "the target data does not have Predecessor " << endl;
// 		else
// 			cout << "the Predecessor is " << Predecessor << endl;
// 		// judge the case of Successor
// 		if (Successor < target)
// 			cout << "the target data does not have successor " << endl;
// 		else
// 			cout << "the Successor is " << Successor << endl;
// 		return;
// 	}
// 	// locate the data
// 	for (int i = 0; i < datablock->num; i++)
// 	{
// 		// target data is the first data in the main bloclabelArray
// 		if (datablock->labelArray[i] == target && i == 0)
// 		{
// 			// 判断是否为空;
// 			int Predecessor = datablock->prev->labelArray[(datablock->prev->num - 1)];
// 			if (Predecessor > target)
// 				cout << "the target data does not have Predecessor " << endl;
// 			else
// 				cout << "the Predecessor is " << datablock->prev->labelArray[datablock->prev->num - 1] << endl;
// 			cout << "the Successor is " << datablock->labelArray[1] << endl;
// 			break;
// 		}
// 		// target data is the last data in the main bloclabelArray
// 		else if (datablock->labelArray[i] == target && i == (datablock->num - 1))
// 		{
// 			cout << "the Preredeccor is " << datablock->labelArray[i - 1] << endl;
// 			// 判断是否为空;
// 			int Successor = datablock->next->labelArray[0];
// 			if (Successor < target)
// 				cout << "the target data does not have Successor " << endl;
// 			else
// 				cout << "the Successor is " << datablock->next->labelArray[0] << endl;
// 			break;
// 		}
// 		// the target is in the main bloclabelArray
// 		else if (datablock->labelArray[i] == target)
// 		{
// 			cout << "the Predecessor is " << endl;
// 			cout << "the Successor is " << endl;
// 			break;
// 		}
// 	}
// 	return;
// }

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
	btree_node_num ++;
	begin = doubleBlockHead;
}
btree_node *BPlusTree::returnRoot()
{
	return roots;
}
// int BPlusTree::btree_search_successor(btree_node *root)
// {
// 	return 0;
// }
// int BPlusTree::btree_search_predecessor(btree_node *root)
// {
// 	return 0;
// }