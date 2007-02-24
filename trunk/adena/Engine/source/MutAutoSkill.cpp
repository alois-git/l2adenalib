/*
 * MutAutoSkill.cpp - Automaticly adds skils to a player when they lvl up.
 * Created February 10, 2007, by Michael 'Bigcheese' Spencer.
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

#include <MutAutoSkill.h>

namespace adena
{
namespace game_server
{

extern "C"{
REG_EXPORT COObject* load_MutAutoSkill(IOObjectSystem* obj_sys)
{
	return (COObject*)new MutAutoSkill(obj_sys);
}
}

MutAutoSkill::MutAutoSkill(IOObjectSystem* obj_sys)
: Mutator(obj_sys)
{

};

MutAutoSkill::~MutAutoSkill()
{

};

void MutAutoSkill::playerLevelUp(Player* p)
{
	p->CharInfo->Skills = p->Owner->Server->Interfaces.SkillTreeCache->getSkillsForPlayer(p->CharInfo->ClassId, p->getLevel());

	Mutator::playerLevelUp(p); // Calls next mut in list
};

}
}
