/*
 * MovingMax.cpp
 *
 *  Created on: Aug 28, 2015
 *      Author: jlochman
 */

#include "MovingMax.h"

MovingMax::MovingMax(string branchName, int calculateSize,
		const vector<double>* in_vec)
: IndicatorDataController(branchName, calculateSize) {

	input_vec = in_vec;
}

MovingMax::~MovingMax() {
}

double MovingMax::getMax(const vector<double>* in_vec, int fromPos,
		int length) {
	if ( fromPos + length > in_vec->size() ) return 0;
	if ( length <= 0 ) return 0;

	double x = numeric_limits<double>::min();
	for ( int i = fromPos; i < fromPos + length; i++) {
		if ( in_vec->at( i ) > x ) x = in_vec->at(i);
	}
	return x;
}

double MovingMax::calcValue(int pos) {
	return getMax(input_vec, pos, calcSize);
}

bool MovingMax::canCalc(int pos) {
	return ( pos < input_vec->size() - getHistNeeded() );
}

int MovingMax::getMaxPos(const vector<double>* in_vec, int fromPos,
		int length) {
	if ( fromPos + length > in_vec->size() ) return 0;
	if ( length <= 0 ) return 0;

	double pos = 0;
	double max = numeric_limits<double>::min();
	for ( int i = fromPos; i < fromPos + length; i++) {
		if ( in_vec->at( i ) > max ) {
			max = in_vec->at(i);
			pos = i;
		}
	}
	return pos;
}
