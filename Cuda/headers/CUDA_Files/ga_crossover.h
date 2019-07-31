#ifndef GA_CROSSOVER_h
#define GA_CROSSOVER_h

// Collection of functions to perform crossover operations on rkParameters
// A crossover mask is an array of elements equal to the number of elements in the rkParameters list
// The mask defines what elements come from partent n and parent m
// [ {elements}     {coefficients}          {other parameters} ]
// [   0-5          6-14,15-19,20-24, 25,    26, 27                                             ]
#include <random>

#include "../Runge_Kutta/rkParameters.h"
#include "individuals.h"

rkParameters<double> generateNewIndividual(const rkParameters<double> & p1, const rkParameters<double> & p2, const int mask[]);

// gets a number of new Individuals equal to selectionSize by crossover of survivors
int crossover(Individual *survivors, Individual *pool, int survivorSize, int poolSize);

#include "ga_crossover.cu"
#endif

