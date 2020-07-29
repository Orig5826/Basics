#include <Windows.h>

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"


static int get_sum(lua_State* L)
{
	int n = lua_gettop(L);
	double sum = 0;
	int i;
	for (i = 1; i <= n; ++i) {
		if (!lua_isnumber(L, i)) {
			printf("invalid argument i=");
		}
		else {
			sum += lua_tonumber(L, i);
		}
	}
	lua_pushnumber(L, n);
	lua_pushnumber(L, sum);
	return 2;
}

int main()
{
	lua_State* L = luaL_newstate();
	// �򿪱�׼��
	luaL_openlibs(L);
	// ע�ắ��
	lua_register(L, "get_sum", get_sum);
	// ���ز�����
	luaL_dofile(L, "test.lua");
	lua_close(L);
	L = NULL;
	system("pause");
	return 0;
}
