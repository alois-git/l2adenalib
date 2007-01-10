/*
 * CPlayerCache.cpp - Interface for getting player info from the SQL database.
 * Created January 10, 2006, by Michael 'Bigcheese' Spencer.
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
		// Add char
		irr::db::Query add_char(irr::core::stringc("INSERT INTO characters (account_id, name, race_id, class_id, sex, hair_type, hair_color, face)\
VALUES ($acc, '$name', $race, $class, $sex, $hairt, $hairc, $face)"));
		add_char.setVar(irr::core::stringc("$acc"), irr::core::stringc((int)char_info.AccountId));
		add_char.setVar(irr::core::stringc("$name"), char_info.Name);
		add_char.setVar(irr::core::stringc("$race"), irr::core::stringc((int)char_info.RaceId));
		add_char.setVar(irr::core::stringc("$class"), irr::core::stringc((int)char_info.ClassId));
		add_char.setVar(irr::core::stringc("$sex"), irr::core::stringc((int)char_info.Sex));
		add_char.setVar(irr::core::stringc("$hairt"), irr::core::stringc((int)char_info.HairType));
		add_char.setVar(irr::core::stringc("$hairc"), irr::core::stringc((int)char_info.HairColor));
		add_char.setVar(irr::core::stringc("$face"), irr::core::stringc((int)char_info.FaceType));
		interfaces->DataBase->query(add_char);
		return true;
	}
};

irr::u32 CPlayerCache::loadCharSelect(irr::u32 account_id)
{
	SGameServerInterfaces* interfaces = (SGameServerInterfaces*)Interfaces;
	irr::db::Query chars(irr::core::stringc("SELECT * FROM characters WHERE account_id = $acc"));
	chars.setVar(irr::core::stringc("$acc"), irr::core::stringc((int)account_id));
	irr::db::CQueryResult qr = interfaces->DataBase->query(chars);
	return 0;
};

SCharInfo* CPlayerCache::loadChar(irr::u32 account_id, irr::u32 char_index)
{
	return NULL;
};

SCharInfo* CPlayerCache::loadChar(irr::u32 char_id)
{
	return NULL;
};

void CPlayerCache::saveChar(irr::u32 char_id)
{
	
};

void CPlayerCache::garbageCollect(bool full_collect)
{
	
};

}
}
