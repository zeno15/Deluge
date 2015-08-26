#include <DelugeLua.hpp>

#include <lua/lua.hpp>

#include <iostream>

DelugeLua::DelugeLua(void)
{
    m_L = luaL_newstate();

    luaL_openlibs(m_L);

    lua_setglobal(m_L, "cpp_lua_func");
}

DelugeLua::~DelugeLua(void)
{
    lua_close(m_L);
}


void DelugeLua::handleCommand(const std::string& _command)
{
    std::cout << "Lua is executing: '" << _command << "'" << std::endl;

    luaL_dostring(m_L, _command.c_str());

}