/*
 * MovingAverageLin.cpp
 *
 *  Created on: Jul 17, 2015
 *      Author: jlochman
 */

#include "MovingAverageLin.h"

MovingAverageLin::MovingAverageLin(string branchName, int calculateSize, const vector<double>* in_vec)
: IndicatorDataController(branchName, calculateSize) {
	input_vec = in_vec;
	m_weight = calcTotalWeight(calcSize);
}

MovingAverageLin::~MovingAverageLin() {
}

double MovingAverageLin::calcValue(int pos) {
	return getMeanLin( input_vec, pos, calcSize, m_weight );
}

double MovingAverageLin::calcTotalWeight(int length) {
	return length * (1 + length) / 2;
}

double MovingAverageLin::getMeanLin(const vector<double>* in_vec, int fromPos,
		int length, double weight) {
	if ( fromPos + length > in_vec->size() ) return 0;
	if ( length <= 0 ) return 0;
	if ( weight == 0 ) weight = calcTotalWeight( length );

	double x = 0;
	for ( int i = fromPos; i < fromPos + length; i++) {
		x += in_vec->at( i ) * (fromPos + length - i);
	}
	x = x / weight;
	return x;
}

bool MovingAverageLin::canCalc(int pos) {
	return ( pos < input_vec->size() - getHistNeeded() );
}
