#ifndef PROBLEM_STATEMENT_H
#define PROBLEM_STATEMENT_H

const double ICE_HEAT_FUSION = 3.3e5;
const double WATER_HEAT_CAPACITY = 4200.0;
const double ICE_HEAT_CAPACITY = 2100.0;
const double WATER_HEAT_COND_COEFF = 0.56;
const double ICE_HEAT_COND_COEFF = 2.25;
const double WATER_THERM_DIFFUS_COEFF = 1.33e-7;
const double ICE_THERM_DIFFUS_COEFF = 1.08e-6;
const double WATER_DENSITY = 1e3;
const double ICE_DENSITY = 9e2;

const double LEFT_BOUND_X = 0.0;
const double RIGHT_BOUND_X = 1.0;

double StartingCondition(double x);
double BorderingConditionAtLeftBound(double t);
double BorderingConditionAtRightBound(double t); 

#endif