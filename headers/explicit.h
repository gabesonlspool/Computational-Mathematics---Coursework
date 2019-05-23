#ifndef EXPLICIT_H
#define EXPLICIT_H

#include "solver.h"

class Explicit: public Solver {

public:

	Explicit(int n, double eps, double time_start, double time_target);
		
protected:

	void iterationStep(int n) override;
	
};

#endif
