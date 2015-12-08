/*
 * Volatility.cpp
 *
 *  Created on: Sep 5, 2015
 *      Author: jlochman
 */

#include "Volatility.h"

Volatility::Volatility(string branchName, int calculateSize,
		const vector<double>* in_vec)
	: IndicatorDataController(branchName, calculateSize) {

	input_vec = in_vec;
}

Volatility::~Volatility() {
}

double Volatility::getVolatility(const vector<double>* in_vec, int fromPos,
		int length) {

	if ( fromPos + length > in_vec->size() ) return 0;
	if ( length <= 0 ) return 0;

	double x = 0;
	for ( int i = fromPos; i < fromPos + length - 1; i++) {
		x += abs( in_vec->at(i) - in_vec->at(i+1) );
	}
	return x;
}

double Volatility::calcValue(int pos) {
	return getVolatility( input_vec, pos, calcSize );
}

bool Volatility::canCalc(int pos) {
	return ( pos < input_vec->size() - getHistNeeded() );
}
