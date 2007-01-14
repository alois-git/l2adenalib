/*
 * CPUserInfo.h - User info.
 * Created January 8, 2007, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_C_P_USER_INFO_H_
#define _ADENA_C_P_USER_INFO_H_

#include <CServerPacket.h>
#include <irrString.h>
#include <SGameServerInterfaces.h>
#include <COPlayer.h>

namespace adena
{
namespace game_server
{

	class CPUserInfo : public CServerPacket
	{
	public:

		CPUserInfo(COPlayer* player)
		: CServerPacket(), Player(player)
		{
			Priority = EPP_HIGH;
		};

		virtual ~CPUserInfo() {};

		virtual bool writePacket()
		{
			SCharInfo* ci = Player->CharInfo;
			SClassTemplate* ct = Player->Client->Server->Interfaces.CharTemplates->loadTemplate(Player->CharInfo->ClassId);

			resize(500);

			w8(0x04); // Packet type

			w32(ci->x); // x
			w32(ci->y); // y
			w32(ci->z); // z
			w32(0x00); // Heading
			w32(ci->CharacterId); // Char obj id
			wStrW(ci->Name); // Char name
			w32(ci->RaceId); // Race
			w32(ci->Sex); // Sex
			w32(ci->ClassId); // Class

			w32(ci->Level); // Level
			w64(ci->xp); // XP
			w32(Player->getStr()); // STR
			w32(Player->getDex()); // DEX
			w32(Player->getCon()); // CON
			w32(Player->getInt()); // INT
			w32(Player->getWit()); // WIT
			w32(Player->getMen()); // MEN
			w32(Player->getMaxHp()); // Max hp
			w32(Player->getHp()); // Current hp
			w32(Player->getMaxMp()); // Max mp
			w32(Player->getMp()); // Current mp
			w32(0x00); // Sp
			w32(0x00); // Weight
			w32(ct->MAX_WEIGHT); // Max weight

			w32(0x28); // Unknown

			// Object id.
			w32(0x00); // Underware
			w32(0x00); // Rear
			w32(0x00); // Left rear
			w32(0x00); // Neckless
			w32(0x00); // Right ring
			w32(0x00); // Left ring
			w32(0x00); // Helmate
			w32(0x00); // Right hand
			w32(0x00); // Left hand
			w32(0x00); // Gloves
			w32(0x00); // Main armor
			w32(0x00); // Leggings
			w32(0x00); // Boots
			w32(0x00); // Back
			w32(0x00); // Left right hand
			w32(0x00); // Hair

			// Item id
			w32(0x00); // Underware
			w32(0x00); // Rear
			w32(0x00); // Left rear
			w32(0x00); // Neckless
			w32(0x00); // Right ring
			w32(0x00); // Left ring
			w32(0x00); // Helmate
			w32(0x00); // Right hand
			w32(0x00); // Left hand
			w32(0x00); // Gloves
			w32(0x00); // Main armor
			w32(0x00); // Leggings
			w32(0x00); // Boots
			w32(0x00); // Back
			w32(0x00); // Left right hand
			w32(0x00); // Hair

			w32(ct->P_ATK); // Patk
			w32(ct->P_SPD); // Patk speed
			w32(ct->P_DEF); // Pdef
			w32(ct->EVASION); // Evasion
			w32(ct->ACC); // Accutacy
			w32(ct->CRIT); // Crit
			w32(ct->M_ATK); // Matk
			w32(ct->M_SPD); // Cast speed
			w32(ct->P_SPD); // Atk speed
			w32(ct->M_DEF); // Mdef

			w32(0x00); // Pvp state (0 = white, 1 = purple)
			w32(0x00); // Karma

			w32(ct->RUN_SPEED); // Run speed
			w32(100); // Walk speed
			w32(ct->RUN_SPEED); // Swim run speed
			w32(100); // Swim walk speed
			w32(ct->RUN_SPEED); // _flRunSpd
			w32(0x00); // _flWalkSpd
			w32(ct->RUN_SPEED); // Fly run speed
			w32(100); // Fly walk speed
			wf(1); // Move x
			wf(1); // Atk speed x

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
			w32(0x00); // Builder lvl

			wStrW(ci->Title); // Title

			w32(0x00); // Clan id
			w32(0x00); // Clan crest id
			w32(0x00); // Ally id
			w32(0x00); // Ally crest id
			w32(0x00); // siege-flags  0x40 - leader rights  0x20 - ??
			w8(0x00); // Mount type (0 = none, 1 = stryder, 2 = whyfren(sp?))
			w8(0x00); // Pvt store type (1 sell shop)
			w8(ct->canCraft); // Can craft?
			w32(1000); // Pks
			w32(0x00); // Pvps

			w16(0x00); // Cubics count.
			//for()
			//	w16(cube id);

			w8(0x00); // 1-find party members?

			w32(0x00); // Abnormal effect (bit map)
			w8(0x00);

			w32(0x00); // Clan privs

			w16(0x00); // Recs left
			w16(0x00); // Recs have
			w32(0x00);
			w16(100); // Max invantory count

			w32(ci->ClassId); // Class id
			w32(0x00); // Effect arround player
	        
			w32(100); // Max cp
			w32(ci->cp); // Current cp
			w8(0x00); // Enchant lvl

			w8(0x00); // Team circle around feet (0 = none, 1 = blue, 2 = red)

			w32(0x00); // Clan crest lage id
			w8(0x00); // Symbol on char menu ctrl+I  
			w8(0x00); // Hero Aura?

			w8(0x00); // Fishing?
			w32(0x00); // Fish x
			w32(0x00); // Fish y
			w32(0x00); // Fish z
	        w32(0xffffff); // Name color - 0xrrggbb, rr = red, gg = green, bb = blue

       		w8(0x01); // Running?

			w32(0x00); // Face obj id

			w32(0x00); // Face item id

			w32(0x00); // Clan class
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

		COPlayer* Player;

	};

}
}

#endif
