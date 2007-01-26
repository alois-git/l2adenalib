/* 
 * CGc.h - Garbage collector.
 * Created January 21, 2007, by Michael 'Bigcheese' Spencer.
 */

#ifndef __IRR_GARBAGE_COLLECTOR_H_INCLUDED__
#define __IRR_GARBAGE_COLLECTOR_H_INCLUDED__

#include <irrCompileConfig.h>

enum GCPlacement
{
	UseGC,
	NoGC, 
	PointerFreeGC
};

namespace irr
{
namespace core
{
	class IRRCORE_API gc
	{
	public:

		gc();
		virtual ~gc();

		void* operator new( size_t size );
		void* operator new( size_t size, GCPlacement gcp );
		void* operator new( size_t size, void *p );
		void operator delete( void* obj );
		void* operator new[]( size_t size );
		void* operator new[]( size_t size, GCPlacement gcp );
		void* operator new[]( size_t size, void *p );
		void operator delete[]( void* obj );

		static void garbageCollect();

	private:
	};

}
}

#endif
