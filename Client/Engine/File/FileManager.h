#pragma once
#include "Singleton.h"

#include <filesystem>

class FileManager : public Singleton<FileManager>
{
public:
    FileManager();
    virtual ~FileManager() override = default;

    static std::wstring GetCurrentPath();
    
};
