/*
 * MovingAverage.cpp
 *
 *  Created on: Jun 22, 2015
 *      Author: jlochman
 */

#include <iostream>

#include "MovingAverage.h"

MovingAverage::MovingAverage(string branchName, int calculateSize, const vector<double>* in_vec)
	: IndicatorDataController(branchName, calculateSize) {
	input_vec = in_vec;
}

MovingAverage::~MovingAverage() {
}

double MovingAverage::calcValue(int pos) {
	return getMean(input_vec, pos, calcSize);
}

bool MovingAverage::canCalc(int pos) {
	return ( pos < input_vec->size() - getHistNeeded() );
}

double MovingAverage::getMean(const vector<double>* in_vec, int fromPos,
		int length) {
	if ( fromPos + length > in_vec->size() ) return 0;
	if ( length <= 0 ) return 0;

	double x = 0;
	for ( int i = fromPos; i < fromPos + length; i++) {
		x += in_vec->at( i );
	}
	x = x / length;
	return x;
}
