#include <stdexcept>
#include <string>
#include <cmath>
#include <iostream>
#include "problem_statement.h"


void ValidateX (double x) {
	
	if (x < LEFT_BOUND_X || x > RIGHT_BOUND_X) {
		std::string error_msg = "Argument " + std::to_string(x) + " shoud be within bounds [" +\
			std::to_string(LEFT_BOUND_X) + "; " + std::to_string(RIGHT_BOUND_X) + "]";
		throw std::invalid_argument(error_msg);
	}
	
}


double StartingCondition(double x) {
	
	try {
		ValidateX(x);
		return 7 * x / (RIGHT_BOUND_X - LEFT_BOUND_X) + 273.0;
	} catch (const char* err) {
		std::cout << err << std::endl;
		return -1;
	}

}


double BorderingConditionAtLeftBound(double t) {
	return (273.0 - 13.0 * (1 - exp( -1e-4 * t)));
}


double BorderingConditionAtRightBound(double t) {
	return 280.0;
}
