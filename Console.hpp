#ifndef DELUGE_CONSOLE_HPP
#define DELUGE_CONSOLE_HPP

#include <zeno/Graphics/Font.hpp>
#include <zeno/Graphics/Rectangle.hpp>
#include <zeno/Graphics/Text.hpp>

#include <zeno/System/Event.hpp>
#include <zeno/System/Mat4x4.hpp>

#include <string>

class Console
{
public:
    static Console& getInstance(void)
    {
        static Console console;

        return console;
    }

    void processEvent(const zeno::Event& _event);

    void render(const zeno::Mat4x4& _transform) const;

    void setFocusState(bool _hasFocus);

    void processInput(const std::string& _input);

private:
    Console(void);

    ~Console(void);

    zeno::Rectangle m_ConsoleBackground;

    zeno::Text m_ConsoleText;

    zeno::Font m_Font;

    bool m_HasFocus;
    bool m_HadFocus;

    std::string m_ConsoleCurrentText;
};

#define sConsole Console::getInstance()

#endif //~ DELUGE_CONSOLE_HPP
