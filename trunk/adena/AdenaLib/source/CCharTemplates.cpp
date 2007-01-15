/*
 * CCharTemplates.cpp - Caches the default char templates.
 * Created January 11, 2006, by Michael 'Bigcheese' Spencer.
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

#include <CCharTemplates.h>
#include <stdlib.h>

namespace adena
{
namespace game_server
{

CCharTemplates::CCharTemplates(irr::db::IDatabase* database)
: DataBase(database)
{
	loadTemplates();
};

CCharTemplates::~CCharTemplates()
{
	// Go thru and delete them all
	AVL<irr::u32, SClassTemplate*>::Iterator<irr::u32, SClassTemplate*> ittr(&Templates);
	irr::u32 key;
	SClassTemplate* item;
	if(ittr.GetFirst(key, item))
	{
		while(true)
		{
			delete item;
			if(!ittr.GetNext(key, item))
				break;
		}
	}
};

SClassTemplate* CCharTemplates::loadTemplate(irr::u32 class_id)
{
	SClassTemplate* ct;
	if(Templates.Find(class_id, ct))
	{
		return ct;
	}else
	{
		return NULL;
	}
};

void CCharTemplates::loadTemplates()
{
	irr::db::Query q(irr::core::stringc("SELECT * FROM char_templates"));
	irr::db::CQueryResult qr = DataBase->query(q);
	irr::u32 i;
	for(i = 0; i < qr.RowCount; i++)
	{
		SClassTemplate* ct = new SClassTemplate();
		ct->ClassId = atoi(qr[i]["ClassId"].c_str());
		ct->ClassName = qr[i]["ClassName"];
		ct->RaceId = atoi(qr[i]["RaceId"].c_str());
		ct->STR = atoi(qr[i]["STR"].c_str());
		ct->CON = atoi(qr[i]["CON"].c_str());
		ct->DEX = atoi(qr[i]["DEX"].c_str());
		ct->INT = atoi(qr[i]["_INT"].c_str());
		ct->WIT = atoi(qr[i]["WIT"].c_str());
		ct->MEN = atoi(qr[i]["MEN"].c_str());
		ct->P_ATK = atoi(qr[i]["P_ATK"].c_str());
		ct->P_DEF = atoi(qr[i]["P_DEF"].c_str());
		ct->M_ATK = atoi(qr[i]["M_ATK"].c_str());
		ct->M_DEF = atoi(qr[i]["M_DEF"].c_str());
		ct->P_SPD = atoi(qr[i]["P_SPD"].c_str());
		ct->M_SPD = atoi(qr[i]["M_SPD"].c_str());
		ct->ACC = atoi(qr[i]["ACC"].c_str());
		ct->CRIT = atoi(qr[i]["CRIT"].c_str());
		ct->EVASION = atoi(qr[i]["EVASION"].c_str());
		ct->RUN_SPEED = atoi(qr[i]["MOVE_SPD"].c_str());
		ct->MAX_WEIGHT = atoi(qr[i]["_LOAD"].c_str());
		ct->x = atoi(qr[i]["x"].c_str());
		ct->y = atoi(qr[i]["y"].c_str());
		ct->z = atoi(qr[i]["z"].c_str());
		ct->canCraft = atoi(qr[i]["canCraft"].c_str());
		ct->M_UNK1 = atoi(qr[i]["M_UNK1"].c_str());
		ct->M_UNK2 = atoi(qr[i]["M_UNK2"].c_str());
		ct->M_COL_R = atof(qr[i]["M_COL_R"].c_str());
		ct->M_COL_H = atof(qr[i]["M_COL_H"].c_str());
		ct->F_UNK1 = atoi(qr[i]["F_UNK1"].c_str());
		ct->F_UNK2 = atoi(qr[i]["F_UNK2"].c_str());
		ct->F_COL_R = atof(qr[i]["F_COL_R"].c_str());
		ct->F_COL_H = atof(qr[i]["F_COL_H"].c_str());
		ct->items1 = atoi(qr[i]["items1"].c_str());
		ct->items2 = atoi(qr[i]["items2"].c_str());
		ct->items3 = atoi(qr[i]["items3"].c_str());
		ct->items4 = atoi(qr[i]["items4"].c_str());
		ct->items5 = atoi(qr[i]["items5"].c_str());
		Templates.Insert(ct->ClassId, ct);
	}
};

}
}
