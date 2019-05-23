#ifndef IMPLICIT_H
#define IMPLICIT_H

#include "solver.h"


class Implicit: public Solver {

public:

	Implicit(int n, double eps, double time_start, double time_target);
		
protected:

	void iterationStep(int n) override;
	
private:

	const double a = 1.0;
	const double c = 1.0;
	
	double b(int n);
	double d(int n);
	
};

#endif
