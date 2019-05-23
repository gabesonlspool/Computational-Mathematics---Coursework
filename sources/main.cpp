#include <set>
#include <ctime>
#include <string>
#include <iostream>
#include "explicit.h"
#include "implicit.h"
#include "crunk_nickelson.h"

double TIME_START = 0.0;
double TIME_TARGET = 86400.0;

std::set<string> available_solvers = {"explicit", "implicit", "crunk_nickelson"};


int main (int argc, char *argv[]) {

	struct timespec begin, end;
	try {
	
		if(argc < 3) throw "Not enough parameters passed through command line (argc is too small).";
		const int NODES_NUM = atoi(argv[1]);
		const double EPS = atof(argv[2]);
		const string solver_type = string(argv[3]);

		if (!available_solvers.count(solver_type)) 
			throw "Solver type is not recognisied";
	
		//initialize solver
		Solver * solver;
        	if (solver_type == "crunk_nickelson") {
			CrunkNickelson * cn = new CrunkNickelson(NODES_NUM, EPS, TIME_START, TIME_TARGET);
			solver = (Solver *) cn;
		} else if(solver_type == "implicit") {
			Implicit * cn = new Implicit(NODES_NUM, EPS, TIME_START, TIME_TARGET);
			solver = (Solver *) cn;
		} else {
			Explicit * cn = new Explicit(NODES_NUM, EPS, TIME_START, TIME_TARGET);
			solver = (Solver *) cn;
		}


		string output_file = "output_" + solver_type + ".dat"; 
		clock_gettime(CLOCK_REALTIME, &begin);
		solver->solve(output_file);
		clock_gettime(CLOCK_REALTIME, &end);
		std::cout << (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) /1e9 << std::endl;	
	   
	} catch (const char* exc) {
		std::cout << exc << std::endl;
	}
	
	return 0;
}
