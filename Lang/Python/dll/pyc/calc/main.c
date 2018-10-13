#include <Python.h>
#include <Windows.h>
#include "calc.h"

extern PyMODINIT_FUNC PyInit_calc_module(void);

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
	switch (fdwReason) {
	case DLL_PROCESS_ATTACH:
		//Py_Initialize();
		break;
	case DLL_PROCESS_DETACH:
		//Py_Finalize();
		break;
	}
	return TRUE;
}
