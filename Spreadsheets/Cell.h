#pragma once

enum class CellType {
	Int,
	Double
};

class Cell {
private:
	CellType cellType;
public:
	Cell(CellType cellType) : cellType(cellType) {};

	virtual void PrintCell() const = 0;
	virtual Cell* clone() const = 0;
	virtual ~Cell() = default;

	CellType GetType() const {
		return this->cellType;
	}
};