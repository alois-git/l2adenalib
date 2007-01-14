/*
 * COPlayer.cpp - A player.
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

#include <COPlayer.h>

namespace adena
{
namespace game_server
{

COPlayer::COPlayer(IGameServerClient* client)
: Client(client)
{

};

irr::u32 COPlayer::getLevel()
{
	irr::u32 maxlvl = atoi((*Client->Server->Interfaces.ConfigFile)["gameserver"]["max_level"].getData());
	irr::u32 minlvl = atoi((*Client->Server->Interfaces.ConfigFile)["gameserver"]["min_level"].getData());

	if(CharInfo->Level > maxlvl)
		CharInfo->Level = maxlvl;
	if(CharInfo->Level < minlvl)
		CharInfo->Level = minlvl;

	return CharInfo->Level;
};

irr::u32 COPlayer::getStr()
{
	SClassTemplate* ct = Client->Server->Interfaces.CharTemplates->loadTemplate(CharInfo->ClassId);
	return ct->STR;
};

irr::u32 COPlayer::getCon()
{
	SClassTemplate* ct = Client->Server->Interfaces.CharTemplates->loadTemplate(CharInfo->ClassId);
	return ct->CON;
};

irr::u32 COPlayer::getDex()
{
	SClassTemplate* ct = Client->Server->Interfaces.CharTemplates->loadTemplate(CharInfo->ClassId);
	return ct->DEX;
};

irr::u32 COPlayer::getInt()
{
	SClassTemplate* ct = Client->Server->Interfaces.CharTemplates->loadTemplate(CharInfo->ClassId);
	return ct->INT;
};

irr::u32 COPlayer::getWit()
{
	SClassTemplate* ct = Client->Server->Interfaces.CharTemplates->loadTemplate(CharInfo->ClassId);
	return ct->WIT;
};

irr::u32 COPlayer::getMen()
{
	SClassTemplate* ct = Client->Server->Interfaces.CharTemplates->loadTemplate(CharInfo->ClassId);
	return ct->MEN;
};

irr::u32 COPlayer::getHp()
{
	irr::u32 maxhp = getMaxHp();
	if(CharInfo->hp > maxhp)
		CharInfo->hp = maxhp; // No over hp
	return CharInfo->hp;
}

irr::u32 COPlayer::getMaxHp()
{
	// HP = ((Class Base HP*CON Modifier)*Buffs*Weapon Bonus)+Boost HP+Armor Bonus+M.Def. Bonus
	irr::f64 basehp = getBaseHpForClass(CharInfo->ClassId, CharInfo->Level);
	irr::f64 conmod = getConMod(getCon());
	return (irr::u32)(basehp * conmod);
}

irr::u32 COPlayer::getMp()
{
	irr::u32 maxmp = getMaxMp();
	if(CharInfo->mp > maxmp)
		CharInfo->mp = maxmp; // No over mp
	return CharInfo->mp;
};

irr::u32 COPlayer::getMaxMp()
{
	return 0;
};

irr::f64 _inline quadEqu(irr::f64 a, irr::f64 b, irr::f64 c, irr::f64 x)
{
	return ((a * (x * x)) + (b * x) + c);
}

irr::f64 _inline cubicEqu(irr::f64 a, irr::f64 b, irr::f64 c, irr::f64 d, irr::f64 x)
{
	return ((a * (x * x * x)) + (b * (x * x)) + (c * x) + d);
};

irr::f64 _inline getConMod(irr::u32 con)
{
	return cubicEqu(0.0000048694242, 0.0000608003, 0.0148674192, 0.4381339809, con);
};

irr::f64 _fastcall getBaseHpForClass(irr::u32 class_id, irr::u32 level)
{
	static irr::f64 table[119][80];
	static bool gened = false;

	if( !((class_id < 119) && (level < 81) && (level > 0)) )
		return 0;

	if(!gened)
	{
		gened = true;
		// Generate table
		irr::u32 i;
		for(i = 0; i < 80; i++)
		{
			table[0][i] = quadEqu(0.064990671, 11.63594781, 68.27948918, i + 1); // Human fighter
			table[1][i] = quadEqu(0.15, 26.85, -270, i + 1); // Warrior
			table[2][i] = quadEqu(0.19, 34.01, -620.4, i + 1); // Gladiator
			table[3][i] = quadEqu(0.21, 37.59, -795.6, i + 1); // Warlord
			table[4][i] = quadEqu(0.135, 25.165, -210.3, i + 1); // Human Knight
			table[5][i] = quadEqu(0.18, 32.22, -604.5, i + 1); // Paladin
			table[6][i] = quadEqu(0.18, 32.22, -604.5, i + 1); // DA
			table[7][i] = quadEqu(0.125, 22.375, -170.5, i + 1); // Rogue
			table[8][i] = quadEqu(0.1598791578, 28.6558902, -477.6100288, i + 1); // TH
			table[9][i] = quadEqu(0.17, 30.43, -564.7, i + 1); // HE
			table[10][i] = quadEqu(0.085, 15.215, 85.7, i + 1); // Human Mage
			table[11][i] = quadEqu(0.125, 22.375, -73.5, i + 1); // Human Wizard
			table[12][i] = quadEqu(0.175, 31.325, -511.5, i + 1); // Sorcerer
			table[13][i] = quadEqu(0.175, 31.325, -511.5, i + 1); // Necro
			table[14][i] = quadEqu(0.1889124205, 34.15301178, -647.4902592, i + 1); // Warlock
			table[15][i] = quadEqu(0.155, 27.745, -192.9, i + 1); // Cleric

			// Copy base class hp stats into higher class hp stats
			for(irr::u32 c = 0; c < 10; c++)
				memcpy(table[c], table[0], sizeof(irr::f64) * 19);
		}
	}

	return table[class_id][level - 1];
}

}
}
