/* 
 * CGc.h - Garbage collector.
 * Created January 22, 2007, by Michael 'Bigcheese' Spencer.
 */

#include <CGc.h>
#include <gc_local_alloc.h>

namespace irr
{
namespace core
{

gc::gc()
{

};

gc::~gc()
{

};

void gc::garbageCollect()
{
	GC_gcollect();
};

inline void* gc::operator new( size_t size )
{
    return GC_MALLOC( size );
};

inline void* gc::operator new( size_t size, GCPlacement gcp )
{
    if (gcp == UseGC) 
        return GC_MALLOC( size );
    else if (gcp == PointerFreeGC)
	return GC_MALLOC_ATOMIC( size );
    else
        return GC_MALLOC_UNCOLLECTABLE( size );
};

inline void* gc::operator new( size_t size, void *p )
{
    return p;
};

inline void gc::operator delete( void* obj )
{
    GC_FREE( obj );
};

inline void* gc::operator new[]( size_t size )
{
    return gc::operator new( size );
};

inline void* gc::operator new[]( size_t size, GCPlacement gcp )
{
    return gc::operator new( size, gcp );
};

inline void* gc::operator new[]( size_t size, void *p )
{
    return p;
};

inline void gc::operator delete[]( void* obj )
{
    gc::operator delete( obj );
};

}
}
