#pragma once

#undef UNICODE

#include <stdint.h>
#include <stdio.h>
#include <stdint.h>
#include <Windows.h>


#ifdef DLL_EXPORTS
#define DLL_DEF _declspec(dllexport)
#else
#define DLL_DEF _declspec(dllimport)
#endif

#define CALL	__stdcall
#define DLL_API  DLL_DEF CALL


extern uint32_t DLL_DEF g_num;

void DLL_API num_set(uint32_t n);
uint32_t DLL_API num_get(uint32_t n);
