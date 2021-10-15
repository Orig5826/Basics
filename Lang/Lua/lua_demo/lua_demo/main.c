#include <Windows.h>
#include <stdint.h>

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
	int count = 0;

	lua_State* L = luaL_newstate();
	if (L == NULL)
	{
		printf("LuaL_newstate Failed!\n");
		exit(-1);
	}
	// �򿪱�׼��
	luaL_openlibs(L);

	// ע�ắ�����ṩ���ű�����
	{
		lua_register(L, "get_sum", get_sum);
	}

	while (1)
	// 1. ���ؽű���ִ��
	// 2. ���ú���
	{
		int data = 15;
		int result = 0;

		count++;
		printf("---------- [%d] ----------\n",count);
		if (luaL_dofile(L, "test.lua"))
		{
			printf("luaL_dofile Failed!\n");
			exit(-1);
		}

		// �����Ĵ��κͷ���
		lua_getglobal(L, "echo");
		lua_pushnumber(L, data);
		lua_call(L, 1, 1);
		// lua_pcall(L, 1, 1, 0);           //! ���ַ�ʽ��ok
		result = (int)lua_tonumber(L, -1);
		if (!lua_isnumber(L, 1)) {
			printf("invalid result!");
			exit(-1);
		}
		lua_pop(L, 1);
		printf("[C] result = %d\n", result);

		Sleep(2000);
	}

	lua_close(L);
	L = NULL;
	system("pause");
	return 0;
}
