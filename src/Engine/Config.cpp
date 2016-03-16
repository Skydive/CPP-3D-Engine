#include "Config.h"

#include <iostream>
#include <sstream>
#include <algorithm>

//#include <regex> No support... >:( I WILL NOT USE BOOST.

Config::Config(std::string file)
{
    BoundFile = File(CONFIG_DIR+file);
    ParseConfig();
}

bool Config::ParseConfig()
{
    KeyValues.clear();

    std::stringstream ss(BoundFile.FileData);
    std::string item;
    int line=1;
    while(std::getline(ss, item, '\n'))
    {

        std::stringstream ss(item);
        std::string key, value;
        // This is a comment!
        if(item.empty() || item[0] == ';')
            continue;

        std::getline(ss, key, '=');
        std::getline(ss, value, '=');

        key.erase(0, key.find_first_not_of(' '));
        key.erase(key.find_last_not_of(' ') + 1);
        value.erase(0, value.find_first_not_of(' '));
        value.erase(value.find_last_not_of(' ') + 1);

        if(!key.empty()  && !value.empty())
        {
            KeyValues[key] = value;
        }
        else
        {
            std::cout << "Config.cpp: " << BoundFile.FilePath << ": Line "
                      << line << ": has an invalid entry." << std::endl;
        }
        line++;
    }

    return true;
}

std::string Config::GetValueString(const std::string& key, std::string fallback)
{
    if(KeyValues.find(key) != KeyValues.end() )
    {
        return KeyValues[key];
    }
    return fallback;
}
bool Config::GetValueBool(const std::string& key, bool fallback)
{
    if(KeyValues.find(key) != KeyValues.end() )
    {
        std::string value = KeyValues[key];
        std::transform(value.begin(), value.end(), value.begin(), tolower);
        if(value == "true" || value == "false")
        {
            return (value == "true" ? true : false);
        }
    }
    return fallback;
}
float Config::GetValueFloat(const std::string& key, float fallback)
{
    if(KeyValues.find(key) != KeyValues.end())
    {
        return atof(KeyValues[key].c_str());
    }
    return fallback;
}
int Config::GetValueInt(const std::string& key, int fallback)
{
    if(KeyValues.find(key) != KeyValues.end())
    {
        return atoi(KeyValues[key].c_str());
    }
    return fallback;
}
