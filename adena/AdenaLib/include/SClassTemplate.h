/*
 * SClassTemplate.h - Class template.
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

#ifndef _ADENA_S_CLASS_TEMPLATE_H_
#define _ADENA_S_CLASS_TEMPLATE_H_

#include <AdenaConfig.h>

namespace adena
{
namespace game_server
{

		struct SClassTemplate
		{
			irr::u8 ClassId;
			irr::core::stringc ClassName;
			irr::u8 RaceId;
			irr::u8 STR;
			irr::u8 CON;
			irr::u8 DEX;
			irr::u8 INT;
			irr::u8 WIT;
			irr::u8 MEN;
			irr::u32 P_ATK;
			irr::u32 P_DEF;
			irr::u32 M_ATK;
			irr::u32 M_DEF;
			irr::u32 P_SPD; // Atk speed
			irr::u32 M_SPD; // Cast speed
			irr::u32 ACC; // Acuracy
			irr::u32 CRIT; // Crit rate
			irr::u32 EVASION;
			irr::u32 RUN_SPEED;
			irr::u32 MAX_WEIGHT;
			irr::s32 x;
			irr::s32 y;
			irr::s32 z;
			irr::u8 canCraft;
			irr::f64 M_UNK1;
			irr::f64 M_UNK2;
			irr::f64 M_COL_R;
			irr::f64 M_COL_H;
			irr::f64 F_UNK1;
			irr::f64 F_UNK2;
			irr::f64 F_COL_R;
			irr::f64 F_COL_H;
			irr::u32 items1;
			irr::u32 items2;
			irr::u32 items3;
			irr::u32 items4;
			irr::u32 items5;
		};

}
}

#endif
