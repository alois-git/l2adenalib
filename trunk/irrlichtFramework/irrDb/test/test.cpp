#include <irrDb.h>
#include <iostream>

using namespace std;
using namespace irr;

int main()
{
	db::IDatabase* db = new db::CSQLLite();
	db::CSQLLiteConParms p = db::CSQLLiteConParms();
	p.FileName = "l2login.sqlite";
	if(!db->connect(&p))
	{
		cout << "Error: " << db->getLastError().c_str() << "\n";
	}else
	{
		cout << "No error\n";
		db::Query q(core::stringc("SELECT * FROM accounts WHERE username = '$user'"));
		q.setVar(core::stringc("$user"), core::stringc("bob"));
		db::CQueryResult qr = db->query(q);
		for(int i = 0; i < qr.getRows(); i++)
			cout << qr[i][core::stringc("username")].c_str() << "\n";
	}
	system("PAUSE");
	return 0;
}