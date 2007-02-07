/*
 * CSkillInfoCache.h - Loads and caches the .xml skills.
 * Created February 1, 2007, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_C_SKILL_INFO_CACHE_H_
#define _ADENA_C_SKILL_INFO_CACHE_H_

#include <AdenaConfig.h>
#include <CFileSystem.h>
#include <irrXML.h>
#include <irrThread.h>
#include <irrString.h>
#include <irrArray.h>
#include <map>
#include <AVL.h>

namespace adena
{
namespace game_server
{
	struct SSkillInfo
	{
		irr::u32 Id;
		irr::u32 Levels;
		irr::core::stringc Name;
		irr::core::array<irr::u32> MpConsume;
		irr::core::array<irr::u32> Power;
		std::map<irr::core::stringc, irr::core::stringc> Data;
	};

	class ADENALIB_API CSkillInfoCache
	{
	public:

		CSkillInfoCache();

		~CSkillInfoCache();

		void init(const char* skill_dir);

		void addSkill(SSkillInfo* skill);

		void removeSkill(irr::u32 skill_id);

		SSkillInfo* getSkill(irr::u32 skill_id);

	private:

		void loadFile(const char* file_name);

		AVL<irr::u32, SSkillInfo*> Skills;

	};

}
}

#endif
