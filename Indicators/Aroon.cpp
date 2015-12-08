/*
 * Aroon.cpp
 *
 *  Created on: Sep 5, 2015
 *      Author: jlochman
 */

#include "MovingMax.h"
#include "MovingMin.h"

#include "Aroon.h"

Aroon::Aroon(string branchName, int calculateSize,
		const vector<double>* in_vec)
	: IndicatorDataController(branchName, calculateSize) {

	input_vec = in_vec;
}

Aroon::~Aroon() {
}

double Aroon::getAroon(const vector<double>* in_vec, int fromPos, int length) {

	if ( fromPos + length > in_vec->size() ) return 0;
	if ( length <= 0 ) return 0;

	double maxPos = MovingMax::getMaxPos( in_vec, fromPos, length );
	double minPos = MovingMin::getMinPos( in_vec, fromPos, length );
	return ( maxPos - minPos ) / length;
}

double Aroon::calcValue(int pos) {
	return getAroon( input_vec, pos, calcSize );
}

bool Aroon::canCalc(int pos) {
	return ( pos < input_vec->size() - getHistNeeded() );
}
