#include "stdafx.h"
#include "Individual.h"


Individual::Individual(unsigned long long variable/*=0*/)
	: variable(variable)
{
	fitness = 0.0;
	fitness_rate = 0.0;
	sum_fitness = 0.0;
}

Individual::~Individual()
{
}

unsigned long long Individual::getVariable() const
{
	return variable;
}

double Individual::getFitness() const
{
	return fitness;
}

double Individual::getFitness_rate() const
{
	return fitness_rate;
}

double Individual::getSum_fitness() const
{
	return sum_fitness;
}

void Individual::chageFitness(double fitness)
{
	this->fitness = fitness;
}

void Individual::changeFitness_rate(double fitness_rate)
{
	this->fitness_rate = fitness_rate;
}

void Individual::changeSum_fitness(double sum_fitness)
{
	this->sum_fitness = sum_fitness;
}
