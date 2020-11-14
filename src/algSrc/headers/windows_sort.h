#ifndef __SORT_H__
#define __SORT_H__

#include <windows.h>

#ifdef BUILD_DLL
	#define DLL_EXPORT __declspec(dllexport)
#else
	#define DLL_EXPORT __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C"
{
#endif

DLL_EXPORT void sort(int *arr, int size);

#ifdef __cplusplus
}
#endif

#endif