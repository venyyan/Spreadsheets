#pragma once
#include "Cell.h"

class IntCell : public Cell {
private:
	int data;
public:
	IntCell(int data);

	void PrintCell() const override;
	Cell* clone() const override;

	int GetData() const;
};

