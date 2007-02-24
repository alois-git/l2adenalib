/*
 * CPlayerCache.cpp - Interface for getting player info from the SQL database.
 * Created January 10, 2007, by Michael 'Bigcheese' Spencer.
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

#include <CPlayerCache.h>
#include <SGameServerInterfaces.h>
#include <CCharTemplates.h>
#include <CItemInstance.h>
#include <CItemCache.h>
#include <COObjectSystem.h>

namespace adena
{
namespace game_server
{

CPlayerCache::CPlayerCache(void* interfaces)
: Interfaces(interfaces)
{

};

CPlayerCache::~CPlayerCache()
{
	// Go thru and delete them all
	CharInfosLock.writeLock();
	AVL<irr::u32, SCharInfo*>::Iterator<irr::u32, SCharInfo*> ittr(&CharInfos);
	irr::u32 key;
	SCharInfo* item;
	if(ittr.GetFirst(key, item))
	{
		while(true)
		{
			delete item;
			if(!ittr.GetNext(key, item))
				break;
		}
	}
	CharInfosLock.unlock();
};

bool CPlayerCache::createChar(SCharInfo &char_info)
{
	SGameServerInterfaces* interfaces = (SGameServerInterfaces*)Interfaces;
	irr::db::Query check_name(irr::core::stringc("SELECT * FROM characters WHERE characters.name = '$name'"));
	check_name.setVar(irr::core::stringc("$name"), char_info.Name);
	if(interfaces->DataBase->query(check_name).RowCount != 0)
	{
		// Name already taken.
		return false;
	}else
	{
		SGameServerInterfaces* interfaces = (SGameServerInterfaces*)Interfaces;
		SClassTemplate* ct = interfaces->CharTemplates->loadTemplate(char_info.ClassId);
		if(ct == NULL)
		{
			// Hack attempt
			interfaces->Logger->log("[HACK ALERT] Client attempted to create a char with a ClassId not listed");
			return false;
		}else
		{
			// TODO: Vailidate that the class id is a first class and part of the race
		}

		// Add char
		irr::db::Query add_char(irr::core::stringc("INSERT INTO characters (account_id, name, race_id, class_id, sex, hair_type, hair_color, face, level, xp, sp, hp, mp, cp, x, y, z)\
VALUES ($acc, '$name', $race, $class, $sex, $hairt, $hairc, $face, $lvl, $xp, $sp, $hp, $mp, $cp, $x, $y, $z)"));
		add_char.setVar(irr::core::stringc("$acc"), irr::core::stringc((int)char_info.AccountId));
		add_char.setVar(irr::core::stringc("$name"), char_info.Name);
		add_char.setVar(irr::core::stringc("$race"), irr::core::stringc((int)char_info.RaceId));
		add_char.setVar(irr::core::stringc("$class"), irr::core::stringc((int)char_info.ClassId));
		add_char.setVar(irr::core::stringc("$sex"), irr::core::stringc((int)char_info.Sex));
		add_char.setVar(irr::core::stringc("$hairt"), irr::core::stringc((int)char_info.HairType));
		add_char.setVar(irr::core::stringc("$hairc"), irr::core::stringc((int)char_info.HairColor));
		add_char.setVar(irr::core::stringc("$face"), irr::core::stringc((int)char_info.FaceType));
		add_char.setVar(irr::core::stringc("$lvl"), irr::core::stringc(1));
		add_char.setVar(irr::core::stringc("$xp"), irr::core::stringc(0));
		add_char.setVar(irr::core::stringc("$sp"), irr::core::stringc(0));
		add_char.setVar(irr::core::stringc("$hp"), irr::core::stringc(50));
		add_char.setVar(irr::core::stringc("$mp"), irr::core::stringc(50));
		add_char.setVar(irr::core::stringc("$cp"), irr::core::stringc(50));
		add_char.setVar(irr::core::stringc("$x"), irr::core::stringc(ct->x));
		add_char.setVar(irr::core::stringc("$y"), irr::core::stringc(ct->y));
		add_char.setVar(irr::core::stringc("$z"), irr::core::stringc(ct->z));
		interfaces->DataBase->query(add_char);
		return true;
	}
};

SCharSelectIds CPlayerCache::loadCharSelect(irr::u32 account_id)
{
	SGameServerInterfaces* interfaces = (SGameServerInterfaces*)Interfaces;
	irr::db::Query chars(irr::core::stringc("SELECT id FROM characters WHERE account_id = $acc"));
	chars.setVar(irr::core::stringc("$acc"), irr::core::stringc((int)account_id));
	irr::db::CQueryResult qr = interfaces->DataBase->query(chars);
	SCharSelectIds csi;
	csi.Chars = qr.RowCount;
	irr::u32 i;
	for(i = 0; i < csi.Chars; i++)
	{
		csi.CharIds[i] = atoi(qr[i]["id"].c_str());
	}

	return csi;
};

SCharInfo* CPlayerCache::loadChar(irr::u32 char_id)
{
	SGameServerInterfaces* interfaces = (SGameServerInterfaces*)Interfaces;
	SCharInfo* ci;
	CharInfosLock.readLock();
	if(CharInfos.Find(char_id, ci))
	{
		CharInfosLock.unlock();
		return ci;
	}else
	{
		// No need to hold the lock while we do a query
		CharInfosLock.unlock();

		// Load from database
		irr::db::Query q(irr::core::stringc("SELECT * FROM characters WHERE id = $id"));
		q.setVar(irr::core::stringc("$id"), irr::core::stringc((int)char_id));
		irr::db::CQueryResult qr = interfaces->DataBase->query(q);

		if(qr.RowCount != 1)
		{
			// Char doesn't exist
			return NULL;
		}

		ci = new SCharInfo();

		ci->InUse = true;
		ci->CharacterId = atoi(qr[0]["id"].c_str());
		ci->AccountId = atoi(qr[0]["account_id"].c_str());
		ci->Name = qr[0]["name"];
		ci->RaceId = atoi(qr[0]["race_id"].c_str());
		ci->ClassId = atoi(qr[0]["class_id"].c_str());
		ci->Sex = atoi(qr[0]["sex"].c_str());
		ci->HairType = atoi(qr[0]["hair_type"].c_str());
		ci->HairColor = atoi(qr[0]["hair_color"].c_str());
		ci->FaceType = atoi(qr[0]["face"].c_str());
		ci->Title = qr[0]["title"];
		ci->Level = atoi(qr[0]["level"].c_str());
		ci->xp = atoi(qr[0]["xp"].c_str());
		ci->sp = atoi(qr[0]["sp"].c_str());
		ci->hp = atoi(qr[0]["hp"].c_str());
		ci->mp = atoi(qr[0]["mp"].c_str());
		ci->cp = atoi(qr[0]["cp"].c_str());
		ci->x = atoi(qr[0]["x"].c_str());
		ci->y = atoi(qr[0]["y"].c_str());
		ci->z = atoi(qr[0]["z"].c_str());

		// Query skills
		{
			irr::db::Query q2(irr::core::stringc("SELECT * FROM char_skills WHERE char_id = $id"));
			q2.setVar(irr::core::stringc("$id"), irr::core::stringc((int)char_id));
			irr::db::CQueryResult qr2 = interfaces->DataBase->query(q2);

			for(irr::u32 i = 0; i < qr2.RowCount; i++)
			{
				SSkill s;
				s.Id = atoi(qr2[i]["skill_id"].c_str());
				s.Level = atoi(qr2[i]["skill_level"].c_str());
				s.Enchant = atoi(qr2[i]["skill_enchant"].c_str());
				ci->Skills.push_back(s);
			}
		}

		{
			// Query Items
			irr::db::Query q2(irr::core::stringc("SELECT * FROM items WHERE owner_id = $id"));
			q2.setVar(irr::core::stringc("$id"), irr::core::stringc((int)char_id));
			irr::db::CQueryResult qr2 = interfaces->DataBase->query(q2);

			for(irr::u32 i = 0; i < qr2.RowCount; i++)
			{
				CItemInstance ii;

				ii.Id = COObjectSystem::getInstance()->getNextId();
				ii.ItemInfo = CItemCache::getInstance()->getItemInfo(atoi(qr2[i]["item_id"].c_str()));
				ii.ItemCount = atoi(qr2[i]["count"].c_str());
				ci->Items.push_back(ii);
			}
		}

		CharInfosLock.writeLock();
		CharInfos.Insert(char_id, ci);
		CharInfosLock.unlock();
		return ci;
	}
};

void CPlayerCache::saveChar(irr::u32 char_id)
{
		SGameServerInterfaces* interfaces = (SGameServerInterfaces*)Interfaces;
		SCharInfo* ci;
		CharInfosLock.readLock();
		if(!CharInfos.Find(char_id, ci))
		{
			CharInfosLock.unlock();
			return;
		}
		CharInfosLock.unlock();

		{
			irr::db::Query save_char(irr::core::stringc("UPDATE characters SET class_id = $class, title = '$title', level = $lvl, xp = $xp, sp = $sp, hp = $hp, mp = $mp, cp = $cp, x = $x, y = $y, z = $z WHERE id = $id"));
			save_char.setVar(irr::core::stringc("$class"), irr::core::stringc((int)ci->ClassId));
			save_char.setVar(irr::core::stringc("$title"), ci->Title);
			save_char.setVar(irr::core::stringc("$lvl"), irr::core::stringc((int)ci->Level));
			save_char.setVar(irr::core::stringc("$xp"), irr::core::stringc((int)ci->xp));
			save_char.setVar(irr::core::stringc("$sp"), irr::core::stringc((int)ci->sp));
			save_char.setVar(irr::core::stringc("$hp"), irr::core::stringc((int)ci->hp));
			save_char.setVar(irr::core::stringc("$mp"), irr::core::stringc((int)ci->mp));
			save_char.setVar(irr::core::stringc("$cp"), irr::core::stringc((int)ci->cp));
			save_char.setVar(irr::core::stringc("$x"), irr::core::stringc(ci->x));
			save_char.setVar(irr::core::stringc("$y"), irr::core::stringc(ci->y));
			save_char.setVar(irr::core::stringc("$z"), irr::core::stringc(ci->z));
			save_char.setVar(irr::core::stringc("$id"), irr::core::stringc((int)char_id));
			interfaces->DataBase->query(save_char);
		}

		// Skills
		{
			irr::db::Query del_skills(irr::core::stringc("DELETE FROM char_skills WHERE char_id = $id"));
			del_skills.setVar(irr::core::stringc("$id"), irr::core::stringc((int)char_id));
			interfaces->DataBase->query(del_skills);

			irr::core::stringc query("INSERT INTO char_skills (char_id, skill_id, skill_level, skill_enchant) VALUES ");
			for(irr::u32 i = 0; i < ci->Skills.size(); i++)
			{
				query += "(";
				query += (irr::s32)ci->CharacterId;
				query += ", ";
				query += (irr::s32)ci->Skills[i].Id;
				query += ", ";
				query += (irr::s32)ci->Skills[i].Level;
				query += ", ";
				query += (irr::s32)ci->Skills[i].Enchant;
				query += ")";

				if(i != ci->Skills.size() - 1)
					query += ",";
			}

			irr::db::Query add_skills(query);
			interfaces->DataBase->query(add_skills);
		}

		// Items
		{
			irr::db::Query del_items(irr::core::stringc("DELETE FROM items WHERE owner_id = $id"));
			del_items.setVar(irr::core::stringc("$id"), irr::core::stringc((int)char_id));
			interfaces->DataBase->query(del_items);

			irr::core::stringc query("INSERT INTO items (owner_id, item_id, count, loc, equip_loc) VALUES ");
			for(irr::u32 i = 0; i < ci->Items.size(); i++)
			{
				query += "(";
				query += (irr::s32)ci->CharacterId;
				query += ", ";
				query += (irr::s32)ci->Items[i].ItemInfo->ItemId;
				query += ", ";
				query += (irr::s32)ci->Items[i].ItemCount;
				query += ", 'INVENTORY', 0)";

				if(i != ci->Skills.size() - 1)
					query += ",";
			}

			irr::db::Query add_items(query);
			interfaces->DataBase->query(add_items);
		}
};

void CPlayerCache::garbageCollect(bool full_collect)
{
	
};

}
}
