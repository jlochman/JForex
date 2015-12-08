/*
 * CorrelationCoefficient.cpp
 *
 *  Created on: Sep 2, 2015
 *      Author: jlochman
 */

#include "../Indicators/MovingAverage.h"
#include "../Indicators/Sigma.h"

#include "CorrelationCoefficient.h"

double CorrelationCoefficient::getCoefficient(const vector<double>* vec1,
		const vector<double>* vec2) {
	int length = min( vec1->size(), vec2->size() );
	if ( length == 0 ) return 0;

	double x = 0;
	double mean1 = MovingAverage::getMean( vec1, 0, length );
	double mean2 = MovingAverage::getMean( vec2, 0, length );

	vector<double>* vec = new vector<double>();
	vec->resize(length);
	for ( int i = 0; i < length; i++ ) {
		vec->at(i) = ( vec1->at(i) - mean1 ) * ( vec2->at(i) - mean2 );
	}
	double nominator = MovingAverage::getMean( vec, 0, length );
	double denominator = Sigma::getSigma( vec1, 0, length ) * Sigma::getSigma( vec2, 0, length );
	if ( denominator != 0 ) x = nominator / denominator;

	return x;
}
