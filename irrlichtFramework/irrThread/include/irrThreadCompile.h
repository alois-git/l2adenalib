#ifdef _IRR_WINDOWS_
#ifdef IRRTHREAD_EXPORTS
#define IRRTHREAD_API __declspec(dllexport)
#else
#define IRRTHREAD_API __declspec(dllimport)
#endif // IRRLICHT_EXPORT
#else
#define IRRTHREAD_API 
#endif // _IRR_WINDOWS_