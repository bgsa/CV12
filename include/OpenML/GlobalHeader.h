#pragma once

#if defined(WINDOWS) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
	#ifdef API_IMPORT
		#define API_INTERFACE __declspec(dllimport)		
	#else
		#ifdef API_EXPORT
			#define API_INTERFACE __declspec(dllexport)
		#endif
	#endif	
#else
	#define API_INTERFACE __attribute__((visibility("default")))
#endif 

#include <cmath>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;