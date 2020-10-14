#pragma once
class Order
{
private:
	int key;
	char TheOrder[100];
public:
	Order();
	void StartOrder();
	void ReadOrder();
	void OperateTable();
	void OperateNothing();
	void OperateEnd();
};

