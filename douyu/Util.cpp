#include "Util.h"

Util::Util()
{
}
Util::~Util()
{
}
std::string Util::UnicodeToAscii(const std::wstring str)
{
	int	iTextLen = WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, NULL, 0, NULL, NULL);
	std::vector<char> vecText(iTextLen, '\0');
	::WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, &(vecText[0]), iTextLen, NULL, NULL);

	std::string strText = &(vecText[0]);

	return strText;
}

std::string Util::decode(std::string str)
{
	//先将UTF-8转换成Unicode
	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	std::wstring wString = conv.from_bytes(str);
	//在转换成string
	return Util::UnicodeToAscii(wString);
	
}

std::string Util::getValue(const std::string str,const std::string key)
{
	std::string::size_type  pos_s = str.find(key);
	if (pos_s == std::string::npos)
	{
		return "";
	}
	std::string::size_type  pos_e = str.find('/',pos_s);
	//std::cout << pos_s <<" :"<<pos_e<< std::endl;
	int offset = key.length() + 2;
	std::string res = str.substr(pos_s+offset, pos_e- offset-pos_s);
	//std::cout<<res<<std::endl;
	return res;
}