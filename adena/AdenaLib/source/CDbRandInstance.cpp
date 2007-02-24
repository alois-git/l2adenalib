/*
 * CDbRandInstance.cpp - getting db and rand singleton.
 * Created February 20, 2007, by Michael 'Bigcheese' Spencer.
 *
 * Copyright (C) 2007 Michael Spencer
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Michael Spencer - bigcheesegs@gmail.com
 */

#include <CDbRandInstance.h>
#include <CConfig.h>
#include <CMersenneTwister.h>

namespace adena
{

CDbRandInstance::CDbRandInstance()
{

};

CDbRandInstance::~CDbRandInstance()
{

};

irr::db::IDatabase* CDbRandInstance::getDbInstance()
{
	static irr::db::IDatabase* DataBase = 0;	

	if(!DataBase)
	{
		CConfig* ConfigFile = CConfig::getInstance();

		irr::db::IDbConParms* conp;
		if(!strcmp("mysql" ,ConfigFile->getString("database", "type").c_str()))
		{
			DataBase = new irr::db::CMySQL();
			irr::db::CMySQLConParms* cp = new irr::db::CMySQLConParms();
			cp->Ip = ConfigFile->getString("mysql", "ip");
			cp->Username = ConfigFile->getString("mysql", "username");
			cp->Password = ConfigFile->getString("mysql", "password");
			cp->Db = ConfigFile->getString("mysql", "db");
			cp->Port = ConfigFile->getInt("mysql", "port");
			conp = cp;
		}else
		{
			DataBase = new irr::db::CSQLLite();
			irr::db::CSQLLiteConParms* qp = new irr::db::CSQLLiteConParms();
			qp->FileName = ConfigFile->getString("sqlite", "file");
			conp = qp;
		}
		//Interfaces.Logger->log("Attempting to connect to DB...");
		if(!DataBase->connect(conp))
		{
			//Interfaces.Logger->log("FATAL ERROR: Failed to connect to DB (Check connection settings)", irr::ELL_ERROR);
			delete conp;
			return 0;
		}else
			//Interfaces.Logger->log("DB connection sucsessfull");

		delete conp;
	}

	return DataBase;
};

irr::IRng* CDbRandInstance::getRngInstance()
{
	static irr::IRng* rng = 0;

	if(!rng)
	{
		rng = new irr::CMersenneTwister();
	}

	return rng;
};

}
