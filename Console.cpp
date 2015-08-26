#include <Console.hpp>

#include <DelugeLua.hpp>


#include <iostream>

#define THICKNESS 2.0f

#define BACKSPACE 8
#define CTRL_BACKSPACE 127
#define PASTE 22

Console::Console(void) :
m_ConsoleBackground(zeno::Vector2f(720.0f, 32.0f), zeno::Vector2f(THICKNESS, THICKNESS)),
m_HasFocus(false),
m_HadFocus(false)
{
    m_ConsoleBackground.setOutlineThickness(THICKNESS);
    m_ConsoleBackground.setOutlineColour(zeno::Colour(0.5f, 0.5f, 0.5f, 1.0f));
    m_ConsoleBackground.setInternalColour(zeno::Colour(0.8f, 0.8f, 0.8f, 1.8f));

    m_Font.loadFromFile("C:/Windows/Fonts/segoeui.ttf", 24);

    m_ConsoleText.generateText("Example text", &m_Font);
    m_ConsoleText.setColour(zeno::Colour(0.0f, 0.0f, 0.0f, 1.0f));
}

Console::~Console(void)
{

}


void Console::processEvent(const zeno::Event& _event)
{
    if (_event.type == zeno::Event::EventType::KeyDown)
    {
        if (!m_HasFocus)
        {
            if (_event.key.key == zeno::Keyboard::Key::Tilde)
            {
                m_HasFocus = true;
            }
        }
        else if (_event.key.key == zeno::Keyboard::Key::Enter)
        {
            //~ Get text and close keyboard
            processInput(m_ConsoleCurrentText);
            m_ConsoleCurrentText.clear();
            m_HasFocus = false;
            m_HadFocus = false;
        }
    }
    else if (_event.type == zeno::Event::EventType::TextEntered)
    {
        if (m_HasFocus)
        {

            if (_event.text.character == BACKSPACE)
            {
                if (m_ConsoleCurrentText.size() != 0)
                {
                    m_ConsoleCurrentText.pop_back();
                }
            }
            else if (_event.text.character == CTRL_BACKSPACE)
            {
                //~ TODO make this work nicer
                m_ConsoleCurrentText.clear();
            }
            else if (_event.text.character == PASTE)
            {
                //~ TODO access clipboard
            }
            else if (m_HadFocus)
            {
                m_ConsoleCurrentText += _event.text.character;
            }

            m_ConsoleText.generateText(m_ConsoleCurrentText, &m_Font);

            m_HadFocus = true;
        }
    }
}

void Console::render(const zeno::Mat4x4& _transform) const
{
    if (m_HasFocus)
    {
        zeno::RenderData data;
        data.transform = _transform * zeno::Mat4x4::createTranslation(zeno::Vector3f(8.0f, 8.0f, 0.3f));
        m_ConsoleBackground.render(_transform);
        m_ConsoleText.render(data);
    }
}

void Console::setFocusState(bool _hasFocus)
{
    m_HasFocus = _hasFocus;
}

void Console::processInput(const std::string& _input)
{
    if (_input.size() == 0)
    {
        return;
    }

    sDLUA.handleCommand(_input);
}
