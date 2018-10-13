
#ifndef _CALC_H_
#define _CALC_H_

#include <Windows.h>

#define DLL_API	__declspec(dllexport)
#define CALL	__stdcall

DLL_API double CALL  py_get_squre(double);

#endif
