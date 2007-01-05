#include <IrrCompileConfig.h>

#ifdef _IRR_WINDOWS_
#ifdef IRRBIGNUM_EXPORTS
#define IRRBIGNUM_API __declspec(dllexport)
#else
#define IRRBIGNUM_API __declspec(dllimport)
#endif // IRRLICHT_EXPORT
#else
#define IRRBIGNUM_API 
#endif // _IRR_WINDOWS_