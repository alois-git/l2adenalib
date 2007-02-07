/*
 * CGeoData.cpp - GeoData.
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
 */

#include <CGeoData.h>
#include <fstream>
#include <os.h>

namespace adena
{
namespace game_server
{

	class GeoLoadThread : public irr::core::threads::Thread
	{
	public:

		GeoLoadThread(CGeoData* geo, irr::core::stringc filename, irr::u32 x, irr::u32 y)
		: Thread(), Geo(geo), Filename(filename), X(x), Y(y)
		{

		};

		~GeoLoadThread()
		{

		};

		virtual void run()
		{
			Geo->loadRegion(Filename, X, Y);
		};

	private:

		CGeoData* Geo;
		irr::core::stringc Filename;
		irr::u32 X;
		irr::u32 Y;

	};

CGeoData::CGeoData()
{

};

CGeoData::~CGeoData()
{

};

void CGeoData::initGeoData(const char* geo_index_file)
{
	puts("Building geodata...");
	std::fstream file(geo_index_file, std::ios::in);
	irr::c8 buff[256];
	irr::core::array<GeoLoadThread*> LoaderThreads;
	while(file >> buff)
	{
		irr::core::stringc fname(buff);
		irr::s32 place = fname.find("_");
		irr::core::stringc first = fname.subString(0, place);
		irr::core::stringc second = fname.subString(place + 1, fname.size());
		irr::u32 x = atoi(first.c_str());
		irr::u32 y = atoi(second.c_str());
		//loadRegion(fname + ".l2j", x, y);
		GeoLoadThread* glt = new GeoLoadThread(this, fname + ".l2j", x, y);
		glt->start();
		LoaderThreads.push_back(glt);
	}
	for(irr::u32 i = 0; i < LoaderThreads.size(); i++)
	{
		LoaderThreads[i]->wait();
		delete LoaderThreads[i];
	}
	puts("Done building geodata.");
};

irr::s32 CGeoData::getHeight(irr::core::vector3df &loc)
{
	return pvtGetHeight(((irr::s32)loc.X - MAP_MIN_X) >> 4, ((irr::s32)loc.Y - MAP_MIN_Y) >> 4, (irr::s32)loc.Z);
};

irr::core::vector3df CGeoData::moveCheck(irr::core::vector3df &origin, irr::core::vector3df &target)
{
	// Yes, i do know this is almost ezactly the l2j code...
	irr::s32 x = ((irr::s32)origin.X - MAP_MIN_X) >> 4;
	irr::s32 y = ((irr::s32)origin.Y - MAP_MIN_Y) >> 4;
	irr::s32 tx = ((irr::s32)target.X - MAP_MIN_X) >> 4;
	irr::s32 ty = ((irr::s32)target.Y - MAP_MIN_Y) >> 4;

	irr::s32 dx = (tx - x);
	irr::s32 dy = (ty - y);
	irr::f64 dz = (target.Z - origin.Z);
	irr::s32 distance = abs(dx + dy);

	if (distance == 0)
		return target;
	irr::s32 inc_x = sign(dx);
	irr::s32 inc_y = sign(dy);
	irr::f64 inc_z = dz / distance;
	irr::f64 dbl_inc_z = inc_z * 2;

	dx = abs(dx);
	dy = abs(dy);

	int next_x = x;
	int next_y = y;
	irr::f64 z = origin.Z;

	if (dx >= dy)// dy/dx <= 1
	{
		irr::s32 delta_A = 2 * dy;
		irr::s32 d = delta_A - dx;
		irr::s32 delta_B = delta_A - 2 * dx;

		for(irr::s32 i = 0; i <= dx; i++)
		{
    		x = next_x;
    		y = next_y;
    		if(d > 0)
    		{
    			z += dbl_inc_z;
    			d += delta_B;
    			next_x += inc_x;
    			if(!canMoveNext(x, y, z, next_x, next_y, target.Z))
				{
					return irr::core::vector3df((x << 4) + MAP_MIN_X, (y << 4) + MAP_MIN_Y, z);
				}
    			next_y += inc_y;
    			if(!canMoveNext(x, y, z, next_x, next_y, target.Z))
				{
					return irr::core::vector3df((x << 4) + MAP_MIN_X, (y << 4) + MAP_MIN_Y, z);
				}
    		}
    		else
    		{
    			z += inc_z;
    			d += delta_A;
    			next_x += inc_x;
    			if(!canMoveNext(x, y, z, next_x, next_y, target.Z))
				{
    				return irr::core::vector3df((x << 4) + MAP_MIN_X, (y << 4) + MAP_MIN_Y, z);
				}
    		}
		}
	}
	else
	{
		int delta_A = 2 * dx;
		int d = delta_A - dy;
		int delta_B = delta_A - 2 * dy;
		for(irr::s32 i = 0; i <= dy; i++)
		{
    		x = next_x;
    		y = next_y;
    		if(d > 0)
    		{
    			z += dbl_inc_z;
    			d += delta_B;
    			next_y += inc_y;
    			if(!canMoveNext(x, y, z, next_x, next_y, target.Z))
				{
					return irr::core::vector3df((x << 4) + MAP_MIN_X, (y << 4) + MAP_MIN_Y, z);
				}
    			next_x += inc_x;
    			if(!canMoveNext(x, y, z, next_x, next_y, target.Z))
				{
					return irr::core::vector3df((x << 4) + MAP_MIN_X, (y << 4) + MAP_MIN_Y, z);
				}
    		}
    		else
    		{
    			z += inc_z;
    			d += delta_A;
    			next_y += inc_y;
    			if(!canMoveNext(x, y, z, next_x, next_y, target.Z))
				{
					return irr::core::vector3df((x << 4) + MAP_MIN_X, (y << 4) + MAP_MIN_Y, z);
				}
    		}
		}
	}
	return target;
};

// ==== PVT ====

void CGeoData::loadRegion(irr::core::stringc &filename, irr::u32 x, irr::u32 y)
{
	//printf("Geodata - x: %d y: %d - loading...\n", x, y);
	irr::core::stringc fn("./geodata/");
	fn += filename;
	irr::io::CReadFile r(fn.c_str());
	irr::u16 region = ((x << 5) + y); // Convert the region number into a u16
	irr::c8* geo = new irr::c8[r.getSize()];
	r.read(geo, r.getSize()); // Load the whole file into memory
	if(r.getSize() > 196608) // If it's 196608 bytes long than it's just a simple z plane
	{
		irr::u32 block = 0;
		irr::u32 index = 0;
		irr::core::array<irr::u32> indexs;
		indexs.reallocate(128);
		while(block < 65536)
		{
			irr::u8 type = geo[index];
			indexs.push_back(index++);
			block++;
			if(type == 0) // 1 irr::u16.
			{
				index += 2;
			}else if(type == 1) // 64 irr::u16.
			{
				index += 128;
			}else // Layers.
			{
				for(irr::u32 i = 0; i < 64; i++)
				{
					irr::u8 layers = geo[index];
	                index += (layers << 1) + 1;
				}
			}
		}
		GeoIndexM.getLock();
		GeoIndex.Insert(region, indexs);
		GeoIndexM.releaseLock();
	}
	GeoDataM.getLock();
	GeoData.Insert(region, geo);
	GeoDataM.releaseLock();
};

irr::s16 CGeoData::getRegion(irr::s32 geo_x, irr::s32 geo_y)
{
	irr::s32 x = geo_x >> 11; // =/(256 * 8)
	irr::s32 y = geo_y >> 11;
	return (((x+16) << 5) + (y+10));
};

irr::s32 CGeoData::getBlock(irr::s32 pos)
{
	return (pos >> 3) % 256;
};

irr::s32 CGeoData::getCell(irr::s32 pos)
{
	return pos % 8;
};

irr::s32 CGeoData::pvtGetHeight(irr::s32 x, irr::s32 y, irr::s32 z)
{
	irr::u16 region = getRegion(x, y);
	irr::s32 blockX = getBlock(x);
	irr::s32 blockY = getBlock(y);
	irr::s32 cellX, cellY, index;
	irr::core::array<irr::u32> indexs;
	if(GeoIndex.Find(region, indexs))
	{
		// It's not a z plane
		index = indexs[((blockX << 8)) + (blockY)];
	}else
	{
		// It's a z plane
		index = ((blockX << 8) + blockY) * 3;
	}
	irr::c8* geo;
	if(!GeoData.Find(region, geo))
	{
		// No geodata for this location...
		return z;
	}else
	{
		irr::u8 type = geo[index++];
		if(type == 0)
		{
			irr::s16* height;
			height = (irr::s16*)(geo + index);
			return *height;
		}else if(type == 1)
		{
			cellX = getCell(x);
			cellY = getCell(y);
			index += ((cellX << 3) + cellY) << 1;
			irr::s16* th = (irr::s16*)(geo + index);
			irr::s16 height = *th;
			height = height & 0x0fff0;
			height = height >> 1; //height / 2
			return height;
		}else
		{
			cellX = getCell(x);
			cellY = getCell(y);
			irr::s32 offset = (cellX << 3) + cellY;
			while(offset > 0)
			{
				irr::u8 lc = geo[index];
				index += (lc << 1) + 1;
				offset--;
			}
			irr::u8 layers = geo[index];
			index++;
			if(layers <= 0 || layers > 125)
			{
				// Invailid layer count			
				return z;
			}
			irr::s16 temph = 0x8000;
			while(layers > 0)
			{
				irr::s16* th = (irr::s16*)(geo + index);
				irr::s16 height = *th;
				height = height & 0x0fff0;
				height = height >> 1; //height / 2
				if ((z - temph) * (z-temph) > (z - height) * (z - height))
					temph = height;
				layers--;
				index += 2;
			}
			return temph;
		}
	}
};

bool CGeoData::canMoveNext(irr::s32 x, irr::s32 y, irr::s32 z, irr::s32 tx, irr::s32 ty, irr::s32 tz)
{
	irr::s16 region = getRegion(x, y);
	irr::s32 blockX = getBlock(x);
	irr::s32 blockY = getBlock(y);
	irr::s32 cellX, cellY, index;
	irr::s16 NSEW = 0;
	irr::core::array<irr::u32> indexs;
	if(GeoIndex.Find(region, indexs))
	{
		// It's not a z plane
		index = indexs[((blockX << 8)) + (blockY)];
	}else
	{
		// It's a z plane
		index = ((blockX << 8) + blockY) * 3;
	}
	irr::c8* geo;
	if(!GeoData.Find(region, geo))
	{
		// No geodata for this location...
		return true;
	}else
	{
		irr::u8 type = geo[index++];
		if(type == 0)
		{
			return true;
		}else if(type == 1)
		{
			cellX = getCell(x);
			cellY = getCell(y);
			index += ((cellX << 3) + cellY) << 1;
			irr::s16* th = (irr::s16*)(geo + index);
			irr::s16 height = *th;
			NSEW = height & 0x0f;
		}else
		{
			cellX = getCell(x);
			cellY = getCell(y);
			irr::s32 offset = (cellX << 3) + cellY;
			while(offset > 0)
			{
				irr::u8 lc = geo[index];
				index += (lc << 1) + 1;
				offset--;
			}
			irr::u8 layers = geo[index];
			index++;
			if(layers <= 0 || layers > 125)
			{
				// Invailid layer count
				return false;
			}
			irr::s16 tempz = 0x8000;
			irr::s16 tempz2 = 0x8000;
			while(layers > 0)
			{
				irr::s16* th = (irr::s16*)(geo + index);
				irr::s16 height = *th;
				height = height & 0x0fff0;
				height = height >> 1; //height / 2

				if ((z - tempz) * (z - tempz) > (z - height) * (z - height))
				{
					tempz = height;
					th = (irr::s16*)(geo + index);
					NSEW = *th & 0x0f;
				}
				if ((tz - tempz2) * (tz - tempz2) > (tz - height) * (tz - height))
				{
					tempz2 = height;
				}
				layers--;
				index += 2;
			}
			if(tempz != tempz2)
				return false;
		}
	}
	return checkNSEW(NSEW, x, y, tx, ty);
};

bool CGeoData::checkNSEW(irr::s16 NSEW, irr::s32 x, irr::s32 y, irr::s32 tx, irr::s32 ty)
{
        //Check NSEW
	    if(NSEW == 15)
	       return true;
	    if(tx > x) // East
	    {
	    	if((NSEW & 1) == 0)
	            return false;
	    }
	    else if(tx < x) // West
	    {
	    	if((NSEW & 2) == 0)
	            return false;
	    }
	    if(ty > y) // South
	    {
	    	if((NSEW & 4) == 0)
	            return false;
	    }
	    else if(ty < y) // North
	    {
	    	if((NSEW & 8) == 0)
	            return false;
	    }
	    return true;
};

irr::s32 CGeoData::sign(irr::s32 a)
{
	if(a >= 0)
		return 1;
	return -1;
}


}
}
