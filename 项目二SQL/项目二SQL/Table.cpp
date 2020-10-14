#include "Table.h"
#include<iostream>
#include"DoFile.h"
#include<cstdio>
using namespace std;
int DataCompare(DataNode a, DataNode b, int TheColumnId[],int ChosenColumnNum)
{
	for (int index = 0; index < ChosenColumnNum; index++)
	{
		if (strcmp(a.data[TheColumnId[index]], b.data[TheColumnId[index]]) != 0)
			return strcmp(a.data[TheColumnId[index]], b.data[TheColumnId[index]]);
	}
	return 0;
}
Table::Table()
{
	TableHead = NULL;
	DoFile dofile;
	TableHead = dofile.TableListOutFile();
}
void Table::ShowTable()
{
	int TableNum = 0;
	TableNode *x = TableHead;
	while (x != NULL)
	{
		TableNum++;
		x = x->next;
	}
	cout << "total:" << TableNum << endl;
	x = TableHead;
	for (int i = 0; i < TableNum; i++)
	{
		int IdNum = 0;
		DataNode *y = x->ColumnHead;
		while (y != NULL)
		{
			y = y->next;
			IdNum++;
		}
		cout << "\t" << x->TableName << ":(" << x->ColumnNum << "," << IdNum << ")";
		cout << "[";
		int q;
		for (q = 0; q < x->ColumnNum - 1; q++)
			cout << x->ColumnHeadName[q] << ",";
		cout << x->ColumnHeadName[q] << "]" << endl;
		x = x->next;
	}
}
void Table::CreateTable(char TheOrder[])
{
	int i = 0;
	while ((TheOrder[i] != 'T'||TheOrder[i + 1] != 'O')&&TheOrder[i+1] != '\0')
		i++;
	if (TheOrder[i]== 'T'&&TheOrder[i+1]=='O')
	{
		TableNode *x = new TableNode;
		x->next = NULL;
		int i;
		for (i = 13; TheOrder[i] != ' '; i++)
		{
			x->TableName[i - 13] = TheOrder[i];
		}
		x->TableName[i - 13] = '\0';
		while (TheOrder[i] != '(')
			i++;
		for (int ColumnNum = 0; TheOrder[i] != ')'; )
		{
			i++;
			int index = 0;
			while (TheOrder[i] != ','&&TheOrder[i] != ')')
			{
				x->ColumnHeadName[ColumnNum][index] = TheOrder[i];
				x->ColumnHeadName[ColumnNum][index + 1] = '\0';
				index++;
				i++;
			}
			ColumnNum++;
			x->ColumnNum = ColumnNum;
		}
		if (TableHead != NULL)
		{
			TableNode *y = TableHead;
			while (y->next != NULL)
			{
				y = y->next;
			}
			y->next = x;
		}
		else
		{
			TableHead = x;
		}
		DoFile dofile;
		dofile.TableListInFile(TableHead);
		x->ColumnHead = NULL;
		dofile.OneTableInFile(x);
		cout << "ID";
		for (int index = 0; index < x->ColumnNum; index++)
		{
			cout.width(10);
			cout << x->ColumnHeadName[index] << " ";
		}
		cout << endl;
	}
	else
	{
		TableNode *x = new TableNode;
		x->next = NULL;
		int i;
		for (i = 13; TheOrder[i] != ' '; i++)
		{
			x->TableName[i - 13] = TheOrder[i];
		}
		x->TableName[i - 13] = '\0';
		DoFile dofile;
		x=dofile.OneTableOutFile(x->TableName);
		if (TableHead!= NULL)
		{
			TableNode *y = TableHead;
			while (y->next != NULL)
			{
				y = y->next;
			}
			y->next =x;
		}
		else
		{
			TableHead = x;
		}
		dofile.TableListInFile(TableHead);
		cout << "ID";
		for (int index = 0; index < x->ColumnNum; index++)
		{
			cout.width(10);
			cout << x->ColumnHeadName[index] << " ";
		}
		cout << endl;
	}
}
void Table::DeleteTable(char TheOrder[])
{
	if (TheOrder[17] != '\0')
	{
		char DeleTableName[50];
		int i;
		for (i = 12; TheOrder[i] != ' '; i++)
			DeleTableName[i - 12] = TheOrder[i];
		DeleTableName[i - 12] = '\0';
		i++;
		while (TheOrder[i] != ' ')
			i++;
		i++;
		char SomeColumnName[50];
		for (int index = 0; TheOrder[i] != ' '; i++)
		{
			SomeColumnName[index] = TheOrder[i];
			SomeColumnName[index+1] = '\0';
			index++;
		}
		i++;
		if (TheOrder[i] == '=')//识别WHERE 的=符号
		{
			i += 2;
			char SomeData[50];
			for (int index = 0; TheOrder[i] != '\0'; i++)
			{
				SomeData[index] = TheOrder[i];
				SomeData[index+1] = '\0';
				index++;
			}
			TableNode* x = TableHead;
			for (; x != NULL&&strcmp(x->TableName, DeleTableName) != 0; x = x->next)
				;
			if (x != NULL)
			{
				int TheColumnNum = 0;
				while (strcmp(x->ColumnHeadName[TheColumnNum], SomeColumnName) != 0 && TheColumnNum < x->ColumnNum)
				{
					TheColumnNum++;
				}
				if (TheColumnNum < x->ColumnNum)
				{
					DataNode*index = x->ColumnHead;
					DataNode*bedex = NULL;
					for (; index != NULL; )
					{
						if (strcmp(index->data[TheColumnNum], SomeData) == 0)
						{
							if (bedex == NULL)
							{
								x->ColumnHead = index->next;
								delete index;
								index = x->ColumnHead;
							}
							else
							{
								bedex->next = index->next;
								delete index;
								index = bedex->next;
							}
						}
						else
						{
							bedex = index;
							index = index->next;
						}
					}
					DoFile dofile;
					dofile.OneTableInFile(x);
					char SelectOrder[40] = "SElECT * FROM ";
					strcat_s(SelectOrder, x->TableName);
					SelectTable(SelectOrder);
				}
			}
		}

	}
	else
	{
		char DeleTableName[50];
		int i;
		for (i = 14; TheOrder[i] != ' '; i++)
			DeleTableName[i - 14] = TheOrder[i];
		DeleTableName[i - 14] = '\0';
		i++;
		TableNode* x = TableHead;
		for (; x != NULL&&strcmp(x->TableName, DeleTableName) != 0; x = x->next)
			;
		if (x != NULL)
		{
			DataNode *bedex =x->ColumnHead;
			DataNode *index = bedex->next;
			while (index != NULL)
			{
				delete bedex;
				bedex = index;
				index = index->next;
			}
			delete bedex;
			DoFile dofile;
			dofile.OneTableInFile(x);
			char SelectOrder[40] = "SElECT * FROM ";
			strcat_s(SelectOrder, x->TableName);
			SelectTable(SelectOrder);
		}
	}
}
void Table::DropTable(char TheOrder[])
{
	char DropTableName[50];
	int i;
	for (i = 11; TheOrder[i] != '\0'; i++)
		DropTableName[i - 11] = TheOrder[i];
	DropTableName[i - 11] = '\0';
	TableNode* x;
	TableNode* y = NULL;
	for (x = TableHead; strcmp(x->TableName, DropTableName) != 0; x = x->next)
	{
		y = x;
	}
	if (y == NULL)
	{
		TableHead = TableHead->next;
		delete x;
	}
	else
	{
		y->next = x->next;
		delete x;
	}
	DoFile dofile;
	dofile.TableListInFile(TableHead);
	char DropFileName[40];
	char TheAddress[40] = "d:\\";
	strcpy_s(DropFileName, DropTableName);
	DropFileName[0] += 'a' - 'A';
	strcat_s(DropFileName, ".txt");
	strcat_s(TheAddress, DropFileName);
	remove(TheAddress);
}
void Table::InsertTable(char TheOrder[])
{
	char InsertTableName[50];
	int i;
	for (i = 12; TheOrder[i] != ' '; i++)
		InsertTableName[i - 12] = TheOrder[i];
	InsertTableName[i - 12] = '\0';
	i++;
	if (TheOrder[i] == 'V')
	{
		i += 8;
		TableNode *x = TableHead;
		while (strcmp(x->TableName, InsertTableName) != 0)
			x = x->next;
		DataNode *InsertData = new DataNode;
		InsertData->next = NULL;
		for (int index = 0; index < x->ColumnNum; index++)
		{
			int j = 0;
			while (TheOrder[i] != ','&&TheOrder[i] != ')')
			{
				InsertData->data[index][j] = TheOrder[i];
				InsertData->data[index][j + 1] = '\0';
				i++;
				j++;
			}
			if (TheOrder[i] == ',')
				i++;
		}
		DataNode* y = x->ColumnHead;
		if (y == NULL)
		{
			x->ColumnHead = InsertData;
		}
		else
		{
			while (y->next != NULL)
				y = y->next;
			y->next = InsertData;
		}
		DoFile dofile;
		dofile.OneTableInFile(x);
		char SelectOrder[40] = "SElECT * FROM ";
		strcat_s(SelectOrder, x->TableName);
		SelectTable(SelectOrder);
	}
	else
	{
		TableNode *x = TableHead;
		while (strcmp(x->TableName, InsertTableName) != 0)
			x = x->next;
		DataNode *InsertData = new DataNode;
		InsertData->next = NULL;
		char InsertColumn[10][40];
		for (int index; TheOrder[i] != ')'; )
		{
			int j = 0;
			i++;
			index = 0;
			while (TheOrder[i] != ','&&TheOrder[i] != ')')
			{
				InsertColumn[index][j]=TheOrder[i];
				j++;
				i++;
			}
			InsertColumn[index][j] = '\0';
			index++;
		}
		i += 10;//移动到左括号后一个
		for (int index = 0; index < x->ColumnNum; index++)//每个InsertData的每个列都要被填写，缺省的填'\0'即可
		{
			if (strcmp(x->ColumnHeadName[index], InsertColumn[index]) == 0)
			{
				for (int j = 0; TheOrder[i] != ','&&TheOrder[i] != ')';)
				{
					InsertData->data[index][j] = TheOrder[i];
					j++;
					i++;
				}
			}
			else
				strcpy_s(InsertData->data[index], "\0");
		}
		DataNode* y = x->ColumnHead;
		if (y == NULL)
		{
			x->ColumnHead = InsertData;
		}
		else
		{
			while (y->next != NULL)
				y = y->next;
			y->next = InsertData;
		}
		DoFile dofile;
		dofile.OneTableInFile(x);
		char SelectOrder[40] = "SElECT * FROM ";
		strcat_s(SelectOrder, x->TableName);
		SelectTable(SelectOrder);
	}
}
void Table::UpdateTable(char TheOrder[])
{
	int i;
	for (i= 0; TheOrder[i] != 'W' || TheOrder[i + 1] != 'H' || TheOrder[i + 2] != 'E'||TheOrder[i + 3] != 'R' || TheOrder[i + 4] != 'E' || TheOrder[i + 4] == '\0'; i++)
		;
	if (TheOrder[i+4] == '\0')
	{
		i = 7;
		char UpdataTableName[40];
		for (int index = 0; TheOrder[i] != ' '; index++)
		{
			UpdataTableName[index] = TheOrder[i];
			UpdataTableName[index + 1] = '\0';
			i++;
		}
		i+=3;
		char UpdataColumnName[10][40];
		char UpdataValue[10][40];
		int UpdataColumnNum = 0;
		for (; TheOrder[i] != '\0';)
		{
			i+=2;
			int j = 0;
			while (TheOrder[i] != ' ')
			{
				UpdataColumnName[UpdataColumnNum][j] = TheOrder[i];
				i++;
				j++;
			}
			UpdataColumnName[UpdataColumnNum][j] = '\0';
			j = 0;
			i += 3;
			while (TheOrder[i] != ','&&TheOrder[i] != '\0')
			{
				UpdataValue[UpdataColumnNum][j] = TheOrder[i];
				i++;
				j++;
			}
			UpdataColumnName[UpdataColumnNum][j] = '\0';
			UpdataColumnNum++;
		}
		TableNode *x = TableHead;
		while (strcmp(x->TableName, UpdataTableName) != 0)
			x = x->next;
		DataNode *y = x->ColumnHead;
		while (y != NULL)//循环每一行
		{
			for (int index = 0; index < UpdataColumnNum; index++)//循环每个要更新的列
			{
				int q;
				for (q = 0; strcmp(x->ColumnHeadName[q], UpdataColumnName[index]) != 0; q++)//在已有列中一一寻找匹配的列
					;
				strcpy_s(y->data[q], UpdataValue[index]);//更新！
			}
			y = y->next;
		}
		DoFile dofile;
		dofile.OneTableInFile(x);
	}
	else
	{
		i = 7;
		char UpdataTableName[40];
		for (int index = 0; TheOrder[i] != ' '; index++)
		{
			UpdataTableName[index] = TheOrder[i];
			UpdataTableName[index + 1] = '\0';
			i++;
		}
		i+=3;
		char UpdataColumnName[10][40];
		char UpdataValue[10][40];
		int UpdataColumnNum = 0;
		for (; TheOrder[i] != ' ';)
		{
			i += 2;
			int j = 0;
			while (TheOrder[i] != ' ')
			{
				UpdataColumnName[UpdataColumnNum][j] = TheOrder[i];
				i++;
				j++;
			}
			UpdataColumnName[UpdataColumnNum][j] = '\0';
			j = 0;
			i += 3;
			while (TheOrder[i] != ','&&TheOrder[i] != ' ')
			{
				UpdataValue[UpdataColumnNum][j] = TheOrder[i];
				UpdataValue[UpdataColumnNum][j+1] = '\0';
				i++;
				j++;
			}
			UpdataColumnNum++;
		}
		i += 7;
		char AColumn[30];
		char TheValue[30];
		int AColumnNum = 0;
		for (int w = 0; TheOrder[i] != ' '; w++)
		{
			AColumn[w] = TheOrder[i];
			AColumn[w + 1] = '\0';
			i++;
		}
		i += 3;
		for (int w = 0; TheOrder[i] != '\0'; w++)
		{
			TheValue[w] = TheOrder[i];
			TheValue[w + 1] = '\0';
			i++;
		}
		TableNode *x = TableHead;
		while (strcmp(x->TableName, UpdataTableName) != 0)
			x = x->next;
		for (; strcmp(x->ColumnHeadName[AColumnNum], AColumn) != 0; AColumnNum++)
			;
		DataNode *y = x->ColumnHead;
		while (y != NULL)
		{
			while (y != NULL&&strcmp(y->data[AColumnNum], TheValue) != 0)
				y = y->next;
			if(y!=NULL)
			for (int index = 0; index < UpdataColumnNum; index++)//循环每个要更新的列
			{
				int q;
				for (q = 0; strcmp(x->ColumnHeadName[q], UpdataColumnName[index]) != 0; q++)//在已有列中一一寻找匹配的列
					;
				strcpy_s(y->data[q], UpdataValue[index]);//更新！
			}
			if(y!=NULL)
			y = y->next;
		}
		DoFile dofile;
		dofile.OneTableInFile(x);
	}
}
void Table::SelectTable(char TheOrder[])
{
	cout.setf(std::ios::left);
	if (TheOrder[7] == 'D')//DISTINCT
	{
		char TheColumn[10][30];
		char TheTable[30];
		int SelectColumnNum = 0;
		int i = 15;
		while (TheOrder[i] != ' ' || TheOrder[i + 1] != 'F' || TheOrder[i + 2] != 'R' || TheOrder[i + 3] != 'O')
		{
			i++;
			int j = 0;
			while (TheOrder[i] != ','&&TheOrder[i] != ' ')
			{
				TheColumn[SelectColumnNum][j] = TheOrder[i];
				i++;
				j++;
			}
			TheColumn[SelectColumnNum][j] = '\0';
			SelectColumnNum++;
		}
		i += 6;
		int e = 0;
		while (TheOrder[i] != '\0')
		{
			TheTable[e] = TheOrder[i];
			TheTable[e + 1] = '\0';
			e++;
			i++;
		}
		TheTable[e] = '\0';
		TableNode *x = TableHead;
		while (strcmp(x->TableName, TheTable) != 0)
			x = x->next;
		cout.width(20);
		for (int in = 0; in < SelectColumnNum; in++)//每个选择的列进行distinct输出
		{
			//先找到每个列的列号是多少
			int ColumnId = 0;
			while (strcmp(x->ColumnHeadName[ColumnId], TheColumn[in]) != 0)
				ColumnId++;
			if (in == 0)
			{
				cout << endl;
				cout.width(10);
				cout << "ID";
				cout << x->ColumnHeadName[ColumnId] << " " << endl;
			}
			DataNode* y = x->ColumnHead;
			int id = 0;
			int yid = 0;
			while (y != NULL)
			{
				int ifdistinct = 1;
				DataNode* z;
				int zid = 0;
				for (z = x->ColumnHead; zid < yid&&ifdistinct == 1; z = z->next)
				{
					if (strcmp(z->data[ColumnId], y->data[ColumnId]) == 0)
						ifdistinct = 0;
					zid++;
				}
				if (ifdistinct)
				{
					cout.width(10);
					cout << id << y->data[ColumnId] << " " << endl;
					id++;
				}
				yid++;
				y = y->next;
			}
		}

	}
	else if (TheOrder[7] == '*')//全体操作
	{
		int i = 14;
		while (TheOrder[i] != ' '&&TheOrder[i] != '\0')
		{
			i++;
		}
		if (TheOrder[i] == ' ')//升降序或WHERE或WHERE TO TXT
		{
			i++;
			if (TheOrder[i] == 'W')//WHERE或WHERE TO TXT
			{
				while ((TheOrder[i] != 'T' || TheOrder[i + 1] != 'O') && TheOrder[i] != '\0')
					i++;
				if (TheOrder[i] == '\0')//WHERE
				{
					i = 14;
					char TheTableName[30];
					int j = 0;
					for (; TheOrder[i] != ' '; i++)
					{
						TheTableName[j] = TheOrder[i];
						TheTableName[j+1] = '\0';
						j++;
					}
					i += 7;
					char TheColumn[30];
					j = 0;
					for (; TheOrder[i] != ' '; i++)
					{
						TheColumn[j] = TheOrder[i];
						TheColumn[j+1] = '\0';
						j++;
					}
					char TheValue[30];
					i += 3;
					j = 0;
					for (; TheOrder[i] != '\0'; i++)
					{
						TheValue[j] = TheOrder[i];
						TheValue[j+1] ='\0';
						j++;
					}
					TableNode *x = TableHead;
					while (strcmp(x->TableName, TheTableName) != 0)
						x = x->next;
					//找到了对应的TABLE
					cout.width(10);
					cout << "ID";
					for (int index = 0; index < x->ColumnNum; index++)
					{
						cout.width(10);
						cout << x->ColumnHeadName[index] << " ";
					}
					cout << endl;
					int TheColumnNum = 0;
					for (int index = 0; index < x->ColumnNum; index++)
					{
						if (strcmp(x->ColumnHeadName[index], TheColumn) == 0)
						{
							TheColumnNum = index;
							index = x->ColumnNum;
						}
					}
					DataNode *y = x->ColumnHead;
					for (int id = 0; y != NULL; y = y->next)
					{
						if (strcmp(y->data[TheColumnNum], TheValue) == 0)
						{
							cout.width(10);
							cout << id;
							id++;
							for (int index = 0; index < x->ColumnNum; index++)
							{
								cout.width(10);
								cout << y->data[index] << " ";
							}
							cout << endl;
						}
					}

				}
				else//WHERE TO TXT
				{
					TableNode *FileTable = new TableNode;
					i = 13;
					char TheTableName[30];
					int j = 0;
					for (; TheOrder[i] != ' '; i++)
					{
						TheTableName[j] = TheOrder[i];
						j++;
					}
					TheTableName[j] = '\0';
					strcpy_s(FileTable->TableName, TheTableName);
					i += 7;
					char TheColumn[30];
					j = 0;
					for (; TheOrder[i] != ' '; i++)
					{
						TheColumn[j] = TheOrder[i];
						j++;
					}
					TheColumn[j] = '\0';
					char TheValue[30];
					i += 3;
					j = 0;
					for (; TheOrder[i] != ' '; i++)
					{
						TheValue[j] = TheOrder[i];
						j++;
					}
					TheValue[j] = '\0';
					i += 3;
					char FileName[30];
					j = 0;
					while (TheOrder[i] != '\0')
					{
						FileName[j] = TheOrder[i];
						i++;
						j++;
					}
					FileName[j] = '\0';
					TableNode *x = TableHead;
					while (strcmp(x->TableName, TheTableName) != 0)
						x = x->next;
					//找到了对应的TABLE
					FileTable->ColumnNum = x->ColumnNum;
					for (int index = 0; index < x->ColumnNum; index++)
						strcpy_s(FileTable->ColumnHeadName[index], x->ColumnHeadName[index]);
					cout.width(10);
					cout << "ID";
					for (int index = 0; index < x->ColumnNum; index++)
					{
						cout.width(10);
						cout << x->ColumnHeadName[index] << " ";
					}
					cout << endl;
					int TheColumnNum = 0;
					for (int index = 0; index < x->ColumnNum; index++)
					{
						if (strcmp(x->ColumnHeadName[index], TheColumn) == 0)
						{
							TheColumnNum = index;
							index = x->ColumnNum;
						}
					}
					DataNode *y = x->ColumnHead;
					for (int id = 0; y != NULL; y = y->next)
					{
						if (strcmp(y->data[TheColumnNum], TheValue) == 0)
						{
							DataNode *ANode = new DataNode;
							ANode->next = NULL;
							cout.width(10);
							cout << id;
							id++;
							for (int index = 0; index < x->ColumnNum; index++)
							{
								cout.width(10);
								cout << y->data[index] << " ";
								strcpy_s(ANode->data[index], y->data[index]);
							}
							cout << endl;
							if (FileTable->ColumnHead == NULL)
								FileTable->ColumnHead = ANode;
							else
							{
								DataNode* p = FileTable->ColumnHead;
								while (p->next != NULL)
									p = p->next;
								p->next = ANode;
							}
						}
					}
					char address[40]="d:\\";
					strcat_s(address, FileName);
					DoFile dofile;
					dofile.OneTableInTxt(FileTable,address);
				}
			}
			else//升降序
			{
				TableNode * ATable = new TableNode;
				i = 14;
				int j = 0;
				while (TheOrder[i] != ' ')
				{
					ATable->TableName[j] = TheOrder[i];
					i++;
					j++;
				}
				ATable->TableName[j] = '\0';
				i += 10;
				char AColumnName[10][30];
				int k = 0;
				while (TheOrder[i] != ' ')
				{
					j = 0;
					while (TheOrder[i] != ' '&&TheOrder[i] != ',')
					{
						AColumnName[k][j] = TheOrder[i];
						i++;
						j++;
					}
					AColumnName[k][j] = '\0';
					k++;
				}
				TableNode *x = TableHead;
				while (strcmp(x->TableName, ATable->TableName) != 0)
					x = x->next;
				ATable = x;
				int TheColumnId[10];
				for (int gg = 0; gg < k; gg++)
					for (int index = 0; index < x->ColumnNum; index++)
					{
						if (strcmp(x->ColumnHeadName[index], AColumnName[gg]) == 0)
						{
							TheColumnId[gg] = index;
						}
					}
				//对ATable 进行升序排序   标记考虑顺序的列数是ColumnId、一个有k个列被标记
				DataNode AscOrderData[200];
				int IdNum = 0;
				int BondId[300];
				DataNode *y = ATable->ColumnHead;
				while (y != NULL)
				{
					AscOrderData[IdNum] = *y;
					IdNum++;
					y = y->next;
					BondId[IdNum] = IdNum;
				}
				//对AscOrderData的IdNum行成员进行DataCompare,已知int TheColumnId[]和k作为第三个第四个形参
				for (int ci = 0; ci < IdNum - 1; ci++)
				{
					int max = 0;
					for (int cj = 1; cj < IdNum - 1 - ci; cj++)
					{
						if (DataCompare(AscOrderData[cj], AscOrderData[max], TheColumnId, k) > 0)
							max = cj;
					}
					DataNode SubData;
					SubData = AscOrderData[max];
					AscOrderData[max] = AscOrderData[IdNum - 1 - ci];
					AscOrderData[IdNum - 1 - ci] = SubData;
					int SubInt;
					SubInt = BondId[max];
					BondId[max] = BondId[IdNum - 1 - ci];
					BondId[IdNum - 1 - ci] = SubInt;
				}
				while (TheOrder[i] != '\0')
					i++;
				i -= 3;
				if (TheOrder[i] == 'A')//ASC
				{
					cout.width(10);
					cout << "ID";
					for (int index = 0; index < x->ColumnNum; index++)
					{
						cout.width(10);
						cout << x->ColumnHeadName[index] << " ";
					}
					cout << endl;
					int Id = 0;
					for (int ii = 0; ii < IdNum; ii++)
					{
						y = x->ColumnHead;
						for (int index = 0; index < BondId[ii]; index++)
							y = y->next;
						cout.width(10);
						cout << Id;
						Id++;
						for (int index = 0; index < x->ColumnNum; index++)
						{
							cout.width(10);
							cout << y->data[index] << " ";
						}
						cout << endl;
					}
				}
				else//DESC
				{
					cout.width(10);
					cout << "ID";
					for (int index = 0; index < x->ColumnNum; index++)
					{
						cout.width(10);
						cout << x->ColumnHeadName[index] << " ";
					}
					cout << endl;
					int Id = 0;
					for (int ii = IdNum - 1; ii >= 0; ii--)
					{
						y = x->ColumnHead;
						for (int index = 0; index < BondId[ii]; index++)
							y = y->next;
						cout.width(10);
						cout << Id;
						Id++;
						for (int index = 0; index < x->ColumnNum; index++)
						{
							cout.width(10);
							cout << y->data[index] << " ";
						}
						cout << endl;
					}
				}
			}
		}
		else//照常输出
		{
			char ChosenTableName[30];
			i = 14;
			int j = 0;
			while (TheOrder[i] != '\0')
			{
				ChosenTableName[j] = TheOrder[i];
				i++;
				j++;
			}
			ChosenTableName[j] = '\0';
			TableNode *x = TableHead;
			while (strcmp(x->TableName, ChosenTableName) != 0)
				x = x->next;
			cout.width(10);
			cout << "ID";
			for (int index = 0; index < x->ColumnNum; index++)
			{
				cout.width(10);
				cout << x->ColumnHeadName[index] << " ";
			}
			cout << endl;
			int id = 0;
			DataNode* u = x->ColumnHead;
			while (u != NULL)
			{
				cout.width(10);
				cout << id;
				id++;
				for (int index = 0; index < x->ColumnNum; index++)
				{
					cout.width(10);
					cout << u->data[index] << " ";
				}
				u = u->next;
				cout << endl;
			}
		}

	}
	else if (TheOrder[7] == 'M'&&TheOrder[8] == 'A')
	{
		int i = 11;
		char ColumnName[30];
		int j = 0;
		while (TheOrder[i] != ')')
		{
			ColumnName[j] = TheOrder[i];
			ColumnName[j + 1] = '\0';
			i++;
			j++;
		}
		i += 7;
		char tablename[30];
		j = 0;
		while (TheOrder[i] != '\0')
		{
			tablename[j] = TheOrder[i];
			tablename[j + 1] = '\0';
			i++;
			j++;
		}
		TableNode *x = TableHead;
		while (strcmp(tablename, x->TableName) != 0)
			x = x->next;
		int ColumnId = 0;
		for (; strcmp(ColumnName, x->ColumnHeadName[ColumnId]) != 0; ColumnId++)
			;
		int max = 0;
		DataNode* y = x->ColumnHead->next;
		i = 1;;
		while (y != NULL)
		{
			DataNode* m = x->ColumnHead;
			for (int index = 0; index < max; index++)
				m = m->next;
			if (strcmp(m->data[ColumnId], y->data[ColumnId]) < 0)
				max = i;
				i++;
				y = y->next;
		}
		cout << "ID ";
		for (int index = 0; index < x->ColumnNum; index++)
		{
			cout.width(10);
			cout << x->ColumnHeadName[index] << " ";
		}
		cout << endl;
		cout << "0 ";
		y = x->ColumnHead;
		for (int j = 0; j < max; j++)
			y = y->next;
		for (int index = 0; index < x->ColumnNum; index++)
		{
			cout.width(10);
			cout << y->data[index] << " ";
		}
		cout << endl;
	}
	else if (TheOrder[7] == 'M'&&TheOrder[8] == 'I')
	{
		int i = 11;
		char ColumnName[30];
		int j = 0;
		while (TheOrder[i] != ')')
		{
			ColumnName[j] = TheOrder[i];
			ColumnName[j + 1] = '\0';
			i++;
			j++;
		}
		i += 7;
		char tablename[30];
		j = 0;
		while (TheOrder[i] != '\0')
		{
			tablename[j] = TheOrder[i];
			tablename[j + 1] = '\0';
			i++;
			j++;
		}
		TableNode *x = TableHead;
		while (strcmp(tablename, x->TableName) != 0)
			x = x->next;
		int ColumnId = 0;
		for (; strcmp(ColumnName, x->ColumnHeadName[ColumnId]) != 0; ColumnId++)
			;
		int min = 0;
		DataNode* y = x->ColumnHead->next;
		 i = 1;;
		while (y != NULL)
		{
			DataNode* m = x->ColumnHead;
			for (int index = 0; index < min; index++)
				m = m->next;
			if (strcmp(m->data[ColumnId], y->data[ColumnId])>0)
				min = i;
			i++;
			y = y->next;
		}
		cout << "ID ";
		for (int index = 0; index < x->ColumnNum; index++)
		{
			cout.width(10);
			cout << x->ColumnHeadName[index] << " ";
		}
		cout << endl;
		cout << "0 ";
		y = x->ColumnHead;
		for (int j = 0; j < min; j++)
			y = y->next;
		for (int index = 0; index < x->ColumnNum; index++)
		{
			cout.width(10);
			cout << y->data[index] << " ";
		}
		cout << endl;
	}
	else//部分列展示全体
	{
		char ChosenColumnName[10][30];
		char ChosenTableName[30];
		int i = 7;
		int ChosenColumnNum = 0;
		int ChosenColumnId[10];
		while (TheOrder[i] != ' ')
		{
			if (TheOrder[i] == ',')
				i++;
			int j = 0;
			while (TheOrder[i] != ' '&&TheOrder[i] != ',')
			{
				ChosenColumnName[ChosenColumnNum][j] = TheOrder[i];
				ChosenColumnName[ChosenColumnNum][j + 1] = '\0';
				i++;
				j++;
			}
			ChosenColumnNum++;
		}
		i += 6;
		int j = 0;
		while (TheOrder[i] != '\0'&&TheOrder[i] != ' ')
		{
			ChosenTableName[j] = TheOrder[i];
			ChosenTableName[j + 1] = '\0';
			j++;
			i++;
		}
		TableNode *x = TableHead;
		while (strcmp(x->TableName, ChosenTableName) != 0)
			x = x->next;
		for (int index = 0; index < ChosenColumnNum; index++)
		{
			for (int cc = 0; cc < x->ColumnNum; cc++)
			{
				if (strcmp(ChosenColumnName[index], x->ColumnHeadName[cc]) == 0)
				{
					ChosenColumnId[index] = cc;
					cc = x->ColumnNum;
				}
			}
		}
		if (TheOrder[i] == '\0')//照常输出
		{
			cout.width(10);
			cout << "ID";
			for (int index = 0; index < ChosenColumnNum; index++)
			{
				cout.width(10);
				cout << x->ColumnHeadName[ChosenColumnId[index]] << " ";
			}
			cout << endl;
			int id = 0;
			DataNode* u = x->ColumnHead;
			while (u != NULL)
			{
				cout.width(10);
				cout << id;
				id++;
				for (int index = 0; index < ChosenColumnNum; index++)
				{
					cout.width(10);
					cout << u->data[ChosenColumnId[index]] << " ";
				}
				u = u->next;
				cout << endl;
			}
		}
		else//升降序或WHERE或WHERE TO TXT
		{
			i++;
			if (TheOrder[i] == 'W')//WHERE或WHERE TO TXT
			{
				while ((TheOrder[i] != 'T' || TheOrder[i + 1] != 'O') && TheOrder[i] != '\0')
					i++;
				if (TheOrder[i] == '\0')//WHERE
				{
					for (int i = 0; TheOrder[i] != 'W' || TheOrder[i + 1] != 'H' || TheOrder[i + 2] != 'E'; i++)
						;
					i += 6;
					char TheColumn[30];
					j = 0;
					for (; TheOrder[i] != ' '; i++)
					{
						TheColumn[j] = TheOrder[i];
						TheColumn[j + 1] = '\0';
						j++;
					}
					char TheValue[30];
					i += 3;
					j = 0;
					for (; TheOrder[i] != '\0'; i++)
					{
						TheValue[j] = TheOrder[i];
						TheValue[j + 1] = '\0';
						j++;
					}
					//找到了对应的TABLE
					cout.width(10);
					cout << "ID";
					for (int index = 0; index < ChosenColumnNum; index++)
					{
						cout.width(10);
						cout << x->ColumnHeadName[ChosenColumnId[index]] << " ";
					}
					cout << endl;
					int TheColumnNum = 0;
					for (int index = 0; index < x->ColumnNum; index++)
					{
						if (strcmp(x->ColumnHeadName[index], TheColumn) == 0)
						{
							TheColumnNum = index;
							index = x->ColumnNum;
						}
					}
					DataNode *y = x->ColumnHead;
					for (int id = 0; y != NULL; y = y->next)
					{
						if (strcmp(y->data[TheColumnNum], TheValue) == 0)
						{
							cout.width(10);
							cout << id;
							id++;
							for (int index = 0; index < ChosenColumnNum; index++)
							{
								cout.width(10);
								cout << y->data[ChosenColumnId[index]] << " ";
							}
							cout << endl;
						}
					}
				}
				else//WHERE TO TXT
				{
					TableNode *FileTable = new TableNode;
					strcpy_s(FileTable->TableName, ChosenTableName);
					for (int i = 0; TheOrder[i] != 'W' || TheOrder[i + 1] != 'H' || TheOrder[i + 2] != 'E'; i++)
						;
					i += 6;
					char TheColumn[30];
					j = 0;
					for (; TheOrder[i] != ' '; i++)
					{
						TheColumn[j] = TheOrder[i];
						TheColumn[j + 1] = '\0';
						j++;
					}
					char TheValue[30];
					i += 3;
					j = 0;
					for (; TheOrder[i] != ' '; i++)
					{
						TheValue[j] = TheOrder[i];
						TheValue[j + 1] = '\0';
						j++;
					}
					i += 4;
					char FileName[30];
					j = 0;
					while (TheOrder[i] != '\0')
					{
						FileName[j] = TheOrder[i];
						FileName[j + 1] = '\0';
						i++;
						j++;
					}
					//找到了对应的TABLE
					FileTable->ColumnNum = ChosenColumnNum;
					for (int index = 0; index < ChosenColumnNum; index++)
						strcpy_s(FileTable->ColumnHeadName[index], x->ColumnHeadName[ChosenColumnId[index]]);
					cout.width(10);
					cout << "ID";
					for (int index = 0; index < ChosenColumnNum; index++)
					{
						cout.width(10);
						cout << x->ColumnHeadName[ChosenColumnId[index]] << " ";
					}
					cout << endl;
					int TheColumnNum = 0;
					for (int index = 0; index < x->ColumnNum; index++)
					{
						if (strcmp(x->ColumnHeadName[index], TheColumn) == 0)
						{
							TheColumnNum = index;
							index = x->ColumnNum;
						}
					}
					DataNode *y = x->ColumnHead;
					for (int id = 0; y != NULL; y = y->next)
					{
						if (strcmp(y->data[TheColumnNum], TheValue) == 0)
						{
							DataNode *ANode = new DataNode;
							ANode->next = NULL;
							cout.width(10);
							cout << id;
							id++;
							for (int index = 0; index < ChosenColumnNum; index++)
							{
								cout.width(10);
								cout << y->data[ChosenColumnId[index]] << " ";
								strcpy_s(ANode->data[index], y->data[ChosenColumnId[index]]);
							}
							cout << endl;
							if (FileTable->ColumnHead == NULL)
								FileTable->ColumnHead = ANode;
							else
							{
								DataNode* p = FileTable->ColumnHead;
								while (p->next != NULL)
									p = p->next;
								p->next = ANode;
							}
						}
					}
					char address[40]="d:\\";
					strcat_s(address, FileName);
					DoFile dofile;
					dofile.OneTableInTxt(FileTable,address);
				}
			}
			else//升降序
			{
				while ((TheOrder[i] != 'T' || TheOrder[i + 1] != 'O') && TheOrder[i] != '\0')
					i++;
				if (TheOrder[i] == '\0')
				{
					TableNode * ATable = new TableNode;
					int j;
					char AColumnName[10][30];
					for (i = 0; TheOrder[i] != 'O' || TheOrder[i + 1] != 'R' || TheOrder[i + 2] != 'D' || TheOrder[i + 3] != 'E'; i++)
						;
					i += 9;
					int k = 0;
					while (TheOrder[i] != ' ')
					{
						j = 0;
						while (TheOrder[i] != ' '&&TheOrder[i] != ',')
						{
							AColumnName[k][j] = TheOrder[i];
							AColumnName[k][j + 1] = '\0';
							i++;
							j++;
						}
						k++;
						if (TheOrder[i] == ',')
							i++;
					}
					ATable = x;
					int TheColumnId[10];
					for (int gg = 0; gg < k; gg++)
						for (int index = 0; index < x->ColumnNum; index++)
						{
							if (strcmp(x->ColumnHeadName[index], AColumnName[gg]) == 0)
							{
								TheColumnId[gg] = index;
							}
						}
					//对ATable 进行升序排序   标记考虑顺序的列数是ColumnId、一个有k个列被标记,
					DataNode AscOrderData[200];
					int IdNum = 0;
					int BondId[300];
					DataNode *y = ATable->ColumnHead;
					while (y != NULL)
					{
						AscOrderData[IdNum] = *y;
						IdNum++;
						y = y->next;
						BondId[IdNum - 1] = IdNum;
					}
					//对AscOrderData的IdNum行成员进行DataCompare,已知int TheColumnId[]和k作为第三个第四个形参
					for (int ci = 0; ci < IdNum - 1; ci++)
					{
						int max = 0;
						for (int cj = 0; cj < IdNum - ci; cj++)
						{
							if (DataCompare(AscOrderData[cj], AscOrderData[max], TheColumnId, k) > 0)
								max = cj;
						}
						DataNode SubData;
						SubData = AscOrderData[max];
						AscOrderData[max] = AscOrderData[IdNum - 1 - ci];
						AscOrderData[IdNum - 1 - ci] = SubData;
						int SubInt;
						SubInt = BondId[max];
						BondId[max] = BondId[IdNum - 1 - ci];
						BondId[IdNum - 1 - ci] = SubInt;
					}
					while (TheOrder[i] != '\0')
						i++;
					i -= 3;
					if (TheOrder[i] == 'A')//ASC
					{
						cout.width(10);
						cout << "ID";
						for (int index = 0; index < ChosenColumnNum; index++)
						{
							cout.width(10);
							cout << x->ColumnHeadName[ChosenColumnId[index]] << " ";
						}
						cout << endl;
						int Id = 0;
						for (int ii = 0; ii < IdNum; ii++)
						{
							y = x->ColumnHead;
							for (int index = 0; index < BondId[ii] - 1; index++)
								y = y->next;
							cout.width(10);
							cout << Id;
							Id++;
							for (int index = 0; index < ChosenColumnNum; index++)
							{
								cout.width(10);
								cout << y->data[ChosenColumnId[index]] << " ";
							}
							cout << endl;
						}
					}
					else//DESC
					{
						cout.width(10);
						cout << "ID";
						for (int index = 0; index < ChosenColumnNum; index++)
						{
							cout.width(10);
							cout << x->ColumnHeadName[ChosenColumnId[index]] << " ";
						}
						cout << endl;
						int Id = 0;
						for (int ii = IdNum - 1; ii >= 0; ii--)
						{
							y = x->ColumnHead;
							for (int index = 0; index < BondId[ii] - 1; index++)
								y = y->next;
							cout.width(10);
							cout << Id;
							Id++;
							for (int index = 0; index < ChosenColumnNum; index++)
							{
								cout.width(10);
								cout << y->data[ChosenColumnId[index]] << " ";
							}
							cout << endl;
						}
					}
				}
				else
				{
					TableNode *FileTable = new TableNode;
					FileTable->ColumnHead = NULL;
					int j;
					strcpy_s(FileTable->TableName,ChosenTableName);
					i += 3;
					char FileName[30];
					j = 0;
					while (TheOrder[i] != '\0')
					{
						FileName[j] = TheOrder[i];
						FileName[j+1]='\0';
						i++;
						j++;
					}
					//找到了对应的TABLE
					FileTable->ColumnNum = ChosenColumnNum;
					for (int index = 0; index <ChosenColumnNum; index++)
						strcpy_s(FileTable->ColumnHeadName[index], x->ColumnHeadName[ChosenColumnId[index]]);
					cout.width(10);
					cout << "ID";
					for (int index = 0; index <ChosenColumnNum; index++)
					{
						cout.width(10);
						cout << x->ColumnHeadName[ChosenColumnId[index]] << " ";
					}
					cout << endl;
					DataNode *y = x->ColumnHead;
					for (int id = 0; y != NULL; y = y->next)
					{
	
							DataNode *ANode = new DataNode;
							ANode->next = NULL;
							cout.width(10);
							cout << id;
							id++;
							for (int index = 0; index <ChosenColumnNum; index++)
							{
								cout.width(10);
								cout << y->data[ChosenColumnId[index]] << " ";
								strcpy_s(ANode->data[index], y->data[ChosenColumnId[index]]);
							}
							cout << endl;
							if (FileTable->ColumnHead == NULL)
								FileTable->ColumnHead = ANode;
							else
							{
								DataNode* p = FileTable->ColumnHead;
								while (p->next != NULL)
									p = p->next;
								p->next = ANode;
							}
					}
					char address[30]="d:\\";
					strcat_s(address, FileName);
					DoFile dofile;
					dofile.OneTableInTxt(FileTable,address);
				}
			}
		}
	}
}



