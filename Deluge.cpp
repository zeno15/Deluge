#include <App.hpp>

int main(int _argc, char **_argv)
{
    sApp.run(_argc, _argv);

    return EXIT_SUCCESS;
}

/*
#include <lua/lua.hpp>

int main(int _argc, char **_argv)
{
    lua_State *L = luaL_newstate();

    luaL_dostring(L, "a = 10 + 5");
    lua_getglobal(L, "a");
    int i = static_cast<int>(lua_tointeger(L, -1));
    std::cout << "i: " << i << std::endl;
    lua_close(L);

    return EXIT_SUCCESS;
}*/