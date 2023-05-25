#include <iostream>
#include "Table.h"

int main()
{
	Table table("file.txt");
	table.PrintTable(std::cout);
}