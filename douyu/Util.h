#pragma once

#include <iostream>
#include <codecvt>
#include "windows.h" 
#include<vector>
#include <string>

class Util
{
public:
	Util();
	~Util();

	static std::string decode(std::string str);
	static std::string UnicodeToAscii(const std::wstring str);
	static std::string getValue(const std::string str,const std::string key);


};

