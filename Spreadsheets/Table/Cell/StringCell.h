#pragma once
#include "Cell.h"
#include "..\..\Utilities\MyString.h"

class StringCell : public Cell
{
private:
	MyString data;
public:
	StringCell();
	StringCell(const MyString& data);

	void PrintCell(std::ostream& streamType) const override;

	Cell* Clone() const override;

	virtual MyString GetData() const override;

};

