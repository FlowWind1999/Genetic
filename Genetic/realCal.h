#ifndef REALCAL_H 
#define REALCAL_H 
#include <iostream>
#include<cmath> 
#include<string>
#include<cctype>
using namespace std;
/* 输入一行算式计算出值，可以算加减乘除，乘方，阶乘，三角反三角*/
double cal(int s,int e,string str); 

long fact(long n) {     //算阶乘的函数
	if (n == 1 || n == 0)
		return 1;
	else
		return n*fact(n - 1);
}
//将字符转化成数值
double getvalue(int &s, int e, string str) {   
	double value=0;
	//优先计算括号里的值
	if (str[s] == '(' || str[s] == '[' || str[s] == '{')
	{
		int news, newe;    //new的头和尾
		news = s + 1;
		int i = 1;         //计数括号有几对
		while (i)           //当i=0跳出
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
		s++;                     //指向括号的后一个符号
		return cal(news, newe, str);
	}
	//计算三角函数的值
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
	//确定一个数的值
	if (isdigit(str[s]))   //判断是否是数字  （这里因为能进入函数，s的值一定小于e）
	{
		value = str[s]-'0';  //将字符转化为数字
		s++;                //再判断后面的是数字还是纯符号              
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
// 乘方的优先运算
double power(int &s, int e, string str) {
	double val;
	val=getvalue(s, e, str);
	if (s < e && str[s] == '^')
		val = pow(val, getvalue(++s, e, str));
	return val;
}
//除和乘的优先运算
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
//只算加减法  加减法的等级最低最后算
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
//检查是否有非法字符
bool check(string str){
	for(int i=0;i!=str.size();++i){
		if(!(isdigit(str[i]) || str[i]=='!'|| str[i]=='s'||str[i]=='i'||str[i]=='n'||str[i]=='c'||
		str[i]=='o'||str[i]=='t'||str[i]=='a'||str[i]=='^'||str[i]=='+'||str[i]=='-'||
		str[i]=='*'||str[i]=='/'||str[i]=='.'||str[i]=='r'||str[i]=='%'||str[i]=='j'||str[i]=='('||
		str[i]==')'||str[i]=='['||str[i]==']'||str[i]=='{'||str[i]=='}'))
		{
			//cout<<"有错误字符！"<<endl;
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
