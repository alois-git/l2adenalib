#include <irrCompileConfig.h>

#ifdef _IRR_WINDOWS_
#ifdef IRRDB_EXPORTS
#define IRRDB_API __declspec(dllexport)
#else
#define IRRDB_API __declspec(dllimport)
#endif // IRRDB_EXPORTS
#else
#define IRRDB_API 
#endif // _IRR_WINDOWS_ 