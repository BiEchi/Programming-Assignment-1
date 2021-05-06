#include <stdio.h>
#include <stdlib.h>
#include "BTree.h"
#include "BPlusTree.h"
#include "Context.h"

int main()
{

	/*************************************ֱ�ӵ���B  B+ �ĵ���ʹ��****************************************/
	/************************************* Direct call B + B method ****************************************/
	BTree bt;
	BPlusTree bpt;

	int arr[] = {18, 31, 12, 10, 15, 48, 45, 47, 50, 52, 23, 30, 20};
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
	{
		bt.insert(arr[i]);
		bpt.insert(arr[i]);
	}
	printf("no delete data:\n");
	printf("display about B-Tree:\n");
	bt.level_display();
	bt.inorder_print();
	printf("\n\n");

	printf("display about B+ Tree:\n");
	bt.level_display();
	bt.inorder_print();
	printf("\n");
	bpt.linear_print();
	printf("\n");
	bt.NodeNum_print();
	bpt.NodeNum_print();
	printf("delete data...\n");
	int todel[] = {15, 18, 23, 30, 31, 52, 50};

	for (int i = 0; i < sizeof(todel) / sizeof(int); i++)
	{
		printf("after delete %d\n", todel[i]);
		bt.del(todel[i]);
		bpt.del(todel[i]);
	}

	bt.NodeNum_print();
	bpt.NodeNum_print();

	printf("\n\ndelete after data:\n");
	printf("display about B-Tree:\n");
	bt.level_display();
	bt.inorder_print();
	printf("\n\n");

	printf("display about B+ Tree:\n");
	bpt.level_display();
	bpt.inorder_print();
	printf("\n");
	bpt.linear_print();
	printf("\n");

	/***************************************************************************************************/
	/***************************************************************************************************/
	/************************************* �ò��Է����ĵ���B    ****************************************/
	/************************************* strategy pattern method ****************************************/

	printf("strategy method start\n");

	//����������ࡱֻ�ڶ������������ࡱʱʹ��
	Context *Context_A = new Context(new BTree()),
			*Context_B = new Context(new BPlusTree());

	//���÷�����ֻͨ���������ࡱʵ�֣��㷨֮��Ĳ����ѱ�����
	int arrnum[] = {10, 2, 3, 4, 5, 9, 8, 7, 6, 1};
	for (int i = 0; i < sizeof(arrnum) / sizeof(int); i++)
	{
		Context_A->Insert(arrnum[i]);
		Context_B->Insert(arrnum[i]);
	}
	Context_A->Inorder_Print();
	printf("\n\n");
	Context_B->LevelDisplay();

	/***************************************************************************************************/
	/***************************************************************************************************/
	return 0;
}
