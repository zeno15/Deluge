#include <PersistantSettings.hpp>

#include <fstream>
#include <iostream>

const std::string PersistantSettings::SettingsFileName = std::string("Settings.xml");
const zeno::Vector2u PersistantSettings::DefaultResolution = zeno::Vector2u(1280, 720);
const bool PersistantSettings::DefaultFullscreen = false;

PersistantSettings::PersistantSettings(void)
{

}
PersistantSettings::~PersistantSettings(void)
{

}


bool PersistantSettings::loadFromFile(void)
{
    std::ifstream settings;
    settings.open(SettingsFileName);

    bool returnValue = true;

    if (settings.good())
    {
        zeno::XML xml = zeno::XML();

        if (!xml.loadFromFile(SettingsFileName))
        {
            returnValue = false;

            recreateDefaultSettings();
        }
        else
        {
            loadSettingsFromXML(xml);
        }
    }
    else
    {
        returnValue = false;

        recreateDefaultSettings();
    }

    settings.close();

    return returnValue;
}
bool PersistantSettings::saveToFile(void)
{
    zeno::XML xml = zeno::XML();

    createSettingsXML(xml);

    xml.writeToFile(SettingsFileName);

    return true;
}

void PersistantSettings::setResolution(const zeno::Vector2u& _res)
{
    m_Resolution = _res;
}
zeno::Vector2u PersistantSettings::getResolution(void) const
{
    return m_Resolution;
}

void PersistantSettings::setFullscreen(bool _fullscreen)
{
    m_Fullscreen = _fullscreen;
}
bool PersistantSettings::getFullscreen(void) const
{
    return m_Fullscreen;
}

void PersistantSettings::recreateDefaultSettings(void)
{
    m_Resolution = DefaultResolution;
    m_Fullscreen = DefaultFullscreen;
}

void PersistantSettings::createSettingsXML(zeno::XML& _xml)
{
    _xml.addDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
    _xml.addElement("Settings");
    _xml.addElement("Resolution", {}, "/Settings/");
    _xml.addElement("x", {}, "/Settings/Resolution/");
    _xml.addContent(std::to_string(m_Resolution.x), "/Settings/Resolution/x/");
    _xml.addElement("y", {}, "/Settings/Resolution/");
    _xml.addContent(std::to_string(m_Resolution.y), "/Settings/Resolution/y/");
    _xml.addElement("Fullscreen", {}, "/Settings/");
    _xml.addContent(std::to_string(m_Fullscreen ? 1 : 0), "/Settings/Fullscreen/");
}

void PersistantSettings::loadSettingsFromXML(zeno::XML& _xml)
{
    //~ Get Resolution

    std::string xRes = _xml.getContent("/Settings/Resolution/x/");
    std::string yRes = _xml.getContent("/Settings/Resolution/y/");

    if (xRes != std::string() && yRes != std::string())
    {
        m_Resolution.x = std::stoul(xRes);
        m_Resolution.y = std::stoul(yRes);
    }
    else
    {
        m_Resolution = DefaultResolution;
    }

    //~ Get Fullscreen mode

    std::string fullscreen = _xml.getContent("/Settings/Fullscreen/");

    if (fullscreen != std::string())
    {
        m_Fullscreen = std::stoul(fullscreen) == 1;
    }
    else
    {
        m_Fullscreen = DefaultFullscreen;
    }
}