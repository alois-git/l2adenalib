/*
 * CSkillTreeCache.h - Skill tree.
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

#ifndef _ADENA_C_SKILL_TREE_CACHE_H_
#define _ADENA_C_SKILL_TREE_CACHE_H_

#include <AdenaConfig.h>
#include <irrDb.h>
#include <irrThread.h>
#include <irrString.h>
#include <irrArray.h>
#include <map>
#include <AVL.h>
#include <SCharInfo.h>
#include <irrDb.h>

namespace adena
{
namespace game_server
{

	class ADENALIB_API CSkillTreeCache
	{
	public:

		CSkillTreeCache();

		~CSkillTreeCache();

		void init(irr::db::IDatabase* db);

		irr::core::array<SSkill> getSkillsForPlayer(irr::u32 class_id, irr::u32 level);

	private:

		struct SSkillTree
		{
			irr::u32 ClassId;
			irr::u32 Id;
			irr::u32 MaxLevel;
			irr::u32 Sp;
			irr::u32 MinLevel;
		};

		// Returns true if needed_class is a base class of cur_class.
		bool isOfClass(irr::u32 cur_class, irr::u32 needed_class);

		irr::core::array<irr::s32> ClassToBase;
		irr::core::array<SSkillTree> SkillTree;

	};

}
}

#endif
