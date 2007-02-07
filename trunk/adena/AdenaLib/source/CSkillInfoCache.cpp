/*
 * CSkillInfoCache.cpp - Loads and caches the .xml skills.
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

#include <CSkillInfoCache.h>
#include <string.h>

namespace adena
{
namespace game_server
{

CSkillInfoCache::CSkillInfoCache()
{

};

CSkillInfoCache::~CSkillInfoCache()
{

};

void CSkillInfoCache::init(const char* skill_dir)
{
	irr::io::CFileSystem fs = irr::io::CFileSystem();
	fs.changeWorkingDirectoryTo(skill_dir);
	irr::io::IFileList* fl = fs.createFileList();
	irr::u32 count = fl->getFileCount();
	puts("Loading skill data");
	for(irr::u32 i = 0; i < count; i++)
	{
		loadFile(fl->getFileName(i));
	}
	puts("Skill data loaded");
};

void CSkillInfoCache::addSkill(SSkillInfo* skill)
{
	SSkillInfo* s;
	if(Skills.Find(skill->Id, s))
	{
		printf("Attempted to add skill that is already there - id: %d\n", skill->Id);
		delete skill;
	}else
	{
		Skills.Insert(skill->Id, skill);
	}
};

void CSkillInfoCache::removeSkill(irr::u32 skill_id)
{
	SSkillInfo* s;
	if(Skills.Find(skill_id, s))
	{
		Skills.Remove(skill_id);
		delete s;
	}
};

SSkillInfo* CSkillInfoCache::getSkill(irr::u32 skill_id)
{
	SSkillInfo* s;
	if(Skills.Find(skill_id, s))
		return s;
	return 0;
};

irr::core::array<irr::u32> parseTable(const char* data)
{
	irr::core::array<irr::u32> a = irr::core::array<irr::u32>();
	irr::u32 hold = 0;
	for(irr::u32 i = 0; i < strlen(data); i++)
	{
		if(data[i] == ' ' || data[i] == '\n' || data[i] == 0)
		{
			irr::core::stringc str(data + hold, i - hold);
			irr::u32 val = atoi(str.c_str());
			if(val == 0)
			{
				if(str.find("0") == -1)
					continue;
			}
			a.push_back(val);
			hold = i;
		}
	}
	return a;
};

void CSkillInfoCache::loadFile(const char* file_name)
{
	irr::io::IrrXMLReader* xml = irr::io::createIrrXMLReader(file_name);
	irr::u32 state = 0; // 0 = needs skill, 1 = inside skill
	irr::core::stringc nodename;

	while(xml && xml->read())
	{
		switch(xml->getNodeType())
		{
			case irr::io::EXN_ELEMENT:
				if(!strcmp("skill", xml->getNodeName()))
				{
					SSkillInfo* si = new SSkillInfo();
					si->Id = atoi(xml->getAttributeValue("id"));
					si->Levels = atoi(xml->getAttributeValue("levels"));
					si->Name = xml->getAttributeValue("name");
					while(xml->read())
					{
						// Load tables
						if(xml->getNodeType() == irr::io::EXN_ELEMENT)
						{
							if(!strcmp("table", xml->getNodeName()))
							{
								if(!strcmp("#mpConsume", xml->getAttributeValue("name")))
								{
									xml->read();
									si->MpConsume = parseTable(xml->getNodeData());
								}else if(!strcmp("#power", xml->getAttributeValue("name")))
								{
									xml->read();
									si->Power = parseTable(xml->getNodeData());
								} 
							}else if(!strcmp("set", xml->getNodeName()))
							{
								si->Data[xml->getAttributeValue("name")] = xml->getAttributeValue("val");
							}
						}else if(xml->getNodeType() == irr::io::EXN_ELEMENT_END)
						{
							break;
						}
					}
					addSkill(si);
				}
				break;
		}
	}

	delete xml;
};

}
}
