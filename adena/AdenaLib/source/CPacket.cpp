/*
 * CPacket.cpp - L2 login packet.
 * Created January 5, 2007, by Michael 'Bigcheese' Spencer.
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

#include <CPacket.h>

namespace adena
{

//================ Con/De structor ================

CPacket::CPacket()
: Data(0), DataLen(0), WritePointer(0), ReadPointer(0)
{

};

//--------------------------------

CPacket::~CPacket()
{
	if(Data)
		delete[] Data;
};

//================ Protected ================

void CPacket::resize(irr::u32 new_size)
{
	irr::c8* temp = Data;
	Data = new irr::c8[new_size];
	memcpy(Data, temp, irr::core::min_<irr::u32>(DataLen, new_size));
	if(temp)
		delete[] temp;
	DataLen = new_size;
};

//--------------------------------

void CPacket::blowfishPad()
{
	w32(0x00);

	int padding = WritePointer % 8;
	if (padding != 0)
	{
		for (int i = padding; i < 8; i++)
		{
			w8(0x00);
		}
	}
};

//================ Public ================
//================ Write ================

void CPacket::w8(irr::u32 val)
{
	if((WritePointer + 1) > DataLen)
		resize(WritePointer + GROW_SIZE);

	Data[WritePointer++] = (val & 0xff);
};

//--------------------------------

void CPacket::w16(irr::u32 val)
{
	if((WritePointer + 2) > DataLen)
		resize(WritePointer + GROW_SIZE);

	Data[WritePointer++] = (val & 0xff);
	Data[WritePointer++] = ((val >> 8) & 0xff);
};

//--------------------------------

void CPacket::w32(irr::u32 val)
{
	if((WritePointer + 4) > DataLen)
		resize(WritePointer + GROW_SIZE);

	Data[WritePointer++] = (val & 0xff);
	Data[WritePointer++] = ((val >> 8) & 0xff);
	Data[WritePointer++] = ((val >> 16) & 0xff);
	Data[WritePointer++] = ((val >> 24) & 0xff);
};

//--------------------------------

void CPacket::wStr(irr::core::stringc &str)
{
	if((WritePointer + str.size() + 1) > DataLen)
		resize(WritePointer + str.size() + 1);

	for(irr::s32 i = 0; i < str.size(); i++)
		Data[WritePointer++] = str[i];
	Data[WritePointer++] = 0x00;
};

//--------------------------------

void CPacket::wStrW(irr::core::stringw &str)
{
	if((WritePointer + (str.size() * 2) + 2) > DataLen)
		resize(WritePointer + (str.size() * 2) + 2);

	for(irr::s32 i = 0; i < str.size(); i++)
		w16(str[i]);
	w16(0x0000);
};

//--------------------------------

void CPacket::wArray(irr::c8* in_data, irr::u32 data_len)
{
	if((WritePointer + data_len) > DataLen)
		resize(WritePointer + data_len);

	for(irr::u32 i = 0; i < data_len; i++)
		w8(in_data[i]);
};

//================ Read ================

irr::u32 CPacket::r8()
{
	int result = Data[ReadPointer++] &0xff;
	return result;
};

//--------------------------------

irr::u32 CPacket::r16()
{
	int result = Data[ReadPointer++] &0xff;
	result |= ((Data[ReadPointer++] << 8) & 0xff00);
	return result;
};

//--------------------------------

irr::u32 CPacket::r32()
{
	int result = Data[ReadPointer++] &0xff;
	result |= ((Data[ReadPointer++] << 8) & 0xff00);
	result |= ((Data[ReadPointer++] << 16) & 0xff0000);
	result |= ((Data[ReadPointer++] << 24) & 0xff000000);
	return result;
};

//--------------------------------

void CPacket::rStr(irr::core::stringc &str)
{
	irr::u32 len = (irr::u32)strlen(Data + ReadPointer);
	for(irr::u32 i = 0; i < len; i++)
		str += Data[i];
	ReadPointer += len + 1;
};

//--------------------------------

void CPacket::rStrW(irr::core::stringw &str)
{
	// TODO
};

//--------------------------------

void CPacket::rArray(irr::c8* out_data, irr::u32 data_len)
{
	for(irr::u32 i = 0; i < data_len; i++)
		out_data[i] = Data[i + ReadPointer++];
};

}
