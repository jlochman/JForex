/*
 * MovingMin.cpp
 *
 *  Created on: Aug 28, 2015
 *      Author: jlochman
 */

#include "MovingMin.h"

MovingMin::MovingMin(string branchName, int calculateSize,
		const vector<double>* in_vec)
: IndicatorDataController(branchName, calculateSize) {

	input_vec = in_vec;
}

MovingMin::~MovingMin() {
}

double MovingMin::getMin(const vector<double>* in_vec, int fromPos,
		int length) {
	if ( fromPos + length > in_vec->size() ) return 0;
	if ( length <= 0 ) return 0;

	double x = numeric_limits<double>::max();
	for ( int i = fromPos; i < fromPos + length; i++) {
		if ( in_vec->at( i ) < x ) x = in_vec->at(i);
	}
	return x;
}

double MovingMin::calcValue(int pos) {
	return getMin(input_vec, pos, calcSize);
}

bool MovingMin::canCalc(int pos) {
	return ( pos < input_vec->size() - getHistNeeded() );
}

int MovingMin::getMinPos(const vector<double>* in_vec, int fromPos,
		int length) {
	if ( fromPos + length > in_vec->size() ) return 0;
	if ( length <= 0 ) return 0;

	double pos = 0;
	double min = numeric_limits<double>::max();
	for ( int i = fromPos; i < fromPos + length; i++) {
		if ( in_vec->at( i ) < min ) {
			min = in_vec->at(i);
			pos = i;
		}
	}
	return pos;
}
