#pragma once
#include "Object.h"

#include <string>
#include <fstream>
#include <iostream>

class File : public Object
{
public:
    File(const std::string& filepath)
    {
        FilePath = filepath;
        FileData = ReadFile(FilePath);
    }

    File(){}

    static std::string ReadFile(const std::string& filepath)
    {
        std::string filedata;
        std::ifstream File(filepath);
        if(File.is_open())
        {
            std::string line;
            while(std::getline(File, line))
            {
                filedata += line + "\n";
            }
            File.close();
        }
        else
        {
            std::cout << "Unable to open file: " << filepath << std::endl;
            return std::string();
        }
        return filedata;
    }
    std::string FileData;
    std::string FilePath;
};
