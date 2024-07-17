#include "pch.h"
#include "DataManager.h"

#include <Windows.h>

DataManager::DataManager()
{
}

void DataManager::SetFloat(const std::string& kKey, float value)
{
    HKEY hKey;
    if (RegCreateKeyEx(HKEY_CURRENT_USER, L"Software\\Game", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL) == ERROR_SUCCESS)
    {
        RegSetValueEx(hKey, std::wstring(kKey.begin(), kKey.end()).c_str(), 0, REG_DWORD, reinterpret_cast<const BYTE*>(&value), sizeof(float));
        RegCloseKey(hKey);
    }
}

float DataManager::GetFloat(const std::string& kKey, float default_value)
{
    HKEY hKey;
    if (RegOpenKeyEx(HKEY_CURRENT_USER, L"Software\\Game", 0, KEY_READ, &hKey) == ERROR_SUCCESS)
    {
        DWORD type;
        DWORD size = sizeof(float);
        float value;
        if (RegQueryValueEx(hKey, std::wstring(kKey.begin(), kKey.end()).c_str(), 0, &type, reinterpret_cast<BYTE*>(&value), &size) == ERROR_SUCCESS)
        {
            RegCloseKey(hKey);
            return value;
        }
        RegCloseKey(hKey);
    }
}