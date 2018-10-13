%module calc_module

%{
#include <Windows.h>
#include "calc.h"
%}

%include <windows.i>
%include "calc.h"