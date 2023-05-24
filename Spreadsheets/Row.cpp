#include "Row.h"
#include "CellFactory.h"

void Row::AddCell(CellType cellType) {
	cells.SetAt(std::move(CellFactory(cellType)), this->cellsCount++);
}