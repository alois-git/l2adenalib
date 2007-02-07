/*
 * CGeoData.h - GeoData.
 * Created January 28, 2007, by Michael 'Bigcheese' Spencer.
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
 *
 * The algorithms used in this class are based off of the L2j Geodata implementation.
 */

#ifndef _ADENA_C_GEO_DATA_H_
#define _ADENA_C_GEO_DATA_H_

#include <AdenaConfig.h>
#include <irrThread.h>
#include <vector3d.h>
#include <CReadFile.h>
#include <AVL.h>
#include <irrArray.h>
#include <irrMath.h>

namespace adena
{
namespace game_server
{

	class ADENALIB_API CGeoData
	{
	friend class GeoLoadThread;
	public:

		CGeoData();

		~CGeoData();

		void initGeoData(const char* geo_index_file);

		/*
		 * @param x: World x
		 * @param y: World y
		 * @param z: World z
		 * returns: World z corrected by geodata
		 */
		irr::s32 getHeight(irr::core::vector3df &loc);

		irr::core::vector3df moveCheck(irr::core::vector3df &origin, irr::core::vector3df &target);

	private:

		void loadRegion(irr::core::stringc &filename, irr::u32 x, irr::u32 y);

		/*
		 * @param x: Geo x
		 * @param y: Geo y
		 * returns: The region that it's in.
		 */
		inline irr::s16 getRegion(irr::s32 geo_x, irr::s32 geo_y);

		inline irr::s32 getBlock(irr::s32 pos);

		inline irr::s32 getCell(irr::s32 pos);

		/*
		 * @param x: Geo x
		 * @param y: Geo y
		 * @param z: World z
		 * returns: World z corrected by geodata
		 */
		irr::s32 pvtGetHeight(irr::s32 x, irr::s32 y, irr::s32 z);

		/*
		 * All non z params are in geodata cords
		 */
		bool canMoveNext(irr::s32 x, irr::s32 y, irr::s32 z, irr::s32 tx, irr::s32 ty, irr::s32 tz);

		inline bool checkNSEW(irr::s16 NSEW, irr::s32 x, irr::s32 y, irr::s32 tx, irr::s32 ty);

		inline irr::s32 sign(irr::s32 a);

		irr::core::threads::Mutex GeoIndexM;
		AVL<irr::u16, irr::core::array<irr::u32> > GeoIndex;
		irr::core::threads::Mutex GeoDataM;
		AVL<irr::u16, irr::c8*> GeoData;

	};

}
}

#endif
