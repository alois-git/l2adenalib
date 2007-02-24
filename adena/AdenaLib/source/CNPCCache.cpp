/*
 * CNPCCache.cpp - Loads all the npc types from the database and stores them.
 * Created February 6, 2007, by Michael 'Bigcheese' Spencer.
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

#include <CNPCCache.h>
#include <stdlib.h>

namespace adena
{
namespace game_server
{

CNPCCache::CNPCCache()
{

};

CNPCCache::~CNPCCache()
{

};

void CNPCCache::init(irr::db::IDatabase* db)
{
	{
		printf("Loading NPC info from data base...\n");
		irr::db::Query q(irr::core::stringc("SELECT * FROM npc"));
		irr::db::CQueryResult qr = db->query(q);
		for(irr::u32 i = 0; i < qr.RowCount; i++)
		{
			SNPCInfo* ni = new SNPCInfo();
			ni->Id = atoi(qr[i]["id"].c_str());
			ni->Name = qr[i]["name"];
			ni->Title = qr[i]["title"];
			ni->Collision_radius = atof(qr[i]["collision_radius"].c_str());
			ni->Collision_height = atof(qr[i]["collision_height"].c_str());
			ni->Level = atoi(qr[i]["level"].c_str());
			if(qr[i]["sex"] == "male")
				ni->Sex = 0;
			else
				ni->Sex = 1;
			ni->SpawnClass = qr[i]["type"];
			ni->Atk_range = atoi(qr[i]["attackrange"].c_str());
			ni->Hp = atoi(qr[i]["hp"].c_str());
			ni->Mp = atoi(qr[i]["mp"].c_str());
			ni->Hp_regen = atof(qr[i]["hpreg"].c_str());
			ni->Mp_regen = atof(qr[i]["mpreg"].c_str());
			ni->STR = atoi(qr[i]["str"].c_str());
			ni->CON = atoi(qr[i]["con"].c_str());
			ni->DEX = atoi(qr[i]["dex"].c_str());
			ni->INT = atoi(qr[i]["int"].c_str());
			ni->WIT = atoi(qr[i]["wit"].c_str());
			ni->MEN = atoi(qr[i]["men"].c_str());
			ni->Exp = atoi(qr[i]["exp"].c_str());
			ni->Sp = atoi(qr[i]["sp"].c_str());
			ni->Patk = atoi(qr[i]["patk"].c_str());
			ni->Pdef = atoi(qr[i]["pdef"].c_str());
			ni->Matk = atoi(qr[i]["matk"].c_str());
			ni->Mdef = atoi(qr[i]["mdef"].c_str());
			ni->Atk_spd = atoi(qr[i]["atkspd"].c_str());
			ni->Aggro_range = atoi(qr[i]["aggro"].c_str());
			ni->Matk_spd = atoi(qr[i]["matkspd"].c_str());
			ni->Rhand = atoi(qr[i]["rhand"].c_str());
			ni->Lhand = atoi(qr[i]["lhand"].c_str());
			ni->Armor = atoi(qr[i]["armor"].c_str());
			ni->Walk_spd = atoi(qr[i]["walkspd"].c_str());
			ni->Run_spd = atoi(qr[i]["runspd"].c_str());
			ni->Is_undead = atoi(qr[i]["isUndead"].c_str());

			NPCs.Insert(ni->Id, ni);
		}
		printf("NPC info loaded.\n");
	}
	{
		printf("Loading drop list...\n");

		irr::db::Query q(irr::core::stringc("SELECT * FROM droplist"));
		irr::db::CQueryResult qr = db->query(q);

		for(irr::u32 i = 0; i < qr.RowCount; i++)
		{
			SNPCInfo* ni = getNPC(atoi(qr[i]["mobId"].c_str()));
			if(ni)
			{
				SDropInfo di;
				di.ItemId = atoi(qr[i]["itemId"].c_str());
				di.Min = atoi(qr[i]["min"].c_str());
				di.Max = atoi(qr[i]["max"].c_str());
				di.Chance = atoi(qr[i]["chance"].c_str());
				ni->DropInfo.push_back(di);
			}
		}

		printf("Drop list loaded.\n");
	}
};

SNPCInfo* CNPCCache::getNPC(irr::u32 id)
{
	SNPCInfo* npc;
	if(NPCs.Find(id, npc))
	{
		return npc;
	}
	return NULL;
};

}
}
