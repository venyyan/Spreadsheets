#pragma once
#include "Row.h"
#include "MyString.h"
#include "CellFactory.h"
#include "IntCell.h"
#include "DoubleCell.h"

class Table
{
private:
	MyVector<UniquePtr<Row>> rows;
public:
	Table() = default;
	Table(const MyString& filePath);
	void PrintTable(std::ostream& streamType) const;

private:
	void GetTableFromFile(const MyString& filePath);
	
	UniquePtr<Row> ReadRow(std::ifstream& ifs) const;

	UniquePtr<Cell> ReturnCell(const MyString& cellStr) const;
};

