/*
 * Sigma.cpp
 *
 *  Created on: Jul 17, 2015
 *      Author: jlochman
 */

#include "Sigma.h"
#include "MovingAverage.h"

Sigma::Sigma(string branchName, int calculateSize,
		const vector<double>* in_vec)
: IndicatorDataController(branchName, calculateSize) {
	input_vec = in_vec;
	m_power = 2;
}

Sigma::Sigma(string branchName, int calculateSize,
		double power, const vector<double>* in_vec)
: IndicatorDataController(branchName, calculateSize) {
	input_vec = in_vec;
	m_power = power;
}

Sigma::~Sigma() {
}

double Sigma::calcValue(int pos) {
	return getSigma(input_vec, pos, calcSize, m_power);
}

double Sigma::getSigma(const vector<double>* in_vec, int fromPos, int length,
		double power) {
	if ( fromPos + length > in_vec->size() ) return 0;
	if ( length <= 0 ) return 0;

	double mean = MovingAverage::getMean( in_vec, fromPos, length );
	double x = 0;
	for ( int i = fromPos; i < fromPos + length; i++) {
		x += pow( abs(mean - in_vec->at(i)), power );
	}
	x = x / length;
	x = pow( x, 1 / power);
	return x;
}

bool Sigma::canCalc(int pos) {
	return ( pos < input_vec->size() - getHistNeeded() );
}
