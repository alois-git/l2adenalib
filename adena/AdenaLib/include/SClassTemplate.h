/*
 * SClassTemplate.h - Class template.
 * Created January 7, 2007, by Michael 'Bigcheese' Spencer.
 *
 * Copyright (C) 2007 Michael Spencer
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
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
		irr::u32 Race; // L2 defined race id.
		irr::u32 ClassId; // L2 defined class id.
		irr::u32 BaseSTR;
		irr::u32 BaseDEX;
		irr::u32 BaseCON;
		irr::u32 BaseINT;
		irr::u32 BaseWIT;
		irr::u32 BaseMEN;
	};

}
}

#endif
