#ifndef DELUGE_PERSISTANT_SETTINGS_HPP
#define DELUGE_PERSISTANT_SETTINGS_HPP


#include <zeno/System/Vector2.hpp>
#include <zeno/Utility/XML.hpp>

#include <string>

class PersistantSettings
{
public:
    PersistantSettings(void);
    ~PersistantSettings(void);

    bool loadFromFile(void);
    bool saveToFile(void);

    void setResolution(const zeno::Vector2u& _res);
    zeno::Vector2u getResolution(void) const;

    void setFullscreen(bool _fullscreen);
    bool getFullscreen(void) const;

private:
    void recreateDefaultSettings(void);

    void createSettingsXML(zeno::XML& _xml);

    void loadSettingsFromXML(zeno::XML& _xml);

private:
    static const std::string SettingsFileName;
    static const zeno::Vector2u DefaultResolution;
    static const bool DefaultFullscreen;

    zeno::Vector2u      m_Resolution;

    bool                m_Fullscreen;

};

#endif //~ DELUGE_PERSISTANT_SETTINGS_HPP
