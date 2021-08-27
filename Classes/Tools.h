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
	static string TFChinese(const string& str);//中文转换为可显示的utf8编码

	static MyQueue<string>* splitString(string str, char delim);//切割字符串

	static int stringToInt(string str);//字符串转数字

	static string formatTime(int time);
	static string formatDistance(int distance);
private:
	static string WideByte2UTF8(const wstring& text);
	static wstring StringToWString(const string& str);
};

#endif // !TOOLS_H_