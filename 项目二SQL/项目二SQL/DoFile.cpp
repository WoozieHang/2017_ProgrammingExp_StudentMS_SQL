#include "DoFile.h"
#include<iostream>
using namespace std;
void DoFile::TableListInFile(TableNode* TableHead)
{
	errno_t err;
	FILE *fp;
	err = fopen_s(&fp, "d:\\TableList.txt", "w");
	TableNode *x = TableHead;
	while (x != NULL)
{
	fputs(x->TableName, fp);
	fputs(",", fp);
	fprintf(fp, "%d", x->ColumnNum);
		for (int index = 0; index < x->ColumnNum; index++)
		{
			fputs(",", fp);
			fputs(x->ColumnHeadName[index], fp);
		}
	fputs("\n", fp);
	x = x->next;
}
	fclose(fp);
}

TableNode *DoFile::TableListOutFile()
{
	errno_t err;
	FILE *fp;
	err = fopen_s(&fp, "d:\\TableList.txt", "r");
	char information[50][200];
	int TableNum = 0;
	while (!feof(fp))
	{
		information[TableNum][0] = '\0';
		fgets(information[TableNum], 200, fp);
		TableNum++;
	}
	TableNode *TableHead = NULL;
	while(information[TableNum - 1][0] == '\0'|| information[TableNum - 1][0] == '\n')
		TableNum--;
	if (information[0][0] == '\0'||information[0][0]=='\n')
	{
		fclose(fp);
		return NULL;
	}
	for (int index = 0; index < TableNum; index++)
	{
		TableNode *x = new TableNode;
		x->next = NULL;
		int i = 0;
		for (int j = 0; information[index][i] != ','; i++)
		{
			x->TableName[j] = information[index][i];
			x->TableName[j + 1] = '\0';
			j++;
		}
		x = OneTableOutFile(x->TableName);
		if (TableHead == NULL)
			TableHead = x;
		else
		{
			TableNode *ANode = TableHead;
			while (ANode->next != NULL)
				ANode = ANode->next;
			ANode->next = x;
		}
	}
	fclose(fp);
	return TableHead;
}
void DoFile::OneTableInFile(TableNode*  OneTable)
{
	errno_t err;
	FILE *fp;
	char TableFileName[50]="d:\\";
	strcat_s(TableFileName, OneTable->TableName);
	TableFileName[3] += 'a' - 'A';
	strcat_s(TableFileName, ".txt");
	err = fopen_s(&fp, TableFileName, "w");
	for (int index = 0; index < OneTable->ColumnNum; index++)
	{
		fputs(OneTable->ColumnHeadName[index], fp);
		if (index != OneTable->ColumnNum - 1)
			fputs(" ", fp);
		else
			fputs("\n", fp);
	}
	DataNode *x = OneTable->ColumnHead;
	while (x != NULL)
	{
		for (int index = 0; index < OneTable->ColumnNum; index++)
		{
			fputs(x->data[index], fp);
			if (index != OneTable->ColumnNum - 1)
				fprintf(fp, " ");
		}
		fprintf(fp, "\n");
		x = x->next;
	}
	fclose(fp);
}

TableNode* DoFile::OneTableOutFile(char TableName[])
{
	errno_t err;
	FILE *fp;
	char TableFileName[50]="d:\\";
	strcat_s(TableFileName,TableName);
	TableFileName[3] += 'a' - 'A';
	strcat_s(TableFileName, ".txt");
	err = fopen_s(&fp, TableFileName, "r");
	TableNode* ToReturnTable = new TableNode;
	ToReturnTable->next = NULL;
	DataNode *DataHead = NULL;
	char CN[200];
	int ColumnNum = 0;
	fgets(CN, 200, fp);
	for (int i = 0; CN[i] != '\n'&&CN[i]!='\0'; )
	{
		int j = 0;
		while (CN[i] != ' '&&CN[i]!='\n'&&CN[i]!='\0')
		{
			ToReturnTable->ColumnHeadName[ColumnNum][j] = CN[i];
			ToReturnTable->ColumnHeadName[ColumnNum][j+1] ='\0';
			i++;
			j++;
		}
		ColumnNum++;
		if (CN[i] != '\n'&&CN[i] != '\0')
			i++;
	}
	ToReturnTable->ColumnNum = ColumnNum;
	char information[200][300];
	int IdNum = 0;
	while (!feof(fp))
	{
		information[IdNum][0] = '\0';
		fgets(information[IdNum], 300, fp);
		IdNum++;
	}
	while (information[IdNum-1][0] == '\0')
		IdNum--;
	for (int index = 0; index < IdNum; index++)//将IdNum行储存在链表中
	{
		DataNode *x = new DataNode;
		x->next = NULL;
		int i = 0;
		int ColumnId = 0;
		while(information[index][i] != '\n'&&information[index][i]!='\0')
		{
			for (int j = 0; information[index][i] != ' '&&information[index][i] != '\n'&&information[index][i] != '\0'; i++)
			{
				x->data[ColumnId][j] = information[index][i];
				x->data[ColumnId][j + 1] = '\0';
				j++;
			}
			if(information[index][i]==' ')
			i++;
			ColumnId++;
		}
		if (DataHead == NULL)
		{
			DataHead = x;
			x->next = NULL;
		}
		else
		{
			DataNode *ANode = DataHead;
			while (ANode->next != NULL)
				ANode = ANode->next;
			ANode->next = x;
			x->next = NULL;
		}
	}
	ToReturnTable->ColumnHead = DataHead;
	strcpy_s(ToReturnTable->TableName, TableName);
	fclose(fp);
	return ToReturnTable;
}

void DoFile::OneTableInTxt(TableNode*  OneTable, char address[])
{
	errno_t err;
	FILE *fp;
	err = fopen_s(&fp, address, "w");
	for (int index = 0; index < OneTable->ColumnNum; index++)
	{
		fputs(OneTable->ColumnHeadName[index], fp);
		if (index != OneTable->ColumnNum - 1)
			fputs(" ", fp);
		else
			fputs("\n", fp);
	}
	DataNode *x = OneTable->ColumnHead;
	while (x != NULL)
	{
		for (int index = 0; index < OneTable->ColumnNum; index++)
		{
			fputs(x->data[index], fp);
			if (index != OneTable->ColumnNum - 1)
				fprintf(fp, " ");
		}
		fprintf(fp, "\n");
		x = x->next;
	}
	fclose(fp);
}



