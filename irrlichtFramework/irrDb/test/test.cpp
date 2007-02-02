#include <irrDb.h>
#include <iostream>

using namespace std;
using namespace irr;

int main()
{
	db::IDatabase* db = new db::CMySQL();
	db::CMySQLConParms p = db::CMySQLConParms();
	p.Ip = "localhost";
	p.Username = "root";
	p.Password = "superhi";
	p.Db = "l2jdb";
	p.Port = 3306;
	if(!db->connect(&p))
	{
		cout << "Error: " << db->getLastError().c_str() << "\n";
	}else
	{
		cout << "No error\n";
		db::Query q(core::stringc("SELECT * FROM accounts WHERE login = '$user'"));
		q.setVar(core::stringc("$user"), core::stringc("bigcheese"));
		db::CQueryResult qr = db->query(q);
		for(int i = 0; i < qr.getRows(); i++)
			cout << qr[i][core::stringc("login")].c_str() << "\n";
	}
	system("PAUSE");
	return 0;
}