/*
 * CConfig.h - Config file.
 * Created February 9, 2007, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_C_CONFIG_H_
#define _ADENA_C_CONFIG_H_

#include <AdenaConfig.h>
#include <irrString.h>
#include <BCini.h>

namespace adena
{

	class ADENALIB_API CConfig
	{
	public:

		CConfig(const char* config_file);

		~CConfig();

		static CConfig* getInstance();

		irr::core::stringc getString(irr::core::stringc section, irr::core::stringc var);
		irr::s32 getInt(irr::core::stringc section, irr::core::stringc var);
		irr::f64 getFloat(irr::core::stringc section, irr::core::stringc var);

	private:

		BCini* Ini;

	};

}

#endif
