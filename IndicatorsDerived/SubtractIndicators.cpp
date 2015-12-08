/*
 * SubtractIndicators.cpp
 *
 *  Created on: Jun 24, 2015
 *      Author: jlochman
 */

#include "SubtractIndicators.h"

SubtractIndicators::SubtractIndicators(string branchName, const vector<double>* vec1, const vector<double>* vec2)
	:	IndicatorDerivedDataController(branchName, vec1) {

	m_inVec2 = vec2;
}

SubtractIndicators::~SubtractIndicators() {
}

double SubtractIndicators::calcValue(int pos) {
	return ( m_inVec1->at(pos) - m_inVec2->at(pos) );
}

bool SubtractIndicators::canCalc(int pos) {
	return ( pos < m_inVec1->size() && pos < m_inVec2->size() );
}


