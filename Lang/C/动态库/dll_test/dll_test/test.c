#define DLL_EXPORTS
#include "test.h"

static uint32_t s_num = 0;

uint32_t DLL_DEF g_num = 0;

void DLL_API num_set(uint32_t n)
{
	s_num = n;
}

uint32_t DLL_API num_get(uint32_t n)
{
	return s_num;
}
