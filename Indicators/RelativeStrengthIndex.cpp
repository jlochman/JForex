/*
 * RelativeStrengthIndex.cpp
 *
 *  Created on: Jul 17, 2015
 *      Author: jlochman
 */

#include <iostream>

#include "RelativeStrengthIndex.h"
#include "MovingAverageExp.h"

RelativeStrengthIndex::RelativeStrengthIndex(string branchName,
		int calculateSize, double alpha,
		const vector<double>* in_vec)
: IndicatorDataController(branchName, calculateSize){
	input_vec = in_vec;
	m_alpha = alpha;
	m_weight = calcTotalWeight(alpha, calcSize);
}

RelativeStrengthIndex::~RelativeStrengthIndex() {
}

double RelativeStrengthIndex::getRSI(const vector<double>* in_vec, int fromPos,
		int length, double alpha, double weight) {

	if ( fromPos + length + 1 > in_vec->size() ) return 0;
	if ( length <= 0 ) return 0;
	if ( weight == 0 ) weight = calcTotalWeight( alpha, length );

	vector<double> vec_down;
	vector<double> vec_up;
	vec_down.resize(0);
	vec_up.resize(0);

	double x = 0;
	for ( int i = fromPos; i < fromPos + length; i++ ) {
		x = in_vec->at(i+1) - in_vec->at(i);
		if ( x > 0 ) {
			vec_up.push_back(x);
			vec_down.push_back(0);
		} else if ( x == 0 ) {
			vec_up.push_back(0);
			vec_down.push_back(0);
		} else if ( x < 0 ) {
			vec_up.push_back(0);
			vec_down.push_back(-x);
		}
	}

	double up   = MovingAverageExp::getMeanExp( &vec_up,   0, length, alpha, weight );
	double down = MovingAverageExp::getMeanExp( &vec_down, 0, length, alpha, weight );
	if ( down != 0 ) return ( 1 - 2 / ( 1 + up/down ) );
	else return 0;
}

double RelativeStrengthIndex::calcTotalWeight(double alpha, int length) {
	return MovingAverageExp::calcTotalWeight(alpha, length);
}

double RelativeStrengthIndex::calcValue(int pos) {
	return getRSI( input_vec, pos, calcSize, m_alpha, m_weight );
}

bool RelativeStrengthIndex::canCalc(int pos) {
	return ( pos < input_vec->size() - getHistNeeded() - 1 );
}
