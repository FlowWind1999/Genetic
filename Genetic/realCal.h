#ifndef REALCAL_H 
#define REALCAL_H 
#include <iostream>
#include<cmath> 
#include<string>
#include<cctype>
using namespace std;
/* ����һ����ʽ�����ֵ��������Ӽ��˳����˷����׳ˣ����Ƿ�����*/
double cal(int s,int e,string str); 

long fact(long n) {     //��׳˵ĺ���
	if (n == 1 || n == 0)
		return 1;
	else
		return n*fact(n - 1);
}
//���ַ�ת������ֵ
double getvalue(int &s, int e, string str) {   
	double value=0;
	//���ȼ����������ֵ
	if (str[s] == '(' || str[s] == '[' || str[s] == '{')
	{
		int news, newe;    //new��ͷ��β
		news = s + 1;
		int i = 1;         //���������м���
		while (i)           //��i=0����
		{
			s++;
			if(s==e)
				break;
			if (str[s] == '(' || str[s] == '[' || str[s] == '{')
				i++;
			if (str[s] == ')' || str[s] == ']' || str[s] == '}')
				i--;
		}
		newe = s;
		s++;                     //ָ�����ŵĺ�һ������
		return cal(news, newe, str);
	}
	//�������Ǻ�����ֵ
	if (str[s] == 's')
	{
		s += 3;
		value = sin(getvalue(s, e, str)); 
	}
	if (str[s] == 'c')
	{
		s += 3;
		value = cos(getvalue(s, e, str));
	}
	if (str[s] == 't')
	{
		s += 3;
		value = tan(getvalue(s, e, str));
	}
	if (str[s] == 'a')
	{
		s+=3;
		if (str[s] == 's')
		{
			s += 3;
			value = asin(getvalue(s, e, str));
		}
		if (str[s] == 'c')
		{
			s += 3;
			value = acos(getvalue(s, e, str));
		}
		if (str[s] == 't')
		{
			s += 3;
			value = atan(getvalue(s, e, str));
		}
	}
	//ȷ��һ������ֵ
	if (isdigit(str[s]))   //�ж��Ƿ�������  ��������Ϊ�ܽ��뺯����s��ֵһ��С��e��
	{
		value = str[s]-'0';  //���ַ�ת��Ϊ����
		s++;                //���жϺ���������ֻ��Ǵ�����              
		while (s < e&&isdigit(str[s]))
		{
			value *=10;
			value += str[s] - '0';
			s++;
		}
		if (str[s] == '!')
		{
			value = fact(value);
			s++; 
		}
		if (str[s] == '.')
		{
			s++;
			int count = 1;
			double val2 = str[s] - '0';
			s++;
			while (s < e&&isdigit(str[s]))
			{
				val2 = val2 * 10 + str[s] - '0';
				s++;
				count++;
			}
			value = value + val2 / pow(10, count);
		}
	}
	return value;
}
// �˷�����������
double power(int &s, int e, string str) {
	double val;
	val=getvalue(s, e, str);
	if (s < e && str[s] == '^')
		val = pow(val, getvalue(++s, e, str));
	return val;
}
//���ͳ˵���������
double muldiv(int &s, int e, string str) { 
	double val;
	val= power(s, e, str);
	if (s < e && str[s] == '*')
		val *= power(++s, e, str);
	else if (s < e && str[s] == '/')
		val /= power(++s, e, str);
	else if(s < e && str[s] == '%') 
		val=(int)val%(int)power(++s, e, str);
	return val;
}
//ֻ��Ӽ���  �Ӽ����ĵȼ���������
double cal(int s, int e, string str) {
	double val=0;
	if (str[s] != '-')
		val = muldiv(s, e, str);
	while (s < e)
	{
		if (str[s] == '+')
			val += muldiv(++s, e, str);
		if (str[s] == '-')
			val -= muldiv(++s, e, str);
	}
	return val;
}
//����Ƿ��зǷ��ַ�
bool check(string str){
	for(int i=0;i!=str.size();++i){
		if(!(isdigit(str[i]) || str[i]=='!'|| str[i]=='s'||str[i]=='i'||str[i]=='n'||str[i]=='c'||
		str[i]=='o'||str[i]=='t'||str[i]=='a'||str[i]=='^'||str[i]=='+'||str[i]=='-'||
		str[i]=='*'||str[i]=='/'||str[i]=='.'||str[i]=='r'||str[i]=='%'||str[i]=='j'||str[i]=='('||
		str[i]==')'||str[i]=='['||str[i]==']'||str[i]=='{'||str[i]=='}'))
		{
			//cout<<"�д����ַ���"<<endl;
			exit(0);
			//return false;
		}
	}
	return true;
}
void eraseBlank(string &str){
	for(int i=0;i!=str.size();++i)
		if(isspace(str[i]))
			str.erase(str.begin()+i--);
}
#endif 
