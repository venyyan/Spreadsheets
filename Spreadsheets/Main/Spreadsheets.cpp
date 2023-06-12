#include <iostream>
#include "..\Table\Table.h"

int main()
{
	Table table("file.txt");
	
	MyString data("\"tjkgrtjg\"");
	table.EditCell(1, 2, data);

	table.PrintTable(std::cout);
}