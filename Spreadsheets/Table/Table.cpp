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

	if (!file.is_open()) {
		//exception in constr?
	}

	MyVector<SharedPtr<Row>> rows;
	
	while (true) {
		if (file.eof())
			break;

		SharedPtr<Row> currentRow = ReadRow(file);
		rows.PushBack(std::move(currentRow));
	}
	size_t longestRow = 0;
	this->rows = std::move(rows);

	for (size_t i = 0; i < this->rows.GetSize(); i++)
	{
		if (this->rows.At(i)->GetCellsCount() > longestRow)
			longestRow = this->rows.At(i)->GetCellsCount();
	}

	for (size_t i = 0; i < this->rows.GetSize(); i++)
	{
		
		if (this->rows.At(i)->GetCellsCount() < longestRow) {
			int cycle = longestRow - this->rows.At(i)->GetCellsCount();
			for (size_t j = 0; j < cycle; j++)
			{
				SharedPtr<Cell> cell = new StringCell("");
				this->rows.At(i)->AddCell(std::move(cell));
			}
		}
			
	}
}

SharedPtr<Row> Table::ReadRow(std::ifstream& ifs) const {
	MyString rowBuffer;
	ifs >> rowBuffer;
	
	if (rowBuffer.IsEmpty())
	{
		return SharedPtr<Row>();
	}

	SharedPtr<Row> currentRow(new Row());

	std::stringstream ss(rowBuffer.c_str());
	size_t cellsCount = 0;

	while (!ss.eof())
	{
		char cellBuffer[1024];
		ss.getline(cellBuffer, CELL_MAX_SIZE, ',');

		MyString cellStr(cellBuffer);
		CellType cellType;
		SharedPtr<Cell> cell = ReturnCell(cellStr);
		currentRow->AddCell(std::move(cell));
	}
	return currentRow;
}

SharedPtr<Cell> Table::ReturnCell(const MyString& cellStr) const {
	if (cellStr.IsInt()) {
		return new IntCell(cellStr.stoi());
	}
	else if (cellStr.IsDouble()) {
		return new DoubleCell(cellStr.stod());
	}
	else if (cellStr.IsQuote()) {
		return new StringCell(cellStr.ExtractQuote());
	}
	else if (cellStr.IsFormula()) {
		SharedPtr<const Table> table(this);
		return new FormulaCell(cellStr.ExtractFormula(), table);
	}
	else {
		return new StringCell("");
	}
	//throw std::runtime_error("Invalid value!");

	//think about empty cells - maybe empty StringCell
}

void Table::PrintTable(std::ostream& streamType) const {
	
	for (size_t i = 0; i < this->rows.GetSize(); i++)
	{
		this->rows.At(i)->PrintRow(streamType);
		streamType << std::endl;
	}
}

void Table::EditCell(size_t row, size_t column, const MyString& newData) {
	//check if this cell exists
	SharedPtr<Cell> edited = ReturnCell(newData);
	this->rows.At(row)->EditCell(std::move(edited), column);
}

const MyVector<SharedPtr<Row>>& Table::GetRows() const {
	return this->rows;
}