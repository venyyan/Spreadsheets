#include "StringCell.h"

StringCell::StringCell() : Cell(CellType::String) {}

StringCell::StringCell(const MyString& data) : Cell(CellType::String), data(data) {}

void StringCell::PrintCell(std::ostream& streamType) const {
	streamType << this->data;
}

Cell* StringCell::clone() const {
	Cell* newCell = new StringCell(*this);
	return newCell;
}

MyString StringCell::GetData() const {
	return this->data;
}