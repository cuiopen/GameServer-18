#include <cstdio>
#include <pthread.h>
#include "Base/Lock.h"

extern "C"
{
#include "3rd/lua/src/lua.h"
#include "3rd/lua/src/lualib.h"
#include "3rd/lua/src/lauxlib.h"
}

int main(int argc, char *argv[])
{
	lua_State *pLua = nullptr;
	pLua = luaL_newstate();
	luaL_openlibs(pLua);
	luaL_dofile(pLua, "./Scripts/hello.lua");
	lua_close(pLua);
	return 0;
}