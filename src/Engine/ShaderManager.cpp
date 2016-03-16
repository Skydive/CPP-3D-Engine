#include "ShaderManager.h"
#include <algorithm>

bool ShaderManager::ShaderExists(Shader* PassedShader)
{
    bool bExists = false;
    for(auto& res : ShaderList)
    {
        if(PassedShader->Name == res->Name)
        {
            bExists = true;
        }
    }
    return bExists;
}

Shader* ShaderManager::PrecacheShader(std::string ShaderName, Shader* PassedShader)
{
    if(ShaderExists(PassedShader) || ShaderName.empty())
    {
        // TODO: Print an error?
        delete PassedShader; // Shame on me.
        return nullptr;
    }
    PassedShader->Name = ShaderName;
    ShaderList.push_back(std::unique_ptr<Shader>(PassedShader));
    return PassedShader;
}

void ShaderManager::FreeShader(Shader* PassedShader)
{
    ShaderList.erase(
        std::remove_if(
            ShaderList.begin(),
            ShaderList.end(),
            [&] (auto& res)
            {
                return PassedShader == res.get();
            }),
            ShaderList.end()
        );
}

void ShaderManager::FreeShader(std::string ShaderName)
{
    ShaderList.erase(
        std::remove_if(
            ShaderList.begin(),
            ShaderList.end(),
            [&] (auto& res)
            {
                return res->Name == ShaderName;
            }),
            ShaderList.end()
        );
}
