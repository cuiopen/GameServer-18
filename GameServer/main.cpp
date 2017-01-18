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

	//��ʼ��lua
	pLua = luaL_newstate();

	//����lua������
	luaL_openlibs(pLua);

	//���нű��ļ�
	luaL_dofile(pLua, "./Scripts/hello.lua");

	//��ȡlua�е�showinfo����
	lua_getglobal(pLua, "showinfo");

	//�����޲�lua�������޷���ֵ
	lua_pcall(pLua, 0, 0, 0);

	const char *pstr = "I'm from c++!";
	lua_getglobal(pLua, "showstr");
	lua_pushstring(pLua, pstr);
	
	//����һ��������lua�������޷���ֵ
	lua_pcall(pLua, 1, 0, 0);

	lua_getglobal(pLua, "add");
	lua_pushinteger(pLua, 2);
	lua_pushinteger(pLua, 3);
	lua_pcall(pLua, 2, 1, 0);
	printf("lua add function return val is %lld\n", lua_tointeger(pLua, -1));

	lua_close(pLua);
	return 0;
}