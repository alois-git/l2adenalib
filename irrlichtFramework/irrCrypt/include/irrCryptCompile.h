#include <IrrCompileConfig.h>

#ifdef _IRR_WINDOWS_
#ifdef IRRCRYPT_EXPORTS
#define IRRCRYPT_API __declspec(dllexport)
#else
#define IRRCRYPT_API __declspec(dllimport)
#endif // IRRLICHT_EXPORT
#else
#define IRRCRYPT_API 
#endif // _IRR_WINDOWS_

#pragma warning(disable:4275)