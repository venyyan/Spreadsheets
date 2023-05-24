#include "DoubleCell.h"

DoubleCell::DoubleCell(double data) : Cell(CellType::Double), data(data) {};

//void DoubleCell::PrintCell() const {
//
//}

Cell* DoubleCell::clone() const {
	Cell* newCell = new DoubleCell(*this);
	return newCell;
}

double DoubleCell::GetData() const {
	return this->data;
}