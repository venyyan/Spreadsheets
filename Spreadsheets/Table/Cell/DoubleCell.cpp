#include "DoubleCell.h"

DoubleCell::DoubleCell(double data) : Cell(CellType::Double), data(data) {};

DoubleCell::DoubleCell() : Cell(CellType::Double) {}


Cell* DoubleCell::Clone() const {
	Cell* newCell = new DoubleCell(*this);
	return newCell;
}

MyString DoubleCell::GetData() const {
	MyString result;
	return result.DoubleToString(this->data);
}

void DoubleCell::PrintCell(std::ostream& streamType) const {
	streamType << this->data;
}