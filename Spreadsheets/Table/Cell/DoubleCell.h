#pragma once
#include "Cell.h"
#include <fstream>

class DoubleCell : public Cell {
private:
	double data = 0;
public:
	DoubleCell();
	DoubleCell(double data);

	void PrintCell(std::ostream& streamType) const override;

	Cell* Clone() const override;
	virtual MyString GetData() const override;
};

