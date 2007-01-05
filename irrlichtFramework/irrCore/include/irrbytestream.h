/*
 * irrByteStream.h - Byte stream.
 * Created November 23, 2006, by Michael 'Bigcheese' Spencer.
 */

#ifndef __IRR_BYTE_STREAM_H_INCLUDED__
#define __IRR_BYTE_STREAM_H_INCLUDED__

#include <irrAllocator.h>

namespace irr
{

template <class T = u8, int grow_size = 8, typename TAlloc = core::irrAllocator<T> >
class ByteStream
{
public:

	ByteStream()
	: data(0), allocated(0), used(0), rptr(0)
	{
	}

	ByteStream(T* start_data, u32 start_len)
	: data(0), allocated(0), used(0), rptr(0)
	{
		wArray(start_data, start_len);
	}

	~ByteStream()
	{
		for(u32 i = 0; i < used; i++)
		{
			allocator.destruct(&data[i]);
		}
		allocator.deallocate(data);
	}

private:

	void reallocate(u32 new_size)
	{
		T* old_data = data;

		data = allocator.allocate(new_size);
		allocated = new_size;

		        // copy old data
		s32 end = used < new_size ? used : new_size;
		
		for (s32 i=0; i<end; ++i)
		{
			// data[i] = old_data[i];
			allocator.construct(&data[i], old_data[i]);
		}
		
        // destruct old data
		for (u32 j=0; j<used; ++j)
			allocator.destruct(&old_data[j]);

		if (allocated < used)
			used = allocated;

		allocator.deallocate(old_data); //delete [] old_data;
	}

protected:

	void checkSize(u32 data_size_to_add)
	{
		if(used + data_size_to_add > allocated)
		{
			reallocate(allocated + grow_size);
		}
	}

public:

	u32 getSize()
	{
		return used;
	}

	T* getData()
	{
		return data;
	}

	void w8(s32 val)
	{
		checkSize(sizeof(c8));
		data[used++] = (val & 0xff);
	}

	void w16(s32 val)
	{
		checkSize(sizeof(s16));
		data[used++] = (val & 0xff);
		data[used++] = ((val >> 8) & 0xff);
	}

	void w32(s32 val)
	{
		checkSize(sizeof(s32));
		data[used++] = (val & 0xff);
		data[used++] = ((val >> 8) & 0xff);
		data[used++] = ((val >> 16) & 0xff);
		data[used++] = ((val >> 24) & 0xff);
	}

	void wArray(T* Scr, u32 len)
	{
		for(int i = 0; i < len; i++)
		{
			w8(Scr[i]);
		}
	}

	s32 r8()
	{
		s32 result = (data[rptr++] & 0xff);
		return result;
	}

	s32 r16()
	{
		s32 result = (data[rptr++] & 0xff);
		result |= ((data[rptr++] << 8) & 0xff00);
		return result;
	}

	s32 r32()
	{
		s32 result = (data[rptr++] & 0xff);
		result |= ((data[rptr++] << 8) & 0xff00);
		result |= ((data[rptr++] << 16) & 0xff0000);
		result |= ((data[rptr++] << 24) & 0xff000000);
		return result;
	}

private:

	T* data;
	u32 allocated;
	u32 used;
	u32 rptr;
	TAlloc allocator;
};

}

#endif
