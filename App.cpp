#include <App.hpp>

#include <Console.hpp>
#include <Sprite.hpp>

#include <zeno/Graphics/ShaderManager.hpp>
#include <zeno/Graphics/Font.hpp>
#include <zeno/Graphics/Text.hpp>
#include <zeno/System/Clock.hpp>

#include <GL/glew.h>

#include <iostream>

App::App(void) :
m_Running(false)
{
    if (!m_Settings.loadFromFile())
    {
        std::cout << "Failed to load settings, restoring defaults" << std::endl;
    }
    else
    {
        std::cout << "Loaded settings" << std::endl;
    }
}

App::~App(void)
{
    if (!m_Settings.saveToFile())
    {
        std::cout << "Failed to save settings" << std::endl;
    }
    else
    {
        std::cout << "Saved settings" << std::endl;
    }
}



void App::run(int _argc, char **_argv)
{
    m_Window.create(zeno::VideoMode(m_Settings.getResolution().x, m_Settings.getResolution().y), "Cuboid", zeno::WindowStyle::Titlebar | zeno::WindowStyle::Close);

    m_Window.setPosition(zeno::Vector2i(100, 100));
    glClearColor(100.0f / 255.0f, 149.0f / 255.0f, 247.0f / 255.0f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    zeno::Font font;
    font.loadFromFile("C:/Windows/Fonts/segoeui.ttf", 32);

    if (!zeno::ShaderManager::getInstance().addShader("Sprite", "Resources/Shaders/SpriteVertex.glsl", "Resources/Shaders/SpriteFragment.glsl"))
    {
        std::cout << "Failed Sprite shader" << std::endl;
    }
    if (!zeno::ShaderManager::getInstance().getShader("Sprite").getLocationOfUniform("View"))
    {
        std::cout << "Failed Sprite shader get loc of uniform View" << std::endl;
    }

    zeno::Texture texture;
    texture.loadFromFile("Resources/Textures/test.png");

    Sprite sprite;
    sprite.setTexture(&texture);
    sprite.addTextureRect(zeno::FloatRect(0.0f, 0.0f, 50.0f, 50.0f));
    sprite.addTextureRect(zeno::FloatRect(50.0f, 0.0f, 50.0f, 50.0f));
    sprite.addTextureRect(zeno::FloatRect(100.0f, 0.0f, 50.0f, 50.0f));
    sprite.addTextureRect(zeno::FloatRect(150.0f, 0.0f, 50.0f, 50.0f));
    sprite.setAnimationFrame(0);

    m_Running = true;
    zeno::Clock clock;

    zeno::Time t;
    unsigned int index = 0;

    while (m_Running)
    {
        zeno::Event event;
        while (m_Window.pollEvent(event))
        {
            sConsole.processEvent(event);

            if (event.type == zeno::Event::EventType::WindowClosed)
            {
                m_Running = false;
            }

        }

        t += clock.getElapsedTime();

        if (t.asSeconds() > 0.5f)
        {
            t -= zeno::Time::seconds(0.5f);
            index = (index + 1) % 4;
            sprite.setAnimationFrame(index);
        }

        m_Window.setTitle(std::string("Deluge FPS: " + std::to_string(1.0f / clock.restart().asSeconds())));

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //sprite.render(zeno::Mat4x4::Orthographic2D(0.0f, static_cast<float>(m_Settings.getResolution().x), static_cast<float>(m_Settings.getResolution().y), 0.0f));

        sConsole.render(zeno::Mat4x4::Orthographic2D(0.0f, static_cast<float>(m_Settings.getResolution().x), static_cast<float>(m_Settings.getResolution().y), 0.0f));

        m_Window.display();
    }

    m_Window.close();
}

PersistantSettings& App::getSettings(void)
{
    return m_Settings;
}