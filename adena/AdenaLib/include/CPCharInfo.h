/*
 * CPCharInfo.h - Char info ftw.
 * Created January 7, 2007, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_C_P_CHAR_INFO_H_
#define _ADENA_C_P_CHAR_INFO_H_

#include <CServerPacket.h>

namespace adena
{
namespace game_server
{

	class CPCharInfo : public CServerPacket
	{
	public:

		CPCharInfo(Player* player)
		: CServerPacket(), P(player)
		{
			Priority = EPP_HIGH;
		};

		virtual ~CPCharInfo()
		{

		};

		virtual bool writePacket()
		{
			SCharInfo* ci = P->CharInfo;
			SClassTemplate* ct = P->Owner->Server->Interfaces.CharTemplates->loadTemplate(P->CharInfo->ClassId);

			w8(0x03);
			w32(P->Location.X); // x
			w32(P->Location.Y); // y
			w32(P->Location.Z); // z
			w32(0x00); // Heading
			w32(P->Id); // Char object id
			wStrW(ci->Name); // Char name
			w32(ci->RaceId); // Race
			w32(ci->Sex); // Sex
			w32(ci->ClassId); // Class

			// item ids
			w32(0x00); // Underware
			w32(0x00); // Helmate
			w32(0x00); // Right hand
			w32(0x00); // Left hand
			w32(0x00); // Gloves
			w32(0x00); // Chest
			w32(0x00); // Leggings
			w32(0x00); // Boots
			w32(0x00); // Back
			w32(0x00); // Gloves
			w32(0x00); // Hair

			w32(0x00); // Pvp status
			w32(0x00); // Karma

			w32(ct->M_SPD); // Cast speed
			w32(P->getAttackSpeed()); // Atk speed

			w32(0x00); // Pvp status
			w32(0x00); // Karma

			w32(P->getSpeed()); // Run speed
			w32(100); // Walk speed
			w32(P->getSpeed());  // Swim run speed
			w32(100);  // Swin walk speed
			w32(P->getSpeed()); // _flRunSpd
			w32(0x00); // _flWalkSpd
			w32(P->getSpeed()); // Fly run speed
			w32(100); // Fly walk speed
			wf(1.0); // Move speed x
			wf(1.0); // Atk speed x
			if(ci->Sex == 0)
			{
				wf(ct->M_COL_R); // Collision radius
				wf(ct->M_COL_H); // Collision height
			}else
			{
				wf(ct->F_COL_R); // Collision radius
				wf(ct->F_COL_H); // Collision height
			}

			w32(ci->HairType); // Hair style
			w32(ci->HairColor); // Hair color
			w32(ci->FaceType); // Face

			wStrW(ci->Title); // Title
			w32(0x00); // Clan id
			w32(0x00); // Clan crest id
			w32(0x00); // Ally id
			w32(0x00); // Ally crest id
			w32(0);	// Seige flags

			w8(0x01); // Standing
			w8(0x01); // Running
			w8(0x00); // Combat
			w8(P->isLooksDead() ? 1 : 0); // Dead

			w8(0x00); // Invisable
			w8(0x00); // Mount type (0 = none, 1 = stryder, 2 = whyfren(sp?))
			w8(0x00); // Pvt store type (1 sell shop)

			w16(0x00); // Cubics count.
			/*for()
				w16(cube id);*/

			w8(0x00); // Find party members

			w32(0x00); // Abnormal effect (bit map)

			w8(0x00); // Recs left
			w16(0x00); // Recs have
			w32(ci->ClassId); // Class id

			w32(P->getMaxCp()); // Max cp
			w32(P->getCp()); // Current cp
	        w8(0x00); // Enchant effect

	        w8(0x00); // Team circle around feet (0 = none, 1 = blue, 2 = red)

			w32(0x00); // Clan crest lage id
			w8(0x00); // Symbol on char menu ctrl+I  
			w8(0x00); // Hero Aura
			
			w8(0x00); // Fishing
			w32(0x00); // Fish x
			w32(0x00); // Fish y
			w32(0x00); // Fish z
			w32(0xffffff); // Name color - 0xrrggbb, rr = red, gg = green, bb = blue
	        
	        w32(0x00);
	        
	        w32(0x00); // Item id face
	        
	        w32(0x00);  // Clan class
	        w32(0x00);
	        
	        w32(0x00); // Title color
	        
	        w32(0x00);
	        
	        w32(0x00); // Cursed weapon lvl
			return true;
		};

		virtual irr::c8* getData()
		{
			return Data;
		};

		virtual irr::u32 getLen()
		{
			return WritePointer;
		};

	private:

		Player* P;

	};

}
}

#endif
