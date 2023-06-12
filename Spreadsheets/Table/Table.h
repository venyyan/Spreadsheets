#pragma once
#include "Row.h"
#include "..\Utilities\MyString.h"
#include "Cell\CellFactory.h"
#include "Cell\IntCell.h"
#include "Cell\DoubleCell.h"
#include "Cell\StringCell.h"

class Table
{
private:
	MyVector<UniquePtr<Row>> rows;
public:
	Table() = default;
	Table(const MyString& filePath);
	void PrintTable(std::ostream& streamType) const;
	void EditCell(size_t row, size_t column, const MyString& newData);
private:
	void GetTableFromFile(const MyString& filePath);
	
	UniquePtr<Row> ReadRow(std::ifstream& ifs) const;

	UniquePtr<Cell> ReturnCell(const MyString& cellStr) const;

	
};

