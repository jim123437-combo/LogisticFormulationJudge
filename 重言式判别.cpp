#include <iostream>
#include <stack>
#include <string>
#include <algorithm>
#include <vector>
#include <cmath>
#include "BiTree.h"

using namespace std;

stack<BiTree>OPS;
stack<BiTree>ODS;
vector<char>VarietyChart;
vector<char>::iterator it;

BiTree T;

bool isOperateNum(char C);
bool isParenthese(char C);
bool isOperateSign(char C);
bool isLegal(string& Exp);
void ShowUserInterface();
char ComparePriority(char C1, char C2);
int JudgePatern(BiTree& T, int NumOfVariety);
int GetNumberOfVariety(string ExpressionFormulation);
int CreateLogisticBinaryTree(BiTree& T, stack<BiTree>& ODS, stack<BiTree>& OPS, string ExpForm);


bool isOperateNum(char C)
{
	if (C >= 'A' && C <= 'Z') return TRUE;
	if (C == '0' || C == '1') return TRUE;
	else return FALSE;
}

bool isParenthese(char C)
{
	if (C == ')' || C == '(') return TRUE;
	return FALSE;
}

bool isOperateSign(char C)
{
	if (C == '&' || C == '|' || C == '~'||C == '(' || C==')') return TRUE;
	return FALSE;
}

bool isLegal(string& Exp)
{
	int LeftParentheseNum = 0;
	int RightParentheseNum = 0;
	if (!isOperateNum(Exp[0]) && Exp[0] != '~')
	{
		cout << "������ı��ʽ��������������:" << endl;
		return FALSE;
	}
	if (!isOperateNum(Exp[Exp.length() - 1])&&Exp[Exp.length()-1]!=')')
	{
		cout << "������ı��ʽ��������������:" << endl;
		return FALSE;
	}
	if(!VarietyChart.empty())
	if (VarietyChart[0] != 'A')
	{
		cout << "������ı��ʽ��������������:" << endl;
		return FALSE;
	}
	for (int i = 0; i < Exp.length(); i++)
	{
		if(Exp[i] == '~' && Exp[i + 1] == '~')
		{
			Exp.erase(i, 2);
			i = i - 1;
		}
	}
	for (int i = 0; i < VarietyChart.size(); i++)
	{
		if (i != 0)
		{
			if (VarietyChart[i] - VarietyChart[i - 1] != 1)
			{
				cout << "������ı��ʽ��������������:" << endl;
				return FALSE;
			}
		}
	}
	for (int i = 0; i < Exp.length(); i++)
	{
		if (i != 0)
		{
			if ((isOperateNum(Exp[i]) && isOperateNum(Exp[i - 1])) || (isParenthese(Exp[i]) && isParenthese(Exp[i - 1])))
			{
				cout << "������ı��ʽ��������������:" << endl;
				return FALSE;
			}
			if (isOperateSign(Exp[i]) && isOperateSign(Exp[i - 1]))
			{
				bool cond1 = (Exp[i - 1] == '~' && (Exp[i] == '('||Exp[i]=='~'));
				bool cond2 = (Exp[i - 1] == '&' || Exp[i - 1] == '|') && (Exp[i] == '~' || Exp[i] == '(');
				bool cond3 = (Exp[i - 1] == '(' && (Exp[i] == '~'||Exp[i]=='('));
				bool cond4 = (Exp[i - 1] == ')' && (Exp[i] == ')') || Exp[i] == '&' || Exp[i] == '|');
				if (!(cond1 || cond2 || cond3||cond4))
				{
					cout<< "������ı��ʽ��������������:" << endl;
					return FALSE;
				}
			}
		}
		if (!isOperateNum(Exp[i])&&!isOperateSign(Exp[i]))
		{
			cout << "������ı��ʽ��������������:" << endl;
			return FALSE;
		}
		if (Exp[i] == ')' && LeftParentheseNum == 0 && RightParentheseNum == 0)
		{
			cout << "������ı��ʽ��������������:" << endl;
			return FALSE;
		}
		if (Exp[i] == '(') LeftParentheseNum++;
		if (Exp[i] == ')') RightParentheseNum++;
	}
	if (LeftParentheseNum != RightParentheseNum)
	{
		cout << "������ı��ʽ��������������:" << endl;
		return FALSE;
	}
	VarietyChart.clear();
}

void ShowUserInterface()
{
	cout << "��ӭʹ������ʽ�б���" << endl;
	cout << "��ע��:" << endl;
	cout << "��������ʹ�ô�д��ĸ��A,B,C������˳������ʹ�ã���������ĳһ��ĸ" << endl;
	cout << "����Ϊ����ʾ��:" << endl;
	cout << "A&B|D" << endl;
	cout << "&��ʾ�롢|��ʾ��~��ʾ�ǣ���������Ż�ʹ��0��1" << endl;
	cout << "���ڣ���������Ҫ�жϵ��߼����ʽ" << endl;
}

char ComparePriority(char C1, char C2)
{
	char Res = '0';
	switch (C1)
	{
		case '|':switch (C2)
				{
					case '|':Res = '>'; break;
					case '&':Res = '<'; break;
					case '~':Res = '<'; break;
					case '(':Res = '<'; break;
					case ')':Res = '>'; break;
					case '@':Res = '>'; break;
				}break;
		case '&':switch (C2)
				{
					case '|':Res = '>'; break;
					case '&':Res = '>'; break;
					case '~':Res = '<'; break;
					case '(':Res = '<'; break;
					case ')':Res = '>'; break;
					case '@':Res = '>'; break;
				}break;
		case '~':switch (C2)
				{
					case '|':Res = '>'; break;
					case '&':Res = '>'; break;
					case '~':Res = '>'; break;
					case '(':Res = '<'; break;
					case ')':Res = '>'; break;
					case '@':Res = '>'; break;
				}break;
		case '(':switch (C2)
				{
					case '|':Res = '<'; break;
					case '&':Res = '<'; break;
					case '~':Res = '<'; break;
					case '(':Res = '<'; break;
					case ')':Res = '='; break;
				}break;
		case ')':switch (C2)
				{
					case '|':Res = '>'; break;
					case '&':Res = '>'; break;
					case '~':Res = '>'; break;
					case '(':Res = '>'; break;
					case ')':Res = '>'; break;
					case '@':Res = '>'; break;
				}break;
		case '@':switch (C2)
				{
					case '|':Res = '<'; break;
					case '&':Res = '<'; break;
					case '~':Res = '<'; break;
					case '(':Res = '<'; break;
					case '@':Res = '='; break;
				}break;
	}
	return Res;
}

int JudgePatern(BiTree& T, int NumOfVariety)
{
	int OneCount = 0;
	int ZeroCount = 0;
	int* res = (int*)malloc((int)pow(2, NumOfVariety) * sizeof(int));
	for (int i = 0; i < (int)pow(2, NumOfVariety); i++)
	{
		AssignValue(T, i, NumOfVariety);
		res[i] = GetTreeValue(T);
	}
	for (int i = 0; i < (int)pow(2, NumOfVariety); i++)
	{
		if (res[i] == 1) OneCount++;
		if (res[i] == 0) ZeroCount++;
	}
	if (ZeroCount == 0) return 1;
	if (OneCount == 0) return -1;
	return OK;
}

int GetNumberOfVariety(string ExpressionFormulation)
{

	int count = 0;
	int Alphabalet[1000];
	for (int i = 0; i < ExpressionFormulation.length(); i++)
	{
		if (ExpressionFormulation[i] <= 'Z' && ExpressionFormulation[i] >= 'A')
			VarietyChart.push_back(ExpressionFormulation[i]);
			Alphabalet[ExpressionFormulation[i]] = -1;
	}
	for (int i = 0; i < 1000; i++)
	{
		if (Alphabalet[i] == -1) count++;
	}
	sort(VarietyChart.begin(), VarietyChart.end());
	it = unique(VarietyChart.begin(), VarietyChart.end());
	VarietyChart.erase(it, VarietyChart.end());
	return count;
}

int CreateLogisticBinaryTree(BiTree& T, stack<BiTree>& ODS, stack<BiTree>& OPS, string ExpForm)//ODS������ջ OPS������ջ
{
	BiTree BT1=NULL;
	InitBTNode(BT1);
	BT1->Value = 0;
	BT1->data = '@';//�����ڱ����ã���־ջ�������
	ODS.push(BT1);
	int LengthOfExpForm = ExpForm.length();
	int index = 0;
	char CurrentChar = ExpForm[index];
	while (!(CurrentChar == '@' && ODS.top()->data == '@'))
	{
		CurrentChar = ExpForm[index];
		if (index >= LengthOfExpForm) CurrentChar = '@';
		BiTree Temp;
		InitBTNode(Temp);
		Temp->data = CurrentChar;
		Temp->Value = 0;
		if (isOperateNum(CurrentChar))
		{
			OPS.push(Temp);
			index++;
			continue;
		}
		else//�����һ���ַ��ǲ��������Ƚϸ��ַ��������վODS�����ַ����ȼ���
		{
			char PriorRes = ComparePriority(ODS.top()->data, CurrentChar);
			if (PriorRes == '<')
			{
				ODS.push(Temp);
				index++; continue;
			}
			if (PriorRes == '=')
			{
				if (CurrentChar != '@')
				{
					ODS.pop();
					index++;
					continue;
				}
				else continue;
			}
			if (PriorRes == '>')
			{
				char TopOD = ODS.top()->data;
				BiTree OD, OP;
				OD = ODS.top(); OP = OPS.top();
				ODS.pop(); OPS.pop();
				OD->rchild = OP;
				if (TopOD != '~')
				{
					BiTree RcNode;
					RcNode = OPS.top();
					OPS.pop();
					OD->lchild = RcNode;
					OPS.push(OD);
				}
				else OPS.push(OD);
			}
		}
	}
	T = OPS.top();
	return OK;
}

int main()
{
	ShowUserInterface();
	string ExpressionFormulation;
	do 
	{ 
		cin >> ExpressionFormulation; 
		GetNumberOfVariety(ExpressionFormulation);
	} while (!isLegal(ExpressionFormulation));
	int NumOfVariety = GetNumberOfVariety(ExpressionFormulation);
	CreateLogisticBinaryTree(T,ODS,OPS,ExpressionFormulation);
	int ValSituation=JudgePatern(T,NumOfVariety);
	if (ValSituation == -1) cout << "��ʽΪì��ʽ" << endl;
	if (ValSituation == 0) cout << "��ʽΪ������ʽ" << endl;
	if (ValSituation == 1) cout << "��ʽΪ����ʽ" << endl;
	system("pause");
	return 0;
}