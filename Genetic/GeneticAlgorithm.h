#pragma once
#include "Individual.h"
#include "X_Range.h"
#include "realCal.h"
#include<random>
#include<vector>
#include<iostream>
#include<fstream>
#include<cmath>
#include<ctime>
#include<string>
#include<algorithm>
using namespace std;

double PI = 3.141592653589793;//定义一个不可改变的常量值PI
int Group_Size = 50;//种群规模
int Epoch = 150;//进化代数
double Ov_Probability = 0.750; //交叉概率
double Va_Probability = 0.005;//变异概率
int Length = 31;  //62位的二进制
unsigned long long Max = (1 << Length) - 1;  //在win编程（1<<62）溢出
string eval;
ofstream log_file("./log.txt");

X_Range *vrange;
vector<Individual> nowpopulation;//P(t)种群
vector<Individual> midpopulation;//中间种群，存放轮盘选择后的优秀个体
vector<Individual> nextpopulation;//P(t+1)种群
default_random_engine e(time(0));  //引擎，生成随机序列

string getString(double x){  //x可能是非正数
	bool flag=true;
	if (x < 0)
	{
		flag = false;
		x = -x;
	}
	long long front_part = x;
	double back_part = x - front_part;
	string f_part,b_part;
	int num;
	// 取整数部分
	while (front_part>0)
	{
		num = front_part % 10;
		f_part.push_back(char(num + '0'));
		front_part /= 10;
	}
	int size = f_part.size();
	for (int i = 0; i < size / 2; ++i)
	{
		swap(f_part[i], f_part[size - 1 - i]);
	}
	if (f_part == "")
		f_part = "0";
	//取小数部分
	while (back_part != 0)
	{
		back_part *= 10;
		num = back_part;   //此处为向下取整
		b_part.push_back(char(num + '0'));
		back_part = back_part - num;
	}
	if (!flag)
		f_part = "-" + f_part;
	if (b_part == "")
		return f_part;
	return f_part + "."+ b_part;
}

double f(double x) {
	string val = getString(x), real_eval;
	for (auto i : eval)
	{
		if (i == 'x')
			real_eval.append(val);
		else
			real_eval.push_back(i);
	}
	//cout << real_eval << endl;
	double res;
	if (check(real_eval))
	{
		res = cal(0, real_eval.size(), real_eval);
		//cout << res << endl;
	}
	return res;
	//return x*sin(3.14 * x) + 2.0;
	//return x*x;
}

double decode(unsigned long long x) {
	auto lower = vrange->getLower();
	auto upper = vrange->getUpper();
	return lower + 
		((upper - lower) / Max )* x;
}

void initialize() {
	//default_random_engine e(time(0));
	uniform_int_distribution<unsigned long long> u(0,Max);
	//初始化种群
	nowpopulation.clear();
	for (int i = 0; i != Group_Size; ++i)
	{
		Individual ind(u(e));
		nowpopulation.push_back(ind);
	}
	//cout << nowpopulation.size()<<endl;
}

void caculaFitness(bool put=false) {
	//算适应度
	double fitness;
	double maxfit;
	for (auto i = nowpopulation.begin();i!= nowpopulation.end();++i)
	{
		fitness = f(decode(i->getVariable()));
		i->chageFitness(fitness);
		if (i == nowpopulation.begin())
		{
			maxfit = fitness;
		}
		else
		{
			maxfit = max(maxfit, fitness);
		}
	}
	if (put)
	{
		cout << maxfit << endl;  //给出最好的适应度
		log_file << maxfit << endl;  //给出最好的适应度
	}
}

//算两个适应率
void calculaFitnessRate() {
	double sum=0.0;
	double temp;
	//cout << nowpopulation.size() << endl;
	for (auto i = nowpopulation.begin(); i != nowpopulation.end(); ++i)
	{
		sum += i->getFitness();  //适应度之和
		//cout << i->getFitness() <<endl;
	}
	//cout <<"sum is "<< sum<<endl;
	//算适应率
	for (auto i = nowpopulation.begin(); i != nowpopulation.end(); ++i)
	{
		temp = i->getFitness() / sum;
		i->changeFitness_rate(temp);  
	}
	//算适应率阶梯
	sum = 0.0;
	for (auto i = nowpopulation.begin(); i != nowpopulation.end(); ++i)
	{
		sum += i->getFitness_rate();
		i->changeSum_fitness(sum);
	}
}

//选择个体进入繁殖池
void seclect() {
	//default_random_engine e(time(0));
	uniform_real_distribution<double> u(0.0, 1.0); //0-1之间的小数
	for (int i = 0; i != Group_Size; ++i) 
	{
		double rate = u(e);	
		for (auto j=nowpopulation.begin();j!=nowpopulation.end();++j)
		{
			if (rate < j->getSum_fitness())
			{
				midpopulation.push_back(*j);
				break;
			}
		}
	}
	nowpopulation.clear();
}

//杂交
void crossing() {
	//default_random_engine e(time(0));  //引擎，生成随机序列
	uniform_real_distribution<double> ur(0.0, 1.0); //0-1之间的小数
	uniform_int_distribution<int> ui(1, Length-1); //62位的二进制数有61个交叉位置
	for (int i = 0; i < Group_Size; i=i+2)
	{
		auto rate = ur(e);
		if (rate < Ov_Probability)  //交叉概率
		{
			nextpopulation.push_back(midpopulation[i]);
			nextpopulation.push_back(midpopulation[i+1]);
			continue;
		}
		//cout << midpopulation.size() << endl;
		unsigned long long father = midpopulation[i].getVariable();
		unsigned long long mother = midpopulation[i + 1].getVariable();
		auto insert_place = ui(e);
		unsigned long long l1 = (father >> insert_place) << insert_place;
		auto r1 = father - l1;
		unsigned long long l2 = (mother >> insert_place) << insert_place;
		auto r2 = mother - l2;
		Individual son1(l1 + r2), son2(l2 + r1);
		nextpopulation.push_back(son1);
		nextpopulation.push_back(son2);
	}
	midpopulation.clear();
}

//变异
void variating() {
	//default_random_engine e(time(0));  //引擎，生成随机序列
	uniform_real_distribution<double> ur(0.0, 1.0); //0-1之间的小数
	uniform_int_distribution<int> ui(1, Length - 1); //选一个二进制位变异
	for (auto i = nextpopulation.begin();i!=nextpopulation.end();++i) 
	{
		auto rate = ur(e);
		if (rate < Va_Probability)
		{
			nowpopulation.push_back(*i);
			continue;
		}
		int variat_place = ui(e);
		unsigned long long n_var = (1 << variat_place);
		n_var = n_var ^ i->getVariable();
		Individual new_ind(n_var);
		nowpopulation.push_back(new_ind);
	}
	nextpopulation.clear();
}
double geneticAlgorithm(double lower,double upper) {
	eraseBlank(eval);
	if (upper < lower)
	{
		log_file << "error! upper must be bigger than lower!" << endl;
		exit(0);
	}

	log_file << "parameter" << endl;
	log_file << "Group_Size: " << Group_Size << endl;
	log_file << "Epoch: " << Epoch << endl;
	log_file << "Ov_Probability: " << Ov_Probability << endl;
	log_file << "Va_Probability: " << Va_Probability << endl;
	log_file << "lower: " << lower << "\tupper: " << upper << endl;
	log_file << "cal the max!" << endl;
	

	vrange = new X_Range(upper, lower);
	initialize();
	for (int i = 0; i != Epoch; ++i)
	{
		if (i % 5 == 0)
		{
			log_file << "epoch " << i << ", best fitness is :";
			caculaFitness(true);			
		}
		else
		{
			caculaFitness();
		}
		calculaFitnessRate();
		seclect();
		crossing();
		variating();
	}
	caculaFitness();
	auto maxfiness = nowpopulation[0].getFitness();
	double bestid = decode(nowpopulation[0].getVariable());
	for (auto i = nowpopulation.begin();i!=nowpopulation.end();++i)
	{
		auto fitness = i->getFitness();
		if (fitness > maxfiness)
		{
			maxfiness = fitness;
			bestid = decode(i->getVariable());
		}
	}
	log_file << "at the place " << bestid << endl;
	log_file << "max finess is " << maxfiness << endl;
	log_file.close();
	return maxfiness;
}
