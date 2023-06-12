#pragma once
#include "Cell.h"
#include "MyString.h"

class StringCell : public Cell
{
private:
	MyString data;
public:
	StringCell();
	StringCell(const MyString& data);

	void PrintCell(std::ostream& streamType) const override;

	Cell* clone() const override;

	const MyString& GetData() const;

};

