#include"Tools.h"

//转为utf8编码
string Tools::WideByte2UTF8(const wstring& text)

{

	int asciisize = ::WideCharToMultiByte(CP_UTF8, 0, text.c_str(), text.size(), NULL, 0, NULL, NULL);

	if (asciisize == ERROR_NO_UNICODE_TRANSLATION ||

		asciisize == 0)

	{

		return string();

	}

	char* resultstring = new char[asciisize];

	int convresult = ::WideCharToMultiByte(CP_UTF8, 0, text.c_str(), text.size(), resultstring, asciisize, NULL, NULL);

	if (convresult != asciisize)

	{

		return string();

	}

	string buffer(resultstring, convresult);

	delete[] resultstring;

	return buffer;

}

//字符串转wstring
wstring Tools::StringToWString(const string& str)
{
	setlocale(LC_ALL, "chs");
	const char* point_to_source = str.c_str();
	size_t new_size = str.size() + 1;
	wchar_t *point_to_destination = new wchar_t[new_size];
	wmemset(point_to_destination, 0, new_size);
	mbstowcs(point_to_destination, point_to_source, new_size);
	wstring result = point_to_destination;
	delete[]point_to_destination;
	setlocale(LC_ALL, "C");
	return result;
}

//中文编码转换
string Tools::TFChinese(const string& str)
{
	return WideByte2UTF8(StringToWString(str));
}

//字符串分割
MyQueue<string>* Tools::splitString(string str, char delim)
{
	MyQueue<string>* res = new MyQueue<string>;

	string s = "";

	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == delim)
		{
			res->append(s);
			s = "";
		}
		else
		{
			s += str[i];
		}
	}
	
	return res;
}

//字符串转整形
int Tools::stringToInt(string str)
{
	int result = 0;
	for (int i = 0; i < str.length(); i++)
	{
		result *= 10;
		result += str[i] - '0';
	}

	return result;
}

//格式化时间
string Tools::formatTime(int time)
{
	int hour = 0, minute = 0, second = time;
	string result = "";
	if (second > 60)
	{
		minute = second / 60;
		second = second % 60;

		if (minute > 60)
		{
			hour = minute / 60;
			minute = minute % 60;
		}
	}
	if (hour != 0)
	{
		result += to_string(hour) + " 小时 ";
	}
	if (minute != 0)
	{
		result += to_string(minute) + " 分 ";
	}
	if (second != 0)
	{
		result += to_string(second) + " 秒 ";
	}

	return result;
}

//格式化距离
string Tools::formatDistance(int distance)
{
	int km = 0, m = distance;
	string result = "";
	if (m > 1000)
	{
		km = m / 1000;
		m = m % 1000;
	}
	if (km != 0)
	{
		result += to_string(km) + " 公里 ";
	}
	if (m != 0)
	{
		result += to_string(m) + " 米 ";
	}

	return result;
}