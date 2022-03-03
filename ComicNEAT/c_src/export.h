

// Define EXPORTED for any platform
#ifdef _WIN32
# ifdef WIN_EXPORT
#   define EXPORTED  __declspec( dllimport)
# else
#   define EXPORTED  __declspec( dllexport  )
# endif
#else
# define EXPORTED
#endif
