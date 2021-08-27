#include"Tools.h"

//תΪutf8����
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

//�ַ���תwstring
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

//���ı���ת��
string Tools::TFChinese(const string& str)
{
	return WideByte2UTF8(StringToWString(str));
}

//�ַ����ָ�
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

//�ַ���ת����
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

//��ʽ��ʱ��
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
		result += to_string(hour) + " Сʱ ";
	}
	if (minute != 0)
	{
		result += to_string(minute) + " �� ";
	}
	if (second != 0)
	{
		result += to_string(second) + " �� ";
	}

	return result;
}

//��ʽ������
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
		result += to_string(km) + " ���� ";
	}
	if (m != 0)
	{
		result += to_string(m) + " �� ";
	}

	return result;
}