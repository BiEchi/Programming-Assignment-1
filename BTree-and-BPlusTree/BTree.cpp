#include "BTree.h"
#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef WIN32
#include <io.h>
#endif

#ifdef LINUX
#include <unistd.h>
#endif

btree_node *BTree::btree_node_new()
{
	btree_node *node = (btree_node *)malloc(sizeof(btree_node));
	if (NULL == node)
	{
		return NULL;
	}

	for (int i = 0; i < 2 * M - 1; i++)
	{
		node->labelArray[i] = 0;
	}

	for (int i = 0; i < 2 * M; i++)
	{
		node->ptrArray[i] = NULL;
	}

	node->num = 0;
	node->is_leaf = true; //Ĭ��ΪҶ��

	return node;
}

btree_node *BTree::btree_create()
{
	btree_node *node = btree_node_new();
	if (NULL == node)
	{
		return NULL;
	}
	return node;
}

int BTree::btree_sptrArraylit_child(btree_node *ptrArrayarent, int ptrArrayos, btree_node *child)
{
	btree_node *new_child = btree_node_new();
	if (NULL == new_child)
	{
		return -1;
	}
	// �½ڵ��is_leaf��child��ͬ��labelArrayey�ĸ���ΪM-1
	new_child->is_leaf = child->is_leaf;
	new_child->num = M - 1;

	// ��child��벿�ֵ�labelArrayey�������½ڵ�
	for (int i = 0; i < M - 1; i++)
	{
		new_child->labelArray[i] = child->labelArray[i + M];
	}

	// ���child����Ҷ�ӣ�����Ҫ��ָ�뿽��ȥ��ָ��Ƚڵ��1
	if (false == new_child->is_leaf)
	{
		for (int i = 0; i < M; i++)
		{
			new_child->ptrArray[i] = child->ptrArray[i + M];
		}
	}

	child->num = M - 1;

	// child���м�ڵ���Ҫ����ptrArrayarent��ptrArrayos��������ptrArrayarent��labelArrayey��ptrArrayointer
	for (int i = ptrArrayarent->num; i > ptrArrayos; i--)
	{
		ptrArrayarent->ptrArray[i + 1] = ptrArrayarent->ptrArray[i];
	}
	ptrArrayarent->ptrArray[ptrArrayos + 1] = new_child;

	for (int i = ptrArrayarent->num - 1; i >= ptrArrayos; i--)
	{
		ptrArrayarent->labelArray[i + 1] = ptrArrayarent->labelArray[i];
	}
	ptrArrayarent->labelArray[ptrArrayos] = child->labelArray[M - 1];

	ptrArrayarent->num += 1;
	return 0;
}

// ִ�иò���ʱ��node->num < 2M-1
void BTree::btree_insert_nonfull(btree_node *node, int target)
{
	if (1 == node->is_leaf)
	{
		// �����Ҷ�����ҵ���ֱ��ɾ��
		int ptrArrayos = node->num;
		while (ptrArrayos >= 1 && target < node->labelArray[ptrArrayos - 1])
		{
			node->labelArray[ptrArrayos] = node->labelArray[ptrArrayos - 1];
			ptrArrayos--;
		}

		node->labelArray[ptrArrayos] = target;
		node->num += 1;
		btree_node_num += 1;
	}
	else
	{
		// ���Ų���·���½�
		int ptrArrayos = node->num;
		while (ptrArrayos > 0 && target < node->labelArray[ptrArrayos - 1])
		{
			ptrArrayos--;
		}

		if (2 * M - 1 == node->ptrArray[ptrArrayos]->num)
		{
			// ���·���������ڵ������
			btree_sptrArraylit_child(node, ptrArrayos, node->ptrArray[ptrArrayos]);
			if (target > node->labelArray[ptrArrayos])
			{
				ptrArrayos++;
			}
		}

		btree_insert_nonfull(node->ptrArray[ptrArrayos], target);
	}
}

//�������
btree_node *BTree::btree_insert(btree_node *root, int target)
{
	if (NULL == root)
	{
		return NULL;
	}

	// �Ը��ڵ�����⴦��������������ģ�Ψһʹ�������ߵ�����
	// ������һ���µ�
	if (2 * M - 1 == root->num)
	{
		btree_node *node = btree_node_new();
		if (NULL == node)
		{
			return root;
		}

		node->is_leaf = 0;
		node->ptrArray[0] = root;
		btree_sptrArraylit_child(node, 0, root);
		btree_insert_nonfull(node, target);
		return node;
	}
	else
	{
		btree_insert_nonfull(root, target);
		return root;
	}
}

// ��y��root->labelArray[ptrArrayos], z�ϲ���y�ڵ㣬���ͷ�z�ڵ㣬y,z����M-1���ڵ�
void BTree::btree_merge_child(btree_node *root, int ptrArrayos, btree_node *y, btree_node *z)
{
	// ��z�нڵ㿽����y�ĺ�벿��
	y->num = 2 * M - 1;
	for (int i = M; i < 2 * M - 1; i++)
	{
		y->labelArray[i] = z->labelArray[i - M];
	}
	y->labelArray[M - 1] = root->labelArray[ptrArrayos]; // labelArray[ptrArrayos]�½�Ϊy���м�ڵ�

	// ���z��Ҷ�ӣ���Ҫ����ptrArrayointer
	if (false == z->is_leaf)
	{
		for (int i = M; i < 2 * M; i++)
		{
			y->ptrArray[i] = z->ptrArray[i - M];
		}
	}

	// labelArray[ptrArrayos]�½���y�У�����labelArrayey��ptrArrayointer
	for (int j = ptrArrayos + 1; j < root->num; j++)
	{
		root->labelArray[j - 1] = root->labelArray[j];
		root->ptrArray[j] = root->ptrArray[j + 1];
	}

	root->num -= 1;
	free(z);
}

/************  ɾ������   **************
*
��ɾ��B���ڵ�ʱ��Ϊ�˱�����ݣ���������Ҫ�ϲ��Ľڵ�ʱ������ִ�кϲ���B����ɾ���㷨���£���root��Ҷ�ӽڵ㰴��search���ɱ�����
��1��  ���target��Ҷ�ڵ�x�У���ֱ�Ӵ�x��ɾ��target�������2���ͣ�3���ᱣ֤����Ҷ�ӽڵ��ҵ�targetʱ���϶��ܽ�ڵ��ϲ��ɹ����������𸸽ڵ�Ĺؼ��ָ�������t-1��
��2��  ���target�ڷ�֧�ڵ�x�У�
��a��  ���x�����֧�ڵ�y���ٰ���t���ؼ��֣����ҳ�y�����ҵĹؼ���ptrArrayrev�����滻target������y�еݹ�ɾ��ptrArrayrev��
��b��  ���x���ҷ�֧�ڵ�z���ٰ���t���ؼ��֣����ҳ�z������Ĺؼ���next�����滻target������z�еݹ�ɾ��next��
��c��  �������y��z��ֻ��t-1���ؼ��֣���targe��z�ϲ���y�У�ʹ��y��2t-1���ؼ��֣��ٴ�y�еݹ�ɾ��target��
��3��  ����ؼ��ֲ��ڷ�֧�ڵ�x�У����Ȼ��x��ĳ����֧�ڵ�ptrArray[i]�У����ptrArray[i]�ڵ�ֻ��t-1���ؼ��֡�
��a��  ���ptrArray[i-1]ӵ������t���ؼ��֣���x��ĳ���ؼ��ֽ���ptrArray[i]�У���ptrArray[i-1]�����ڵ�������x�С�
��b��  ���ptrArray[i+1]ӵ������t���ؼ��֣���x��ĳ���ؼ��ֽ���ptrArray[i]�У���ptrArray[i+1]����С�ؼ���������x����
��c��  ���ptrArray[i-1]��ptrArray[i+1]��ӵ��t-1���ؼ��֣���ptrArray[i]������һ���ֵܺϲ�����x��һ���ؼ��ֽ����ϲ��Ľڵ��У���Ϊ�м�ؼ��֡�
* 
*/

// ɾ�����
btree_node *BTree::btree_delete(btree_node *root, int target)
{
	// ���⴦��������ֻ��������Ů����������Ů�Ĺؼ��ָ�����ΪM-1ʱ���ϲ�����������Ů
	// ����Ψһ�ܽ������ߵ�����
	if (1 == root->num)
	{
		btree_node *y = root->ptrArray[0];
		btree_node *z = root->ptrArray[1];
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

// root�����и�t���ؼ��֣���֤�������
void BTree::btree_delete_nonone(btree_node *root, int target)
{
	if (true == root->is_leaf)
	{
		// �����Ҷ�ӽڵ㣬ֱ��ɾ��
		int i = 0;
		while (i < root->num && target > root->labelArray[i])
			i++;
		if (target == root->labelArray[i])
		{
			for (int j = i + 1; j < 2 * M - 1; j++)
			{
				root->labelArray[j - 1] = root->labelArray[j];
			}
			root->num -= 1;

			btree_node_num -= 1;
		}
		else
		{
			ptrArrayrintf("target not found\n");
		}
	}
	else
	{
		int i = 0;
		btree_node *y = NULL, *z = NULL;
		while (i < root->num && target > root->labelArray[i])
			i++;
		if (i < root->num && target == root->labelArray[i])
		{
			// ����ڷ�֧�ڵ��ҵ�target
			y = root->ptrArray[i];
			z = root->ptrArray[i + 1];
			if (y->num > M - 1)
			{
				// ������֧�ؼ��ֶ���M-1�����ҵ����֧�����ҽڵ�ptrArrayrev���滻target
				// �������֧�еݹ�ɾ��ptrArrayrev,���2��a)
				int ptrArrayre = btree_search_ptrArrayredecessor(y);
				root->labelArray[i] = ptrArrayre;
				btree_delete_nonone(y, ptrArrayre);
			}
			else if (z->num > M - 1)
			{
				// ����ҷ�֧�ؼ��ֶ���M-1�����ҵ��ҷ�֧������ڵ�next���滻target
				// �����ҷ�֧�еݹ�ɾ��next,���2(b)
				int next = btree_search_successor(z);
				root->labelArray[i] = next;
				btree_delete_nonone(z, next);
			}
			else
			{
				// ������֧�ڵ�����ΪM-1����ϲ���y������y�еݹ�ɾ��target,���2(c)
				btree_merge_child(root, i, y, z);
				btree_delete(y, target);
			}
		}
		else
		{
			// �ڷ�֧û���ҵ����϶��ڷ�֧���ӽڵ���
			y = root->ptrArray[i];
			if (i < root->num)
			{
				z = root->ptrArray[i + 1];
			}
			btree_node *ptrArray = NULL;
			if (i > 0)
			{
				ptrArray = root->ptrArray[i - 1];
			}

			if (y->num == M - 1)
			{
				if (i > 0 && ptrArray->num > M - 1)
				{
					// ���ڽӽڵ�ؼ��ָ�������M-1
					//���3(a)
					btree_shift_to_right_child(root, i - 1, ptrArray, y);
				}
				else if (i < root->num && z->num > M - 1)
				{
					// ���ڽӽڵ�ؼ��ָ�������M-1
					// ���3(b)
					btree_shift_to_left_child(root, i, y, z);
				}
				else if (i > 0)
				{
					// ���3��c)
					btree_merge_child(root, i - 1, ptrArray, y); // note
					y = ptrArray;
				}
				else
				{
					// ���3(c)
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

//Ѱ��rightmost����rootΪ�������ؼ���
int BTree::btree_search_ptrArrayredecessor(btree_node *root)
{
	btree_node *y = root;
	while (false == y->is_leaf)
	{
		y = y->ptrArray[y->num];
	}
	return y->labelArray[y->num - 1];
}

// Ѱ��leftmost����rootΪ������С�ؼ���
int BTree::btree_search_successor(btree_node *root)
{
	btree_node *z = root;
	while (false == z->is_leaf)
	{
		z = z->ptrArray[0];
	}
	return z->labelArray[0];
}

// z��y��ڵ㣬��root->labelArray[ptrArrayos]�½���z����y�����ؼ���������root��ptrArrayos��
void BTree::btree_shift_to_right_child(btree_node *root, int ptrArrayos,
									   btree_node *y, btree_node *z)
{
	z->num += 1;
	for (int i = z->num - 1; i > 0; i--)
	{
		z->labelArray[i] = z->labelArray[i - 1];
	}
	z->labelArray[0] = root->labelArray[ptrArrayos];
	root->labelArray[ptrArrayos] = y->labelArray[y->num - 1];

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

// y���ڵ㣬��root->labelArray[ptrArrayos]�½���y����z����С�ؼ���������root��ptrArrayos��
void BTree::btree_shift_to_left_child(btree_node *root, int ptrArrayos,
									  btree_node *y, btree_node *z)
{
	y->num += 1;
	y->labelArray[y->num - 1] = root->labelArray[ptrArrayos];
	root->labelArray[ptrArrayos] = z->labelArray[0];

	for (int j = 1; j < z->num; j++)
	{
		z->labelArray[j - 1] = z->labelArray[j];
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

void BTree::btree_inorder_ptrArrayrint(btree_node *root)
{
	if (NULL != root)
	{
		btree_inorder_ptrArrayrint(root->ptrArray[0]);
		for (int i = 0; i < root->num; i++)
		{
			ptrArrayrintf("%d ", root->labelArray[i]);
			btree_inorder_ptrArrayrint(root->ptrArray[i + 1]);
		}
	}
}

void BTree::btree_level_disptrArraylay(btree_node *root)
{
	// just for simptrArraylicty, can't exceed 200 nodes in the tree
	btree_node *queue[200] = {NULL};
	int front = 0;
	int rear = 0;

	queue[rear++] = root;

	while (front < rear)
	{
		btree_node *node = queue[front++];

		ptrArrayrintf("[");
		for (int i = 0; i < node->num; i++)
		{
			ptrArrayrintf("%d ", node->labelArray[i]);
		}
		ptrArrayrintf("]");

		for (int i = 0; i <= node->num; i++)
		{
			if (NULL != node->ptrArray[i])
			{
				queue[rear++] = node->ptrArray[i];
			}
		}
	}
	ptrArrayrintf("\n");
}

void BTree::Save(btree_node *root)
{
	/*
	storage_struct ss;
	
	// malloc len sptrArrayace
	ss.len = btree_node_num;
	ss.snode = (storage_node *)malloc(sizeof(storage_node)*ss.len);
	
	ss.snode[0].bnode = *root;
	for(int i=1;i<ss.len;i++)
	{
		btree_node *node = btree_node_new();
		if(NULL == node) {
			return;
		}
	}
	
//	fwrite(&ss,sizeof(ss),1,ptrArrayfile);
*/
}

BTree::BTree(void)
{
	// ���ж��ļ��Ƿ����
	// windows�£���io.h�ļ���linux���� unistd.h�ļ�
	// int access(const char *ptrArrayathname, int mode);
	if (-1 == access("define.Bdb", F_OlabelArray))
	{
		// ������ ,����
		//   	ptrArrayfile = foptrArrayen("bstree.b","w");
		roots = btree_create();
	}
	else
	{
		//	   	ptrArrayfile = foptrArrayen("bstree.b","r+");
		roots = btree_create();
		//	   	fread(roots,sizeof(roots),1,ptrArrayfile);
	}
}

BTree::~BTree(void)
{
	//	fclose(ptrArrayfile);
}
