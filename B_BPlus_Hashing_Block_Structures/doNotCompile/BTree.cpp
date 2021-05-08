#include "BTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef WIN32
#include <io.h>
#endif

#ifdef LINUX
#include <unistd.h>
#endif

CommonTreeNode *BTree::btree_node_new()
{
	CommonTreeNode *node = (CommonTreeNode *)malloc(sizeof(CommonTreeNode));
	if (NULL == node)
	{
		return NULL;
	}

	for (int i = 0; i < 2 * M - 1; i++)
	{
		node->labelArrayForBTree[i] = "0";
	}

	for (int i = 0; i < 2 * M; i++)
	{
		node->ptrArray[i] = NULL;
	}

	node->num = 0;
	node->is_leaf = true;

	return node;
}

CommonTreeNode *BTree::btree_create()
{
	CommonTreeNode *node = btree_node_new();
	if (NULL == node)
	{
		return NULL;
	}
	return node;
}

int BTree::btree_split_child(CommonTreeNode *parent, int pos, CommonTreeNode *child)
{
	CommonTreeNode *new_child = btree_node_new();
	if (NULL == new_child)
	{
		return -1;
	}
    new_child->is_leaf = child->is_leaf;
	new_child->num = M - 1;

	for (int i = 0; i < M - 1; i++)
	{
		new_child->labelArrayForBTree[i] = child->labelArrayForBTree[i + M];
	}

	if (false == new_child->is_leaf)
	{
		for (int i = 0; i < M; i++)
		{
			new_child->ptrArray[i] = child->ptrArray[i + M];
		}
	}

	child->num = M - 1;

	for (int i = parent->num; i > pos; i--)
	{
		parent->ptrArray[i + 1] = parent->ptrArray[i];
	}
	parent->ptrArray[pos + 1] = new_child;

	for (int i = parent->num - 1; i >= pos; i--)
	{
		parent->labelArrayForBTree[i + 1] = parent->labelArrayForBTree[i];
	}
	parent->labelArrayForBTree[pos] = child->labelArrayForBTree[M - 1];

	parent->num += 1;
	return 0;
}

void BTree::btree_insert_nonfull(CommonTreeNode *node, int target)
{
	if (1 == node->is_leaf)
	{
		int pos = node->num;
		while (pos >= 1 && target < node->labelArrayForBTree[pos - 1])
		{
			node->labelArrayForBTree[pos] = node->labelArrayForBTree[pos - 1];
            pos--;
		}

		node->labelArrayForBTree[pos] = target;
		node->num += 1;
		btree_node_num += 1;
	}
	else
	{
        int pos = node->num;
		while (pos > 0 && target < node->labelArrayForBTree[pos - 1])
		{
			pos--;
		}

		if (2 * M - 1 == node->ptrArray[pos]->num)
		{
            btree_split_child(node, pos, node->ptrArray[pos]);
			if (target > node->labelArrayForBTree[pos])
			{
				pos++;
			}
		}

		btree_insert_nonfull(node->ptrArray[pos], target);
	}
}

CommonTreeNode *BTree::btree_insert(CommonTreeNode *root, int target)
{
	if (NULL == root)
	{
		return NULL;
	}

	if (2 * M - 1 == root->num)
	{
		CommonTreeNode *node = btree_node_new();
		if (NULL == node)
		{
			return root;
		}

		node->is_leaf = 0;
		node->ptrArray[0] = root;
		btree_split_child(node, 0, root);
		btree_insert_nonfull(node, target);
		return node;
	}
	else
	{
		btree_insert_nonfull(root, target);
		return root;
	}
}

void BTree::btree_merge_child(CommonTreeNode *root, int pos, CommonTreeNode *y, CommonTreeNode *z)
{
	y->num = 2 * M - 1;
	for (int i = M; i < 2 * M - 1; i++)
	{
		y->labelArrayForBTree[i] = z->labelArrayForBTree[i - M];
	}
	y->labelArrayForBTree[M - 1] = root->labelArrayForBTree[pos];
    
	if (false == z->is_leaf)
	{
		for (int i = M; i < 2 * M; i++)
		{
			y->ptrArray[i] = z->ptrArray[i - M];
		}
	}

	for (int j = pos + 1; j < root->num; j++)
	{
		root->labelArrayForBTree[j - 1] = root->labelArrayForBTree[j];
		root->ptrArray[j] = root->ptrArray[j + 1];
	}

	root->num -= 1;
	free(z);
}

CommonTreeNode *BTree::btree_delete(CommonTreeNode *root, int target)
{
	if (1 == root->num)
	{
		CommonTreeNode *y = root->ptrArray[0];
		CommonTreeNode *z = root->ptrArray[1];
		if (NULL != y && NULL != z &&
			M - 1 == y->num && M - 1 == z->num)
		{
			btree_merge_child(root, 0, y, z);
			free(root);
			btree_delete_nonone(y, target);
			return y;
		}
		else
		{
			btree_delete_nonone(root, target);
			return root;
		}
	}
	else
	{
		btree_delete_nonone(root, target);
		return root;
	}
}

void BTree::btree_delete_nonone(CommonTreeNode *root, int target)
{
	if (true == root->is_leaf)
	{
		int i = 0;
		while (i < root->num && target > stoi(root->labelArrayForBTree[i]))
			i++;
		if (target == root->labelArrayForBTree[i])
		{
			for (int j = i + 1; j < 2 * M - 1; j++)
			{
				root->labelArrayForBTree[j - 1] = root->labelArrayForBTree[j];
			}
			root->num -= 1;

			btree_node_num -= 1;
		}
		else
		{
			printf("target not found\n");
		}
	}
	else
	{
		int i = 0;
		CommonTreeNode *y = NULL, *z = NULL;
		while (i < root->num && target > root->labelArrayForBTree[i])
			i++;
		if (i < root->num && target == root->labelArrayForBTree[i])
		{
            y = root->ptrArray[i];
			z = root->ptrArray[i + 1];
			if (y->num > M - 1)
			{
				int pre = btree_search_predecessor(y);
				root->labelArrayForBTree[i] = pre;
				btree_delete_nonone(y, pre);
			}
			else if (z->num > M - 1)
			{
				int next = btree_search_successor(z);
				root->labelArrayForBTree[i] = next;
				btree_delete_nonone(z, next);
			}
			else
			{
                btree_merge_child(root, i, y, z);
				btree_delete(y, target);
			}
		}
		else
        {
            y = root->ptrArray[i];
			if (i < root->num)
			{
				z = root->ptrArray[i + 1];
			}
			CommonTreeNode *ptrArray = NULL;
			if (i > 0)
			{
				ptrArray = root->ptrArray[i - 1];
			}

			if (y->num == M - 1)
			{
				if (i > 0 && ptrArray->num > M - 1)
				{
					btree_shift_to_right_child(root, i - 1, ptrArray, y);
				}
				else if (i < root->num && z->num > M - 1)
				{
					btree_shift_to_left_child(root, i, y, z);
				}
				else if (i > 0)
				{
					btree_merge_child(root, i - 1, ptrArray, y); // note
					y = ptrArray;
				}
				else
				{
					btree_merge_child(root, i, y, z);
				}
				btree_delete_nonone(y, target);
			}
			else
			{
				btree_delete_nonone(y, target);
			}
		}
	}
}

int BTree::btree_search_predecessor(CommonTreeNode *root)
{
	CommonTreeNode *y = root;
	while (false == y->is_leaf)
	{
		y = y->ptrArray[y->num];
	}
	return y->labelArrayForBTree[y->num - 1];
}

int BTree::btree_search_successor(CommonTreeNode *root)
{
	CommonTreeNode *z = root;
	while (false == z->is_leaf)
	{
		z = z->ptrArray[0];
	}
	return z->labelArrayForBTree[0];
}

void BTree::btree_shift_to_right_child(CommonTreeNode *root, int pos,
									   CommonTreeNode *y, CommonTreeNode *z)
{
	z->num += 1;
	for (int i = z->num - 1; i > 0; i--)
	{
		z->labelArrayForBTree[i] = z->labelArrayForBTree[i - 1];
	}
	z->labelArrayForBTree[0] = root->labelArrayForBTree[pos];
	root->labelArrayForBTree[pos] = y->labelArrayForBTree[y->num - 1];

	if (false == z->is_leaf)
	{
		for (int i = z->num; i > 0; i--)
		{
			z->ptrArray[i] = z->ptrArray[i - 1];
		}
		z->ptrArray[0] = y->ptrArray[y->num];
	}

	y->num -= 1;
}

void BTree::btree_shift_to_left_child(CommonTreeNode *root, int pos,
									  CommonTreeNode *y, CommonTreeNode *z)
{
	y->num += 1;
	y->labelArrayForBTree[y->num - 1] = root->labelArrayForBTree[pos];
	root->labelArrayForBTree[pos] = z->labelArrayForBTree[0];

	for (int j = 1; j < z->num; j++)
	{
		z->labelArrayForBTree[j - 1] = z->labelArrayForBTree[j];
	}

	if (false == z->is_leaf)
	{
		y->ptrArray[y->num] = z->ptrArray[0];
		for (int j = 1; j <= z->num; j++)
		{
			z->ptrArray[j - 1] = z->ptrArray[j];
		}
	}

	z->num -= 1;
}

void BTree::btree_inorder_print(CommonTreeNode *root)
{
	if (NULL != root)
	{
		btree_inorder_print(root->ptrArray[0]);
		for (int i = 0; i < root->num; i++)
		{
			printf("%d ", root->labelArrayForBTree[i]);
			btree_inorder_print(root->ptrArray[i + 1]);
		}
	}
}

void BTree::btree_level_display(CommonTreeNode *root)
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
			printf("%d ", node->labelArrayForBTree[i]);
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
