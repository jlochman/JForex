/*
 * AbsolutePriceOscilator.cpp
 *
 *  Created on: Jul 24, 2015
 *      Author: jlochman
 */

#include "AbsolutePriceOscilator.h"
#include "MovingAverageExp.h"

AbsolutePriceOscilator::AbsolutePriceOscilator(string branchName,
		int calculateSize, double alpha,
		const vector<double>* in_vec)
: IndicatorDataController(branchName, calculateSize) {

	input_vec = in_vec;
	m_alpha = alpha;
	m_weight = calcTotalWeight(alpha, calcSize);
}

AbsolutePriceOscilator::~AbsolutePriceOscilator() {
}

double AbsolutePriceOscilator::getAPO(const vector<double>* in_vec, int fromPos,
		int length, double alpha, double weight) {

	if ( fromPos + length + 1 > in_vec->size() ) return 0;
	if ( length <= 0 ) return 0;
	if ( weight == 0 ) weight = calcTotalWeight( alpha, length );

	vector<double> vec_inc;
	vector<double> vec_dec;
	vec_inc.resize(0);
	vec_dec.resize(0);

	for ( int i = fromPos; i < fromPos + length; i++ ) {
		vec_inc.push_back( in_vec->at(i) );
		vec_dec.push_back( in_vec->at(2*fromPos + length - i - 1) );
	}

	double inc = MovingAverageExp::getMeanExp( &vec_inc, 0, length, alpha, weight );
	double dec = MovingAverageExp::getMeanExp( &vec_dec, 0, length, alpha, weight );
	return ( inc - dec );
}

double AbsolutePriceOscilator::calcTotalWeight(double alpha, int length) {
	return MovingAverageExp::calcTotalWeight(alpha, length);
}

double AbsolutePriceOscilator::calcValue(int pos) {
	return getAPO( input_vec, pos, calcSize, m_alpha, m_weight );
}

bool AbsolutePriceOscilator::canCalc(int pos) {
	return ( pos < input_vec->size() - getHistNeeded() );
}
