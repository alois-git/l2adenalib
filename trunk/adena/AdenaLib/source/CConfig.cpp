/*
 * CConfig.cpp - Config file.
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

#include <CConfig.h>

namespace adena
{

CConfig::CConfig(const char* config_file)
{
	Ini = new BCini(config_file);
};

CConfig::~CConfig()
{

};

CConfig* CConfig::getInstance()
{
	static CConfig* instance = 0;

	if(!instance)
		instance = new CConfig("game.ini");

	return instance;
};

irr::core::stringc CConfig::getString(irr::core::stringc section, irr::core::stringc var)
{
	return (*Ini)[section.c_str()][var.c_str()].getData();
};

irr::s32 CConfig::getInt(irr::core::stringc section, irr::core::stringc var)
{
	return atoi((*Ini)[section.c_str()][var.c_str()].getData());
};

irr::f64 CConfig::getFloat(irr::core::stringc section, irr::core::stringc var)
{
	return atof((*Ini)[section.c_str()][var.c_str()].getData());
};

}
