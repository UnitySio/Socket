#pragma once
#include "Singleton.h"

class DataManager : public Singleton<DataManager>
{
public:
    DataManager();
    virtual ~DataManager() override = default;

    void SetFloat(const std::string& kKey, float value);
    float GetFloat(const std::string& kKey, float default_value = 0.f);

};