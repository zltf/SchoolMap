#ifndef TOOLS_H_
#define TOOLS_H_

#include<string>
#include"cocos2d.h"
#include"MyQueue.h"

using namespace std;

USING_NS_CC;

class Tools
{
public:
	static string TFChinese(const string& str);//����ת��Ϊ����ʾ��utf8����

	static MyQueue<string>* splitString(string str, char delim);//�и��ַ���

	static int stringToInt(string str);//�ַ���ת����

	static string formatTime(int time);
	static string formatDistance(int distance);
private:
	static string WideByte2UTF8(const wstring& text);
	static wstring StringToWString(const string& str);
};

#endif // !TOOLS_H_