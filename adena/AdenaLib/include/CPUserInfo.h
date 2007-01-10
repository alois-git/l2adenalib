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

#include <CPacket.h>
#include <irrString.h>

namespace adena
{
namespace game_server
{

	class CPUserInfo : public CPacket
	{
	public:

		CPUserInfo()
		: CPacket()
		{
			resize(500);
			w8(0x04);

			w32(-71338); // x
			w32(258271); // y
			w32(-3104); // z
			w32(0x00); // Heading
			w32(0x00); // Char obj id
			wStrW(irr::core::stringc("test")); // Char name
			w32(0x00); // Race
			w32(0x00); // Sex
			w32(0x00); // Class

			w32(0x01); // Level
			w64(0x00); // XP
			w32(0x00); // STR
			w32(0x00); // DEX
			w32(0x00); // CON
			w32(0x00); // INT
			w32(0x00); // WIT
			w32(0x00); // MEN
			w32(0x00); // Max hp
			w32(0x00); // Current hp
			w32(0x00); // Max mp
			w32(0x00); // Current mp
			w32(0x00); // Sp
			w32(0x00); // Weight
			w32(0x00); // Max weight

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

			w32(0x00); // Patk
			w32(0x00); // Patk speed
			w32(0x00); // Pdef
			w32(0x00); // Evasion
			w32(0x00); // Accutacy
			w32(0x00); // Crit
			w32(0x00); // Matk

			w32(0x00); // Cast speed
			w32(0x00); // Atk speed

			w32(0x00); // Mdef

			w32(0x00); // Pvp state (0 = white, 1 = purple)
			w32(0x00); // Karma

			w32(200); // Run speed
			w32(100); // Walk speed
			w32(200); // Swim run speed
			w32(100); // Swim walk speed
			w32(0x00); // _flRunSpd
			w32(0x00); // _flWalkSpd
			w32(200); // Fly run speed
			w32(100); // Fly walk speed
			wf(0x00); // Move x
			wf(0x00); // Atk speed x

			wf(0x00); // Summon collision radius
			wf(0x00); // Summon collision height

			w32(0x00); // Hair style
			w32(0x00); // Hair color
			w32(0x00); // Face
			w32(0x00); // Builder lvl

			wStrW(irr::core::stringc("Adena!")); // Title

			w32(0x00); // Clan id
			w32(0x00); // Clan crest id
			w32(0x00); // Ally id
			w32(0x00); // Ally crest id
			w32(0x00); // siege-flags  0x40 - leader rights  0x20 - ??
			w8(0x00); // Mount type (0 = none, 1 = stryder, 2 = whyfren(sp?))
			w8(0x00); // Pvt store type (1 sell shop)
			w8(0x00); // Can craft?
			w32(1000); // Pks
			w32(0x00); // Pvps

			w16(0x00); // Cubics count.
			/*for()
				w16(cube id);*/

			w8(0x00); // 1-find party members?

			w32(0x00); // Abnormal effect (bit map)
			w8(0x00);

			w32(0x00); // Clan privs

			w16(0x00); // Recs left
			w16(0x00); // Recs have
			w32(0x00);
			w16(100); // Max invantory count

			w32(0x00); // Class id
			w32(0x00); // Effect arround player
	        
			w32(100); // Max cp
			w32(50); // Current cp
			w8(0x00); // Enchant lvl

			w8(0x00); // Team circle around feet (0 = none, 1 = blue, 2 = red)

			w32(0x00); // Clan crest lage id
			w8(0x00); // Symbol on char menu ctrl+I  
			w8(0x00); // Hero Aura?

			w8(0x00); // Fishing?
			w32(0x00); // Fish x
			w32(0x00); // Fish y
			w32(0x00); // Fish z
	        w32(0x00); // Name color
	        
       		w8(0x00); // Running?
	        
			w32(0x00); // Face obj id
	        
			w32(0x00); // Face item id
	        
			w32(0x00); // Clan class
			w32(0x00);
	        
			w32(0x00); // Title color
	        
			w32(0x00);
	        
			w32(0x00); // Cursed weapon lvl
		};

		virtual ~CPUserInfo()
		{

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



	};

}
}

#endif
