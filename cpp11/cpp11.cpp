#include "stdafx.h"
#include <stdio.h>
#include <regex>
#include <string>
#include <iostream>
using namespace std;

class urlDiv
{
public:
	urlDiv()
	{
		str = "";
		isUrl = true;
	}
	urlDiv(string s)
	{
		str = s + '#';
		isUrl = true;
	}
	void divStr()//C++0x风格
	{
		resL = 0;
		string tmp = "";	//暂存字符串
		bool hasC = false;	//是否出现':'
		//string tmpDiv = "";
		int i=0;
		while (i < str.length())
		{
			if ((str[i]<='z' && str[i]>='a')||(str[i]<='Z' && str[i]>='A')||(str[i]<='9' && str[i]>='0')||str[i]<0)		//数字字母或中文
			{
				tmp+=str[i];
			}else
			{
				if (str[i]==':')		//当前字符为':'判断
				{
					if (i<str.length()-2 && hasC==false)	//判断后两位是否为"//"
					{
						if (str[i+1]=='/' && str[i+2]=='/')
						{
							hasC = true;
							result[resL++] = tmp;
							tmp="";
							i+=2;
						}else
						{
							isUrl = false;
							return;
						}
					}else
					{
						isUrl = false;
						return;
					}
				}else if (str[i] == '-' || str[i] == '_')//-_正常连接
				{
					tmp+=str[i];
				}else if (str[i] == '.' || str[i] == '/' || str[i]=='#')//只用'.' '/' '#'分割，其中手动'#'是在字符串末尾加的，便于处理
				{
					if (tmp=="")//如果分隔符前是非法字符，则报错
					{
						isUrl = false;
						return;
					}
					result[resL++] = tmp;	//否则加入分隔结果中
					tmp = "";
				}else
				{
					char c=str[i];
					isUrl = false;
					return;
				}
			}
			i++;
		}
	}
	void divStrBySTL()//C++11 & STL风格，用lambda表达式实现
	{
		resL = 0;
		char s[100];	//与str相等的字符数组
		int i;
		string tmp="";
		string tmp2="";
		for (i=0;i<str.length();i++)
			s[i]=str[i];
		s[i]='\0';
		for_each(s,s+i,[&] (char c){
			if ((c<='z' && c>='a')||(c<='Z' && c>='A')||(c<='9' && c>='0')|| c<0 || c=='-' || c=='_')	//合法字符加入tmp中
			{
				tmp+=c;
				if (tmp2=="." || tmp2=="/" || tmp2=="://" || tmp2=="#" || tmp2=="")	//如果合法字符前分隔符非法，则报错
					tmp2="";
				else
					isUrl = false;
			}else 
			{
				tmp2+=c;
				if (tmp!="")	//tmp2为分隔符暂存字符串
				{
					result[resL++] = tmp;
					tmp="";
				}
			}
		});
	}
	void outputResult()//输出分隔结果
	{
		if (isUrl)
		{
			int i;
			for (i=0;i<resL-1;i++)
				cout<<result[i]<<',';
			cout<<result[i]<<endl;
		}else
			cout<<"is not a URL"<<endl;
	}
private:
	string str;		//输入字符
	bool isUrl;		//是否为合法URL
	string result[100];//存分隔结果
	int resL;		//结果数组长度
};

int _tmain(int argc, _TCHAR* argv[])
{
	string s = "http://msdn.microsoft.com/en-us/library/vstudio/啊哈.aspx";
	urlDiv *div = new urlDiv(s);
	div->divStr();		//使用c++0x风格分隔
	div->outputResult();	//使用c++11 & STL风格分隔
	div->divStrBySTL();
	div->outputResult();
	return 0;
}

