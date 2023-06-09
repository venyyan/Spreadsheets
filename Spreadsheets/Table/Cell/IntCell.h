#pragma once
#include "Cell.h"
#include <fstream>

class IntCell : public Cell {
private:
	int data = 0;
public:
	IntCell();
	IntCell(int data);

	void PrintCell(std::ostream& streamType) const override;

	Cell* Clone() const override;
	virtual MyString GetData() const override;

};

