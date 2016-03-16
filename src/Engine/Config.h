#pragma once
#include "Object.h"

#include "File.h"

#include <map>

#define CONFIG_DIR "./cfg/"

//TODO: Somehow support writing.
//TODO: Link this with console manager
class Config : public Object
{
public:
    Config(std::string file);
    Config();
    bool ParseConfig();

    //TODO: Template this somehow
    std::string GetValueString(const std::string& key, std::string fallback);
    bool GetValueBool(const std::string& key, bool fallback);
    float GetValueFloat(const std::string& key, float fallback);
    int GetValueInt(const std::string& key, int fallback);

    std::map<std::string, std::string> KeyValues;
    File BoundFile;
};
