/*
 * MovingAverageExp.cpp
 *
 *  Created on: Jul 17, 2015
 *      Author: jlochman
 */

#include "MovingAverageExp.h"

MovingAverageExp::MovingAverageExp(string branchName, int calculateSize, double alpha, const vector<double>* in_vec)
	: IndicatorDataController(branchName, calculateSize) {
	input_vec = in_vec;
	m_alpha = alpha;
	m_weight = calcTotalWeight(alpha, calcSize);

}

MovingAverageExp::~MovingAverageExp() {
}

double MovingAverageExp::calcTotalWeight(double alpha, int length) {
	double result = 0;
	for ( int i = 0; i < length; i++ ) {
		result += pow( alpha, i );
	}
	return result;
}

double MovingAverageExp::calcValue(int pos) {
	return getMeanExp(input_vec, pos, calcSize, m_alpha, m_weight);
}

double MovingAverageExp::getMeanExp(const vector<double>* in_vec, int fromPos,
		int length, double alpha, double weight) {
	if ( fromPos + length > in_vec->size() ) return 0;
	if ( length <= 0 ) return 0;
	if ( weight == 0 ) weight = calcTotalWeight( alpha, length );

	double w = 1;
	double x = 0;
	for ( int i = fromPos; i < fromPos + length; i++) {
		x += in_vec->at( i ) * w;
		w *= alpha;
	}
	x = x / weight;
	return x;
}

bool MovingAverageExp::canCalc(int pos) {
	return ( pos < input_vec->size() - getHistNeeded() );
}
