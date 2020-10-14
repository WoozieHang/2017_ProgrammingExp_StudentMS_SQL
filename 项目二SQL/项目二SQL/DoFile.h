#include"Table.h"
class DoFile
{
public:
	void TableListInFile(TableNode* TableHead);
	TableNode* TableListOutFile();//调用OneTableOutFile
	void OneTableInFile(TableNode*  OneTable);
	TableNode* OneTableOutFile(char TableName[]);//只被TableListOutFile调用
	void OneTableInTxt(TableNode*  OneTable, char address[]);
};

