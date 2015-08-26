#ifndef DELUGE_DELUGELUA_HPP
#define DELUGE_DELUGELUA_HPP

#include <string>

class lua_State;

class DelugeLua
{
public:
    static DelugeLua& getInstance(void)
    {
        static DelugeLua dLua;

        return dLua;
    }

    void handleCommand(const std::string& _command);
    lua_State *m_L;

private:
    DelugeLua(void);
    ~DelugeLua(void);

private:

};

#define sDLUA DelugeLua::getInstance()

#endif //~ DELUGE_DELUGELUA_HPP
