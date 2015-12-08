/*
 * WinningFixedStop.cpp
 *
 *  Created on: Sep 24, 2015
 *      Author: jlochman
 */

#include "MovingMax.h"
#include "MovingMin.h"

#include "WinningFixedStop.h"

WinningFixedStop::WinningFixedStop(string branchName, int calculateSize,
		const vector<double>* in_vec)
	: IndicatorDataController(branchName, calculateSize) {

	input_vec = in_vec;
}

WinningFixedStop::~WinningFixedStop() {
}

double WinningFixedStop::getWinningFixedStop(const vector<double>* in_vec,
		int fromPos, int length) {

	if ( fromPos + length > in_vec->size() ) return 0;
	if ( length <= 0 ) return 0;

	double max = MovingMax::getMax( in_vec, fromPos, length );
	double min = MovingMin::getMin( in_vec, fromPos, length );
	double start = in_vec->at(fromPos);

	double up = max - start;
	double down = start - min;

	if ( up > down ) return up;
	else if ( down > up ) return -down;
	else return 0;
}

double WinningFixedStop::calcValue(int pos) {
	return getWinningFixedStop( input_vec, pos, calcSize );
}

bool WinningFixedStop::canCalc(int pos) {
	return ( pos < input_vec->size() - getHistNeeded() );
}
