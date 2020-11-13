/*
 * GA.cpp
 *
 *  Created on: Sep 20, 2020
 *      Author: sushil
 */

#include "GA.h"
#include <string>
#include <iostream>

GA::GA(int argc, char *argv[], int randomSeed) {
	SetupOptions(argc, argv, randomSeed);
	srandom(options.randomSeed);
}

GA::~GA() {
	// TODO Auto-generated destructor stub
}


void GA::SetupOptions(int argc, char *argv[], int randomSeed){
	options.randomSeed = randomSeed;
	options.popSize = 30;
	options.chromLength = 15;
	options.maxgens = 60;
	options.px = 0.7f;
	options.pm = 0.001f;
	options.infile = std::string ("infile");
	options.outfile = std::string("outfile");
}

void GA::Init(){
	parent = new Population(options);
	child  = new Population(options);
	parent->Init(); // evaluates, stats, and reports on initial population
	parent->Statistics();
	parent->Report(0);
}

void GA::Run(){

	for(unsigned long int i = 1; i < options.maxgens; i++){
		parent->Generation(child);
		child->Evaluate();
		child->Statistics();
		child->Report(i);

		Population *tmp = parent;
		parent = child;
		child = tmp;
	}
}

