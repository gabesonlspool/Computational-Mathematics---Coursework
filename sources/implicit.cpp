#include <cmath>
#include <vector>
#include "implicit.h"


using std::vector;


Implicit::Implicit(int n, double eps, double time_start, double time_target): Solver(n, eps, time_start, time_target) {
	TAU = 0.1;
}
	
		
void Implicit::iterationStep(int n) {
				
	vector<double> new_time_layer(GRID_SIZE + 2);
	new_time_layer[0] = new_time_layer[1] = BorderingConditionAtLeftBound(TAU * n);
	new_time_layer[GRID_SIZE + 1] = new_time_layer[GRID_SIZE] = BorderingConditionAtRightBound(TAU * n);
	int border = (int) floor(phase_front_coord / H) + 1;
	new_time_layer[border] = 273.0;
		
	phase_front.push_back(border);
				
	/* Для неявной схемы получается СЛАУ с трехдиагональной матрицей, которую можно
	 * решить методом прогонки за линейное время*/
		 
	vector<double> alpha(GRID_SIZE + 2);
	vector<double> beta(GRID_SIZE + 2);
		
	alpha[2] = - a / b(2); 
	beta[2]  = (d(2) - c * new_time_layer[1]) / b(2);
				
	for (int i = 3; i < border; ++i) {
		alpha[i] =  - a / (b(i) + c * alpha[i - 1]);
		beta[i]  =  (d(i) - c * beta[i - 1]) / (b(i) + c * alpha[i - 1]);
	}
		
	for (int i = border - 1; i > 1; --i) {
		new_time_layer[i] =  alpha[i] * new_time_layer[i + 1] + beta[i];
	}
		
	alpha[GRID_SIZE - 1] = - c / b(GRID_SIZE - 1);
	beta[GRID_SIZE - 1]  = (d(GRID_SIZE - 1) - a * 280.0) / b(GRID_SIZE - 1);
		
	for (int i = GRID_SIZE - 2; i > border; --i) {
		alpha[i] =  - c / (b(i) + a * alpha[i + 1]);
		beta[i]  =  (d(i) - a * beta[i + 1]) / (b(i) + a * alpha[i + 1]);
	}
		
	for (int i = border + 1; i < GRID_SIZE; ++i) {
		new_time_layer[i] =  alpha[i] * new_time_layer[i - 1] + beta[i];
	}
		
	time_layers.push_back(new_time_layer);
		
	phase_front_coord = phase_front_coord + TAU /\
		ICE_HEAT_FUSION / ICE_DENSITY *\
		(
			ICE_HEAT_COND_COEFF * 
			(
				(time_layers.back()[border] - time_layers.back()[border - 1]) / H  +\
				H / 2 / k_1 / TAU * (new_time_layer[border] - time_layers.back()[border])
			) -\
			WATER_HEAT_COND_COEFF * 
			(
				(time_layers.back()[border + 1] - time_layers.back()[border]) / H  -\
				H / 2 / k_2 / TAU * (new_time_layer[border] - time_layers.back()[border])
			)
		);
	
	return;
}

		
double Implicit::b(int n) {
	int border = (int) floor(phase_front_coord / H) + 1;
	if (n < border)
		return -2.0 - H * H / k_1 / TAU;
	else return -2.0 - H * H / k_2 / TAU;
}

	
double Implicit::d(int n) {
	int border = (int) floor(phase_front_coord / H) + 1;
	if (n < border)
		return (-1.0) * H * H / k_1 / TAU * time_layers.back()[n];
	else return (-1.0) * H * H / k_2 / TAU * time_layers.back()[n];
}
