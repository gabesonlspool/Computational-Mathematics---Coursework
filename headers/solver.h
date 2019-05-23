#ifndef SOLVER_H
#define SOLVER_H
#include "problem_statement.h"
#include <string>
#include <vector>

using std::vector;
using std::string;


class Solver {

public:
	
	Solver(int n, double eps, double time_start, double time_finish);
	void solve(const std::string & filename = ""); 
		
protected:

	std::vector<std::vector<double>> time_layers;
	std::vector<double> phase_front;

	double k_1 = ICE_HEAT_COND_COEFF / ICE_DENSITY / ICE_HEAT_CAPACITY;
	double k_2 = WATER_HEAT_COND_COEFF / WATER_DENSITY / WATER_HEAT_CAPACITY;
	
	double H;
	double TAU;
	double EPS;
	double phase_front_coord;
        double TIME_START;
	double TIME_TARGET;	
		
	int GRID_SIZE;
	int TIME_STEPS;
	
	virtual void iterationStep(int n) = 0;
	
};

#endif
