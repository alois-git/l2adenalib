/*
 * CSQLLite.cpp - SQL lite data base interface.
 * Created January 5, 2007, by Michael 'Bigcheese' Spencer.
 */

#include <CSQLLite.h>
#include <sqllite\sqlite3.h>

namespace irr
{
namespace db
{

CSQLLiteConParms::CSQLLiteConParms()
{
};

CSQLLiteConParms::~CSQLLiteConParms()
{
};

//========================================

CSQLLite::CSQLLite()
: db(0)
{

};

CSQLLite::~CSQLLite()
{
	disconnect();
};

core::stringc& CSQLLite::getLastError()
{
	return LastError;
};

bool CSQLLite::connect(IDbConParms* con_parms)
{
	disconnect();
	core::stringc file = ((CSQLLiteConParms*)con_parms)->FileName;
	int ret = sqlite3_open(file.c_str(), (sqlite3**)&db);
	if(ret == SQLITE_OK)
	{
		return true;
	}else
	{
		LastError = core::stringc(sqlite3_errmsg((sqlite3*)db));
		return false;
	}
};

void CSQLLite::disconnect()
{
	if(db)
		sqlite3_close((sqlite3*)db);
	db = 0;
};

CQueryResult CSQLLite::query(Query& q)
{
	bool ret;
	char ** table = 0;
	int rows;
	int columns;
	char* err = 0;
	CQueryResult res = CQueryResult();
	int fret = sqlite3_get_table((sqlite3*)db, q.QueryStr.c_str(), &table, &rows, &columns, &err);
	if(fret == SQLITE_OK)
	{
		res.RowCount = rows;
		for(int r = 1; r <= rows; r++)
		{
			CQueryResultRow row = CQueryResultRow();
			row.ColumnCount = columns;
			for(int c = 0; c < columns; c++)
				row.Data.Insert(core::stringc(table[c]), core::stringc(table[(r * columns) + c]));
			res.Rows.push_back(row);
		}
	}else
	{
		LastError = core::stringc(sqlite3_errmsg((sqlite3*)db));
	}
	sqlite3_free_table(table);
	sqlite3_free(err);
	return res;
};

}
}
