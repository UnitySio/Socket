#include "pch.h"
#include "FileManager.h"

namespace fs = std::filesystem;

FileManager::FileManager()
{
}

std::wstring FileManager::GetCurrentPath()
{
    return fs::current_path().wstring();
}
