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
	void divStr()//C++0x���
	{
		resL = 0;
		string tmp = "";	//�ݴ��ַ���
		bool hasC = false;	//�Ƿ����':'
		//string tmpDiv = "";
		int i=0;
		while (i < str.length())
		{
			if ((str[i]<='z' && str[i]>='a')||(str[i]<='Z' && str[i]>='A')||(str[i]<='9' && str[i]>='0')||str[i]<0)		//������ĸ������
			{
				tmp+=str[i];
			}else
			{
				if (str[i]==':')		//��ǰ�ַ�Ϊ':'�ж�
				{
					if (i<str.length()-2 && hasC==false)	//�жϺ���λ�Ƿ�Ϊ"//"
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
				}else if (str[i] == '-' || str[i] == '_')//-_��������
				{
					tmp+=str[i];
				}else if (str[i] == '.' || str[i] == '/' || str[i]=='#')//ֻ��'.' '/' '#'�ָ�����ֶ�'#'�����ַ���ĩβ�ӵģ����ڴ���
				{
					if (tmp=="")//����ָ���ǰ�ǷǷ��ַ����򱨴�
					{
						isUrl = false;
						return;
					}
					result[resL++] = tmp;	//�������ָ������
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
	void divStrBySTL()//C++11 & STL�����lambda���ʽʵ��
	{
		resL = 0;
		char s[100];	//��str��ȵ��ַ�����
		int i;
		string tmp="";
		string tmp2="";
		for (i=0;i<str.length();i++)
			s[i]=str[i];
		s[i]='\0';
		for_each(s,s+i,[&] (char c){
			if ((c<='z' && c>='a')||(c<='Z' && c>='A')||(c<='9' && c>='0')|| c<0 || c=='-' || c=='_')	//�Ϸ��ַ�����tmp��
			{
				tmp+=c;
				if (tmp2=="." || tmp2=="/" || tmp2=="://" || tmp2=="#" || tmp2=="")	//����Ϸ��ַ�ǰ�ָ����Ƿ����򱨴�
					tmp2="";
				else
					isUrl = false;
			}else 
			{
				tmp2+=c;
				if (tmp!="")	//tmp2Ϊ�ָ����ݴ��ַ���
				{
					result[resL++] = tmp;
					tmp="";
				}
			}
		});
	}
	void outputResult()//����ָ����
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
	string str;		//�����ַ�
	bool isUrl;		//�Ƿ�Ϊ�Ϸ�URL
	string result[100];//��ָ����
	int resL;		//������鳤��
};

int _tmain(int argc, _TCHAR* argv[])
{
	string s = "http://msdn.microsoft.com/en-us/library/vstudio/����.aspx";
	urlDiv *div = new urlDiv(s);
	div->divStr();		//ʹ��c++0x���ָ�
	div->outputResult();	//ʹ��c++11 & STL���ָ�
	div->divStrBySTL();
	div->outputResult();
	return 0;
}

