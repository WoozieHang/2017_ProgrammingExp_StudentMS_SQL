#include "Order.h"
#include<cstring>
#include<iostream>
#include"Table.h"
using namespace std;
Order::Order()
{
	key = -3;
	strcpy_s(TheOrder,"\0");
}
void Order::StartOrder()
{
	while (key != -2)
	{
		while (key != -1&&key!=-2)
		{
			cout << "~$ ";
			gets_s(TheOrder);
			ReadOrder();
		}
		if(key==-1)
		while (key != 0)
		{
			cout << "(mysql)==> ";
			gets_s(TheOrder);
			ReadOrder();
			if (key == 0)
				OperateEnd();
			else if (key == 8 || key == -1 || key == -2)
				OperateNothing();
			else
				OperateTable();
		}
	}
}
void Order::ReadOrder()
{
	if (TheOrder[0] == 'm'&&TheOrder[1] == 'y'&&TheOrder[2] == 'S'&&TheOrder[3] == 'Q'&&TheOrder[4] == 'L')
		key = -1;//mySQL
	else if (TheOrder[0] == 'E'&&TheOrder[1] == 'N'&&TheOrder[2] == 'D')
		key = -2;//END
	else if (TheOrder[0] == 'C'&&TheOrder[1] == 'R'&&TheOrder[2] == 'E'&&TheOrder[3] == 'A'&&TheOrder[4] == 'T'&&TheOrder[5] == 'E')
		key = 1;//CREATE 
	else if (TheOrder[0] == 'T'&&TheOrder[1] == 'A'&&TheOrder[2] == 'B'&&TheOrder[3] == 'L'&&TheOrder[4] == 'E')
		key = 2;//TABLE LIST
	else if (TheOrder[0] == 'D'&&TheOrder[1] == 'R'&&TheOrder[2] == 'O'&&TheOrder[3] == 'P')
		key = 3;//DROP
	else if (TheOrder[0] == 'I'&&TheOrder[1] == 'N'&&TheOrder[2] == 'S'&&TheOrder[3] == 'E'&&TheOrder[4] == 'R'&&TheOrder[5] == 'T')
		key = 4;//INSERT
	else if (TheOrder[0] == 'D'&&TheOrder[1] == 'E'&&TheOrder[2] == 'L'&&TheOrder[3] == 'E'&&TheOrder[4] == 'T'&&TheOrder[5] == 'E')
		key = 5;//DELETE
	else if (TheOrder[0] == 'U'&&TheOrder[1] == 'P'&&TheOrder[2] == 'D'&&TheOrder[3] == 'A'&&TheOrder[4] == 'T'&&TheOrder[5] == 'E')
		key = 6;//UPDATE
	else if (TheOrder[0] == 'S'&&TheOrder[1] == 'E'&&TheOrder[2] == 'L'&&TheOrder[3] == 'E'&&TheOrder[4] == 'C'&&TheOrder[5] == 'T')
		key = 7;//SELECT
	else if(TheOrder[0] == 'q'&&TheOrder[1] == 'u'&&TheOrder[2] == 'i'&&TheOrder[3] == 't')
		key = 0;//quit
	else key = 8;//NOTHING
	
}
void Order::OperateEnd()
{
}
void Order::OperateNothing()
{
}
void Order::OperateTable()
{
	Table table;
	if (key == 1)
		table.CreateTable(TheOrder);
	else if (key == 2)
		table.ShowTable();
	else if (key == 3)
		table.DropTable(TheOrder);
	else if (key == 4)
		table.InsertTable(TheOrder);
	else if (key == 5)
		table.DeleteTable(TheOrder);
	else if (key == 6)
		table.UpdateTable(TheOrder);
	else if (key == 7)
		table.SelectTable(TheOrder);
}


