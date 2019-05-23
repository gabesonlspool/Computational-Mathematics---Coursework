#include <iostream>
#include <fstream>
#include "solver.h"
#include <cmath>


Solver::Solver(int n, double eps, double time_start, double time_target): 
	EPS(eps), phase_front_coord(0.0), GRID_SIZE(n), TIME_START(time_start), TIME_TARGET(time_target)

{
	
	H = (RIGHT_BOUND_X - LEFT_BOUND_X) / ((double) GRID_SIZE - 1);
	
	std::vector<double> tmp(GRID_SIZE + 2); // Для удобства добавим два фиктивных узла сетки
	for (int i = 1; i < GRID_SIZE + 1; ++i) {
		tmp[i] = StartingCondition((i - 1) * H);
	}
	tmp[0] = BorderingConditionAtLeftBound(0);
	tmp[GRID_SIZE + 1] = BorderingConditionAtRightBound(1);
	time_layers.push_back(tmp);
	// В начальный момент фазовый фронт находится на левом краю сетки
	phase_front.push_back(0);
	
}


void Solver::solve(const string& filename) {
	/* Солвер создает текстовый файл c именем filename ,в который записывает результаты подсчета
	 * в формате, требуемом для gnuplot */
		 
	int time_steps = floor((TIME_TARGET - TIME_START) / TAU);
	int n = 1;
	while (n < time_steps) {
		iterationStep(n);
		n++;
	}
		
	if (filename != "") {
		std::ofstream ofs(filename);
		if (!ofs.is_open())
			throw "Cannot open file '" + filename + "'";
		for (int i = 0; i < time_steps; i+=1000) {
			for (int j = 1; j <= phase_front[i]; j++) {
				ofs << j - 1 << " " << (j - 1) * H << " " << time_layers[i][j] << std::endl; 
			}
			ofs << std::endl << std::endl;
			for (int j = phase_front[i] + 1; j < GRID_SIZE + 1; j++) {
				ofs << j -1  << " " << (j - 1) * H << " " << time_layers[i][j] << std::endl; 
			}
			ofs << std::endl << std::endl;
		}
		ofs.close();
	}
}
