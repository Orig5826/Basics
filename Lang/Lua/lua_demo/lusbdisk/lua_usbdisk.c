
#define DLL_EXPORTS
#include "usbdisk.h"

#include "lauxlib.h"
#include "lualib.h"
#include "lua.h"

#define BUFFER_SIZE_MAX    (4096+16)

/*
 * handle = usbdisk.open(symbolic_link)
 */
static int lua_usb_open(lua_State* L)
{
	HANDLE handle = NULL;
	uint8_t* symbolic = (uint8_t*)luaL_checkstring(L, 1);
	handle = usb_open(symbolic);
	lua_pushinteger(L, (lua_Integer)handle);
	return 1;
}

/*
 * bool = usbdisk.close(handle)
 */
static int lua_usb_close(lua_State* L)
{
	BOOL ret = FALSE;
	HANDLE handle = NULL;
	handle = (HANDLE)luaL_checkinteger(L, 1);
	ret = usb_close(handle);
	lua_pushboolean(L, ret);
	return 1;
}

/*
 * wrote_cnt = usbdisk.write(handle,table)
 *     param2 -> table or byte, usually the table
 */
static int lua_usb_write(lua_State* L)
{
	HANDLE handle = NULL;
	// 固定cmd
	uint8_t cmd = 0xff;
	uint8_t cmd_len = 1;
	uint8_t* sbuf = NULL;
	uint32_t slen = 0;

	uint32_t argn = 0;
	uint32_t wrote_cnt = 0;

	int32_t data = 0;
	uint8_t temp = 0;
	uint32_t i = 0;

	handle = (HANDLE)luaL_checkinteger(L, 1);
	if (lua_gettop(L) < 2)
	{
		return luaL_error(L, "invalid number of arguments");
	}

	for (argn = 2; argn <= (uint32_t)lua_gettop(L); argn++)
	{
		if (lua_type(L, argn) == LUA_TNUMBER)
		{
			data = (int)luaL_checkinteger(L, argn);

			if (data < 0 || data > 255)
			{
				return luaL_error(L, "invalid number of arguments");
			}
			temp = data;
			if (TRUE != usb_write(handle, &cmd, cmd_len, &temp, 1))
			{
				return luaL_error(L, "usb_write failed!");
			}

			wrote_cnt++;
		}
		else if(lua_istable(L,argn))
		{
			slen = (uint32_t)lua_rawlen(L, argn);

			sbuf = (uint8_t*)malloc(BUFFER_SIZE_MAX);
			if (sbuf == NULL)
			{
				return 0;
			}
			memset(sbuf, 0x00, BUFFER_SIZE_MAX);

			for (i = 0; i < slen; i++)
			{
				lua_rawgeti(L, argn, (lua_Integer)i + 1);
				data = (int)luaL_checkinteger(L, -1);
				lua_pop(L, 1);
				if (data < 0 || data > 255)
				{
					free(sbuf);
					return luaL_error(L, "numeric data must be from 0 to 255");
				}
				sbuf[i] = data;
			}
			if(TRUE != usb_write(handle, &cmd, cmd_len, sbuf, slen))
			{
				return luaL_error(L, "usb_write failed!");
			}

			wrote_cnt += i;
			if (i < slen)
				break;
			free(sbuf);
		}
		else
		{
			return luaL_error(L, "invalid arguments");
		}
	}

	lua_pushinteger(L, wrote_cnt);
	return 1;
}

/*
 * table = usbdisk.read(handle,size)
 */
static int lua_usb_read(lua_State* L)
{
	HANDLE handle = NULL;
	// 固定cmd
	uint8_t cmd = 0xff;
	uint8_t cmd_len = 1;
	uint8_t* rbuf = NULL;
	uint32_t rlen = BUFFER_SIZE_MAX;

	uint32_t size;
	// luaL_Buffer b;

	handle = (HANDLE)luaL_checkinteger(L, 1);
	if (lua_gettop(L) < 2)
	{
		return luaL_error(L, "invalid number of arguments");
	}
	size = (uint32_t)luaL_checkinteger(L, 2);
	if (size == 0)
	{
		return 0;
	}

	rbuf = (uint8_t*)malloc(BUFFER_SIZE_MAX);
	if (rbuf == NULL)
	{
		return 0;
	}
	memset(rbuf, 0x30, BUFFER_SIZE_MAX);
	if (TRUE != usb_read(handle, &cmd, cmd_len, rbuf, &rlen))
	{
		return luaL_error(L, "usb_read failed!");
	}

#if 0
	// return string
	luaL_buffinit(L, &b);
	for (uint32_t i = 0; i < rlen; i++)
	{
		luaL_addchar(&b, (char)rbuf[i]);
	}
	luaL_pushresult(&b);
#else
	// return table
	lua_newtable(L);
	for (uint32_t i = 0; i < rlen; i++)
	{
		// 需要注意的一点就是
		// lua的下标是从1开始的
		lua_pushnumber(L, i + 1);
		lua_pushinteger(L, (lua_Integer)rbuf[i]);
		lua_settable(L, -3);
	}
#endif

	free(rbuf);
	return 1;
}

static const struct luaL_Reg usbdisk[] = {
	{"open", lua_usb_open},
	{"close", lua_usb_close},
	{"write", lua_usb_write},
	{"read", lua_usb_read},
	{NULL, NULL},
};

/*
 * dll -> xxx.dll
 * lua -> require(xxx)
 * c -> luaopen_xxx
 */
int DLL_API luaopen_lusbdisk(lua_State* L)
{
	luaL_newlib(L, usbdisk);
	return 1;
}
