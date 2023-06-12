#pragma once
#include <fstream>

enum class CellType {
	Int,
	Double,
	String
};

class Cell {
private:
	CellType cellType;
public:
	Cell(CellType cellType) : cellType(cellType) {};

	virtual void PrintCell(std::ostream& streamType) const = 0;

	virtual Cell* clone() const = 0;
	virtual ~Cell() = default;

	CellType GetType() const {
		return this->cellType;
	}
};