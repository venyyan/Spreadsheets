#include <iostream>
#include "..\Table\Table.h"
#include "..\Formula\ExpressionCalculator.h"
int main()
{
	Table* table = new Table("file.txt");/*
	MyString data("\"tjkgrtjg\"");
	table.EditCell(1, 2, data);*/
	table->PrintTable(std::cout);
}