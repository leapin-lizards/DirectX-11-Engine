#pragma once
#include <string>
class StringHelper {
public:
	static std::wstring StringToWide(std::string str);
	static std::string GetDirectoryFromPath(const std::string & path);
	static std::string GetFileExtension(const std::string & path);
};