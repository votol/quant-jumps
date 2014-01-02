#ifndef __defs_h_
#define __defs_h_
	#define USE_DOUBLE
	#ifdef USE_DOUBLE
		#define TYPE double
	#else
		#define TYPE float
	#endif
    #include <vector>
    #include <map>
    #include <iterator>
    #include <iostream>
#endif
