/*
 * MovingAverageLinInv.cpp
 *
 *  Created on: Sep 16, 2015
 *      Author: jlochman
 */

#include "MovingAverageLin.h"

#include "MovingAverageLinInv.h"

MovingAverageLinInv::MovingAverageLinInv(string branchName, int calculateSize,
		const vector<double>* in_vec)
	: IndicatorDataController(branchName, calculateSize) {
	input_vec = in_vec;
	m_weight = MovingAverageLin::calcTotalWeight(calcSize);
}

MovingAverageLinInv::~MovingAverageLinInv() {
}

double MovingAverageLinInv::getMeanLinInv(const vector<double>* in_vec,
		int fromPos, int length, double weight) {
	if ( fromPos + length > in_vec->size() ) return 0;
	if ( length <= 0 ) return 0;
	if ( weight == 0 ) weight = MovingAverageLin::calcTotalWeight( length );

	double x = 0;
	for ( int i = fromPos; i < fromPos + length; i++) {
		x += in_vec->at( i ) * (i - fromPos + 1);
	}
	x = x / weight;
	return x;
}

double MovingAverageLinInv::calcValue(int pos) {
	return getMeanLinInv( input_vec, pos, calcSize, m_weight );
}

bool MovingAverageLinInv::canCalc(int pos) {
	return ( pos < input_vec->size() - getHistNeeded() );
}
