/*
 * Average.cpp
 *
 *  Created on: Sep 10, 2015
 *      Author: jlochman
 */

#include "Average.h"

Average::Average(string branchName, const vector<double>* vec1,
		const vector<double>* vec2)
	: IndicatorDerivedDataController( branchName, vec1 ) {

	m_inVec2 = vec2;
}

Average::~Average() {
}

double Average::calcValue(int pos) {
	return ( ( m_inVec1->at(pos) + m_inVec2->at(pos) ) / 2 );
}

bool Average::canCalc(int pos) {
	return ( pos < m_inVec1->size() && pos < m_inVec2->size() );
}
