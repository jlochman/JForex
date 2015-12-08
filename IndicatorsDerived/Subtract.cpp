/*
 * Subtract.cpp
 *
 *  Created on: Jul 17, 2015
 *      Author: jlochman
 */

#include "Subtract.h"

Subtract::Subtract(string branchName, double subtractBy,
		const vector<double>* vec1)
: IndicatorDerivedDataController(branchName, vec1) {
	m_subtractBy = subtractBy;
}

Subtract::~Subtract() {
}

double Subtract::calcValue(int pos) {
	return ( m_inVec1->at(pos) + m_subtractBy );
}

bool Subtract::canCalc(int pos) {
	return ( pos < m_inVec1->size() );
}
