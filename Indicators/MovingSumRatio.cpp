/*
 * MovingSumRatio.cpp
 *
 *  Created on: Sep 3, 2015
 *      Author: jlochman
 */

#include "MovingAverage.h"

#include "MovingSumRatio.h"

MovingSumRatio::MovingSumRatio(string branchName, int calculateSize,
		const vector<double>* in_vec1, const vector<double>* in_vec2)
	: IndicatorDataController(branchName, calculateSize) {

	m_vec1 = in_vec1;
	m_vec2 = in_vec2;
}

MovingSumRatio::~MovingSumRatio() {
}

double MovingSumRatio::getMovingSumRatio(const vector<double>* in_vec1,
		const vector<double>* in_vec2, int fromPos, int length) {
	double x1 = MovingAverage::getMean( in_vec1, fromPos, length );
	double x2 = MovingAverage::getMean( in_vec2, fromPos, length );
	if ( x1 == 0 && x2 == 0 ) return 0;
	double ratio = 0;
	if ( x1 != 0 ) ratio = x2 / x1; else ratio = x1 / x2;
	ratio = abs(ratio);
	if ( ratio > 1 ) ratio = 1/ratio;
	ratio = 1 - ratio;
	if ( x1 > x2 ) return ratio; else return -ratio;
}

double MovingSumRatio::calcValue(int pos) {
	return getMovingSumRatio( m_vec1, m_vec2, pos, calcSize );
}

bool MovingSumRatio::canCalc(int pos) {
	return ( pos < m_vec1->size() - getHistNeeded() && pos < m_vec2->size() - getHistNeeded() );
}
