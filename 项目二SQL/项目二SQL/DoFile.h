#include"Table.h"
class DoFile
{
public:
	void TableListInFile(TableNode* TableHead);
	TableNode* TableListOutFile();//����OneTableOutFile
	void OneTableInFile(TableNode*  OneTable);
	TableNode* OneTableOutFile(char TableName[]);//ֻ��TableListOutFile����
	void OneTableInTxt(TableNode*  OneTable, char address[]);
};

