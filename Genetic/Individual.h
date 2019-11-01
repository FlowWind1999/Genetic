#pragma once

class Individual
{
private:
	unsigned long long variable;
	double fitness;
	double fitness_rate;
	double sum_fitness;
public:
	Individual(unsigned long long variable=0);
	~Individual();
	unsigned long long getVariable() const;
	double getFitness() const;
	double getFitness_rate() const;
	double getSum_fitness() const;
	void chageFitness(double fitness);
	void changeFitness_rate(double fitness_rate);
	void changeSum_fitness(double sum_fitness);
};

