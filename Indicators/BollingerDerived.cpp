/*
 * BollingerDerived.cpp
 *
 *  Created on: Sep 5, 2015
 *      Author: jlochman
 */

#include "MovingAverage.h"
#include "Sigma.h"

#include "BollingerDerived.h"

BollingerDerived::BollingerDerived(string branchName, int calculateSize,
		const vector<double>* in_vec)
	: IndicatorDataController(branchName, calculateSize) {

	input_vec = in_vec;
}

BollingerDerived::~BollingerDerived() {
}

double BollingerDerived::getBollingerDerived(const vector<double>* in_vec,
		int fromPos, int length) {

	if ( fromPos + length > in_vec->size() ) return 0;
	if ( length <= 0 ) return 0;

	double sma = MovingAverage::getMean( in_vec, fromPos, length );
	double sigma = Sigma::getSigma( in_vec, fromPos, length, 2 );
	double price = in_vec->at(fromPos);

	if ( sigma == 0 ) return 0;

	double upperBand = sma + 2*sigma;
	double lowerBand = sma - 2*sigma;

	double x = ( price - lowerBand ) / ( upperBand - lowerBand );
	return ( x - 0.5 ) / 2;
}

double BollingerDerived::calcValue(int pos) {
	return getBollingerDerived( input_vec, pos, calcSize );
}

bool BollingerDerived::canCalc(int pos) {
	return ( pos < input_vec->size() - getHistNeeded() );
}
