#include <cmath>
#include <vector>
#include "explicit.h"


using std::vector;


Explicit::Explicit(int n, double eps, double time_start, double time_target): Solver(n, eps, time_start, time_target) {
	TAU = 0.1;
}
	
		
void Explicit::iterationStep(int n) {
				
	std::vector<double> new_time_layer(GRID_SIZE + 2);
	new_time_layer[0] = new_time_layer[1] = BorderingConditionAtLeftBound(TAU * n);
	new_time_layer[GRID_SIZE + 1] = new_time_layer[GRID_SIZE] = BorderingConditionAtRightBound(TAU * n);
		
	int border = (int) floor(phase_front_coord / H) + 1;
	phase_front.push_back(border);
		
	new_time_layer[border] = 273.0;
		
	for (int i = 2; i < border - 1; ++i) {
		new_time_layer[i] = time_layers.back()[i] + TAU / H / H *\
			k_1 * (time_layers.back()[i - 1] - 2 * time_layers.back()[i] + time_layers.back()[i + 1]);
	}
		
	//Около границы раздела двух сред применим неявную схему 
	if (border > 1) {
		new_time_layer[border - 1] = (
			time_layers.back()[border - 1] / TAU +\
			k_1 * (new_time_layer[border - 2] + new_time_layer[border]) / H / H
		) / ( 1/TAU + 2*k_1/H/H);
	}
		
	for (int i = GRID_SIZE - 1; i > border + 1; --i) {
		new_time_layer[i] = time_layers.back()[i] + TAU / H / H *\
			k_2 * (time_layers.back()[i - 1] - 2 * time_layers.back()[i] + time_layers.back()[i + 1]);
	}
		
	if (border < GRID_SIZE + 1) {
		new_time_layer[border + 1] = (
			time_layers.back()[border + 1] / TAU +\
			k_2 * (new_time_layer[border + 2] + new_time_layer[border]) / H / H
		) / (1/TAU + 2*k_2/H/H);
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

