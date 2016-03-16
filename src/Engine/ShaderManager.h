#pragma once
#include "Shader.h"

#include <memory>
#include <vector>

class ShaderManager : public Object
{
public:
    template<class T> T* GetShader(std::string ShaderName)
    {
        for(auto& res : ShaderList)
        {
            T* ShaderObject = dynamic_cast<Shader*>(res.get());
            if(ShaderObject && ShaderObject->Name == ShaderName)
            {
                return ShaderObject;
            }
        }
        return nullptr;
    }
    bool ShaderExists(Shader* PassedShader);
    Shader* PrecacheShader(std::string ShaderName, Shader* PassedShader);
    void FreeShader(Shader* PassedShader);
    void FreeShader(std::string ShaderName);

private:
    std::vector<std::unique_ptr<Shader>> ShaderList;
};
