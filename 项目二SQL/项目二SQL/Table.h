#pragma once
struct DataNode
{
	char data[15][60];
	DataNode* next;
};
struct  TableNode
{
	char TableName[20];
	char ColumnHeadName[15][60];
	int ColumnNum;
	DataNode *ColumnHead;
	TableNode* next;
};
class Table
{
public:
	TableNode *TableHead;
	Table();
	void CreateTable(char TheOrder[]);
	void DeleteTable(char TheOrder[]);
	void DropTable(char TheOrder[]);
	void InsertTable(char TheOrder[]);
	void UpdateTable(char TheOrder[]);
	void SelectTable(char TheOrder[]);
	void ShowTable();
	//more function
};

