#include "STDEx.h"

void std::StringTrim(std::string& str)
{
    str.erase(std::remove_if(str.begin(), str.end(), [](unsigned char x) { return std::isspace(x); }), str.end());
}
