#pragma once
#include <fstream>
#include "../../Utilities/MyString.h"

enum class CellType {
	Int,
	Double,
	String,
	Formula
};

class Cell {
protected:
	CellType cellType;
public:
	Cell(CellType cellType) : cellType(cellType) {};

	virtual void PrintCell(std::ostream& streamType) const = 0;

	virtual Cell* clone() const = 0;
	virtual ~Cell() = default;
	virtual MyString GetData() const = 0;

	CellType GetType() const {
		return this->cellType;
	}
};