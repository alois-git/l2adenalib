/*
 * BCini.h - .ini file loader and creator.
 * Created April 07, 2006, by Michael 'Bigcheese' Spencer.
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
 * Useage:
 * BCini ini(test.ini)
 * ini["group"]["row"] = "value"; // Changes value or if not there, adds it.
 * ini.flush(); // Saves changes to file.
 */

#ifndef _BC_CLASS_BCINI_
#define _BC_CLASS_BCINI_

#include <AdenaConfig.h>
#include <fstream>
#include <exception>

#define BUFFSIZE 256

class ADENALIB_API Row{
private:
	char* key;
	char* data;
public:
	Row(const char* key, const char* data);
	~Row();

	char* getKey();
	char* getData();
	Row& operator = (int i);
	Row& operator = (const char* c);
};

class ADENALIB_API Group{
private:
	char* key;

	int size;
	int len;
	Row** rows;
	void growData();
public:
	Group(const char* key);
	~Group();
	Row* addRow(const char* key, const char* data);

	char* getKey();
	int getLen();
	Row& at(int i);
	Row& operator[] (const char* key);
};

class ADENALIB_API BCini{
private:
	std::fstream *file;
	char* name;

	int size;
	int len;
	Group** groups;
	void growData();
	Group* addGroup(const char* key);

	void parse();
public:
	BCini(const char* filename);
	~BCini();

	char* getName();
	int getLen();
	Group& at(int i);
	void flush();
	Group& operator[](const char* key);
};

ADENALIB_API std::ostream& operator << (std::ostream& stream, BCini& ini);
ADENALIB_API std::ostream& operator << (std::ostream& stream, Group& g);
ADENALIB_API std::ostream& operator << (std::ostream& stream, Row& r);

#endif // #ifndef _BC_CLASS_BCINI_