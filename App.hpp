#ifndef DELUGE_APP_HPP
#define DELUGE_APP_HPP

#include <PersistantSettings.hpp>

#include <zeno/Window/Window.hpp>

class App
{
public:
    static App& getInstance(void)
    {
        static App app;

        return app;
    }

    void run(int _argc, char **_argv);

    PersistantSettings& getSettings(void);

private:
    App(void);

    ~App(void);

    zeno::Window m_Window;

    bool m_Running;

    PersistantSettings m_Settings;
};

#define sApp            App::getInstance()
#define sSettings       App::getInstance().getSettings()

#endif //~ DELUGE_APP_HPP
