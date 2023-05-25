#include "Table.h"
#include <fstream>
#include <sstream>
#include <exception>

const int CELL_MAX_SIZE = 100;

Table::Table(const MyString& filePath) {
	GetTableFromFile(filePath);
}

void Table::GetTableFromFile(const MyString& filePath) {
	std::ifstream file(filePath.c_str());

	if (!file) {
		//exception in constr?
	}

	MyVector<UniquePtr<Row>> rows;

	while (true) {
		if (file.eof())
			break;

		UniquePtr<Row> currentRow = ReadRow(file);
		rows.PushBack(std::move(currentRow));
	}
	this->rows = std::move(rows);
}

UniquePtr<Row> Table::ReadRow(std::ifstream& ifs) const {
	MyString rowBuffer;
	ifs >> rowBuffer;

	Row* row = new Row();
	UniquePtr<Row> currentRow(row);

	std::stringstream ss(rowBuffer.c_str());
	size_t cellsCount = 0;

	while (!ss.eof())
	{
		char cellBuffer[1024];
		ss.getline(cellBuffer, CELL_MAX_SIZE, ',');

		MyString cellStr(cellBuffer);
		CellType cellType;
		UniquePtr<Cell> cell = ReturnCell(cellStr);
		currentRow->AddCell(std::move(cell));
	}
	return currentRow;
}

UniquePtr<Cell> Table::ReturnCell(const MyString& cellStr) const {
	if (cellStr.IsInt()) {
		return new IntCell(cellStr.stoi());
	}
	else if (cellStr.IsDouble()) {
		return new DoubleCell(cellStr.stod());
	}
	else
		throw std::runtime_error("Invalid value!");
}

void Table::PrintTable(std::ostream& streamType) const {
	
	for (size_t i = 0; i < this->rows.GetSize(); i++)
	{
		this->rows.At(i)->PrintRow(streamType);
		streamType << std::endl;
	}
}