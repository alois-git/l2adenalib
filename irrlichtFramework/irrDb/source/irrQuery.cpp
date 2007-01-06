/*
 * irrQuery.cpp - A safe data base query.
 * Created January 5, 2007, by Michael 'Bigcheese' Spencer.
 */

#include <irrQuery.h>

namespace irr
{
namespace db
{

Query::Query(core::stringc& str)
{
	QueryStr = str;
};

Query::~Query()
{

};

void Query::setVar(core::stringc& var_str, core::stringc& val_str)
{
	QueryStr.replaceStr(var_str, val_str);
	// TODO: Make it sql safe :P.
};

}
}
