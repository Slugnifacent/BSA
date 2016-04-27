#include <stdio.h>

#if defined(DEBUG_LOG)
	#define LOG(x) printf("%s, %s, Line: %d, %s\n", __FILE__, __PRETTY_FUNCTION__, __LINE__,x);
#else 
	#define LOG(x)
#endif


#if defined(DEBUG_VERBOSE)
	#define VERBOSE(x) printf("%s, %s, Line: %d, %s\n", __FILE__, __PRETTY_FUNCTION__, __LINE__,x);
#else 
	#define VERBOSE(x)
#endif