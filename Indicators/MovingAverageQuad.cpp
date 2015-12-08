/*
 * MovingAverageQuad.cpp
 *
 *  Created on: Jul 17, 2015
 *      Author: jlochman
 */

#include "MovingAverageQuad.h"

MovingAverageQuad::MovingAverageQuad(string branchName, int calculateSize, const vector<double>* in_vec)
: IndicatorDataController(branchName, calculateSize) {
	input_vec = in_vec;
	m_weight = calcTotalWeight(calcSize);
}

MovingAverageQuad::~MovingAverageQuad() {
}

double MovingAverageQuad::calcTotalWeight(int length) {
	double x = 0;
	for ( int i = 0; i < length; i++ ) {
		x += i * ( length - i );
	}
	return x;
}

double MovingAverageQuad::calcValue(int pos) {
	return getMeanQuad(input_vec, pos, calcSize, m_weight);
}

double MovingAverageQuad::getMeanQuad(const vector<double>* in_vec, int fromPos,
		int length, double weight) {
	if ( fromPos + length > in_vec->size() ) return 0;
	if ( length <= 0 ) return 0;
	if ( weight == 0 ) weight = calcTotalWeight( length );

	double x = 0;
	for ( int i = fromPos; i < fromPos + length; i++) {
		x += in_vec->at( i ) * (fromPos + length - i) * (i - fromPos);
	}
	x = x / weight;
	return x;
}

bool MovingAverageQuad::canCalc(int pos) {
	return ( pos < input_vec->size() - getHistNeeded() );
}
