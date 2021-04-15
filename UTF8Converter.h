#pragma once
#ifdef _WIN32
#include <string>
#include <windows.h>

class UTF8Converter
{
public:
    static std::string to_utf8(const wchar_t* buffer, int len);
    static std::string to_utf8(const std::wstring& str);
};
#endif
