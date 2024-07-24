#pragma once

class Resource
{
public:
    Resource();
    virtual ~Resource() = default;

    virtual bool Load(const std::wstring& kPath) = 0;
    
};
