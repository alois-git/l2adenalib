/*
 * CSkillTreeCache.cpp - Skill tree.
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

#include <CSkillTreeCache.h>
namespace adena
{
namespace game_server
{

CSkillTreeCache::CSkillTreeCache()
{

};

CSkillTreeCache::~CSkillTreeCache()
{

};

void CSkillTreeCache::init(irr::db::IDatabase* db)
{
	irr::db::Query q(irr::core::stringc("SELECT id, parent_id FROM class_list"));
	irr::db::CQueryResult qr = db->query(q);
	irr::u32 i;
	for(i = 0; i < qr.RowCount; i++)
	{
		irr::u32 id = atoi(qr[i]["id"].c_str());
		if(id >= ClassToBase.size())
		{
			ClassToBase.reallocate(id + 64);
			ClassToBase.set_used(id + 64);
		}
		ClassToBase[id] = atoi(qr[i]["parent_id"].c_str());
	}

	q = irr::db::Query(irr::core::stringc("SELECT * FROM skill_trees"));
	qr = db->query(q);
	for(i = 0; i < qr.RowCount; i++)
	{
		SSkillTree st;
		st.ClassId = atoi(qr[i]["class_id"].c_str());
		st.Id = atoi(qr[i]["skill_id"].c_str());
		st.MaxLevel = atoi(qr[i]["level"].c_str());
		st.MinLevel = atoi(qr[i]["min_level"].c_str());
		st.Sp = atoi(qr[i]["sp"].c_str());
		SkillTree.push_back(st);
	}
};

irr::core::array<SSkill> CSkillTreeCache::getSkillsForPlayer(irr::u32 class_id, irr::u32 level)
{
	irr::core::array<SSkill> temp;
	for(irr::u32 i = 0; i < SkillTree.size(); i++)
	{
		if(SkillTree[i].MinLevel <= level && isOfClass(class_id, SkillTree[i].ClassId))
		{
			// Look thru temp and see if one of a lower lvl is already there
			bool found = false;
			for(irr::u32 c = 0; c < temp.size(); c++)
			{
				if(SkillTree[i].Id == temp[c].Id)
				{
					if(SkillTree[i].MaxLevel > temp[c].Level)
					{
						temp[c].Level = SkillTree[i].MaxLevel;
						found = true;
					}
				}
			}
			if(!found)
			{
				SSkill s;
				s.Enchant = 0;
				s.Id = SkillTree[i].Id;
				s.Level = SkillTree[i].MaxLevel;
				temp.push_back(s);
			}
		}
	}
	return temp;
};

bool CSkillTreeCache::isOfClass(irr::u32 cur_class, irr::u32 needed_class)
{
	if(cur_class < ClassToBase.size())
	{
		if(cur_class == needed_class)
			return true;
		while(cur_class != -1)
		{
			cur_class = ClassToBase[cur_class];
			if(cur_class == needed_class)
				return true;
		}
	}

	return false;
};

}
}

