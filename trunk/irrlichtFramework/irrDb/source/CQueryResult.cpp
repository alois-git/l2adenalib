/*
 * CQueryResult.cpp - Query result.
 * Created January 5, 2007, by Michael 'Bigcheese' Spencer.
 */

#include <CQueryResult.h>

namespace irr
{
namespace db
{

CQueryResultRow::CQueryResultRow()
{
	//Data = AVL<core::stringc, core::stringc>();
};

CQueryResultRow::~CQueryResultRow()
{

};

u32 CQueryResultRow::getColumns()
{
	return ColumnCount;
};

core::stringc CQueryResultRow::operator [](core::stringc &str)
{
	core::stringc item("");
	Data.Find(str, item);
	return item;
};

//================================

CQueryResult::CQueryResult()
{
	//Rows = core::array<CQueryResultRow>();
};

CQueryResult::~CQueryResult()
{

};

u32 CQueryResult::getRows()
{
	return RowCount;
};

CQueryResultRow CQueryResult::operator [](u32 idx)
{
	if(idx >= Rows.size())	
		return CQueryResultRow();

	return Rows[idx];
};

}
}
