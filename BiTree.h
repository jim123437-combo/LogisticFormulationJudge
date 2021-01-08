#pragma once

#define OK 0
#define TRUE 1
#define FALSE 0
#define ERROR -1
#define ElemType char

typedef struct BiTreeNode
{
	ElemType data;
	int Value;
	BiTreeNode* lchild;
	BiTreeNode* rchild;
}*BiTree;

void ShowTreePre(BiTree& T, bool(*visit)(char));
void AssignTraversal(BiTree& T, int* ValueChart);
void AssignValue(BiTree& T, int i, int NumOfVariety);
int GetTreeValue(BiTree& T);
int InitBTNode(BiTree& T);

void ShowTreePre(BiTree& T,bool(*visit)(char))
{
	if (T)
	{
		visit(T->data);
		ShowTreePre(T->lchild,visit);
		ShowTreePre(T->rchild,visit);
	}
}

void AssignTraversal(BiTree& T, int* ValueChart)
{
	if (T)
	{
		if (isalpha(T->data)) T->Value = ValueChart[T->data - 'A'];
		AssignTraversal(T->lchild, ValueChart);
		AssignTraversal(T->rchild, ValueChart);
	}
}

void AssignValue(BiTree& T, int i, int NumOfVariety)
{
	int* ValueChart = (int*)malloc(NumOfVariety * sizeof(int));
	for (int k = 0; k < NumOfVariety; k++)
	{
		ValueChart[k] = i % 2;
		i /= 2;
	}
	AssignTraversal(T, ValueChart);
}

int GetTreeValue(BiTree& T)
{
	if (T)
	{
		if (T->data == '&') T->Value = GetTreeValue(T->lchild) & GetTreeValue(T->rchild);
		if (T->data == '|') T->Value = GetTreeValue(T->lchild) | GetTreeValue(T->rchild);
		if (T->data == '~')	T->Value = !GetTreeValue(T->rchild);
		if (T->data == '0') T->Value = 0;
		if (T->data == '1') T->Value = 1;
	};
	return T->Value;
}

int InitBTNode(BiTree& T)
{
	T = (BiTree)malloc(sizeof(BiTreeNode));
	if (!T) return ERROR;
	T->lchild = NULL;
	T->rchild = NULL;
}