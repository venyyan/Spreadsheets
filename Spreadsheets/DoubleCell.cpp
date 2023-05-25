#include "DoubleCell.h"

DoubleCell::DoubleCell(double data) : Cell(CellType::Double), data(data) {};

DoubleCell::DoubleCell() : Cell(CellType::Double) {}


Cell* DoubleCell::clone() const {
	Cell* newCell = new DoubleCell(*this);
	return newCell;
}

double DoubleCell::GetData() const {
	return this->data;
}

void DoubleCell::PrintCell(std::ostream& streamType) const {
	streamType << this->data;
}