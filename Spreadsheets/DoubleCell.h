#pragma once
#include "Cell.h"

class DoubleCell : public Cell{
private:
	double data = 0;
public:
	DoubleCell(double data);

	void PrintCell() const override;
	Cell* clone() const override;

	double GetData() const;
};

