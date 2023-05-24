#include "CellFactory.h"
#include "Cell.h"
#include "IntCell.h"
#include "DoubleCell.h"

Cell* CellFactory(CellType cellType)
{
	switch (cellType)
	{
	case CellType::Int:
		return new IntCell();
	case CellType::Double:
		return new DoubleCell();
	}
	return nullptr;
}