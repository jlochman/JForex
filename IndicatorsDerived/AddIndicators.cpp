/*
 * AddIndicators.cpp
 *
 *  Created on: Aug 9, 2015
 *      Author: jlochman
 */

#include "AddIndicators.h"

AddIndicators::AddIndicators(string branchName, const vector<double>* vec1,
		const vector<double>* vec2)
	: IndicatorDerivedDataController(branchName, vec1) {

	m_inVec2 = vec2;
}

AddIndicators::~AddIndicators() {
}

double AddIndicators::calcValue(int pos) {
	return ( m_inVec1->at(pos) + m_inVec2->at(pos) );
}

bool AddIndicators::canCalc(int pos) {
	return ( pos < m_inVec1->size() && pos < m_inVec2->size() );
}
