/*
 * AdenaConfig.h - Compile config.
 * Created December 31, 2006, by Michael 'Bigcheese' Spencer.
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

#ifndef _ADENA_CONFIG_H_
#define _ADENA_CONFIG_H_

#include <IrrCompileConfig.h>
#include <irrTypes.h>
#include <irrMath.h>
#include <irrDb.h>
#include <memory.h>

// Version number is Major.Release.Revision
#define ADENA_VERSION "0.0.60"

#ifdef _IRR_WINDOWS_
#ifdef ADENALIB_EXPORTS
#define ADENALIB_API __declspec(dllexport)
#else
#define ADENALIB_API __declspec(dllimport)
#endif // ADENALIB_EXPORTS
#endif

#define MAP_MIN_X -131072
#define MAP_MAX_X 228608
#define MAP_MIN_Y -262144
#define MAP_MAX_Y 262144

// Max distance a player can see other pawns.
#define MAX_VIEW_DIST 2850

#endif
