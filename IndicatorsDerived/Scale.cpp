/*
 * Scale.cpp
 *
 *  Created on: Jul 17, 2015
 *      Author: jlochman
 */

#include "Scale.h"

Scale::Scale(string branchName, double scaleBy, const vector<double>* vec1)
	: IndicatorDerivedDataController(branchName, vec1)
{
	m_scaleBy = scaleBy;
}

Scale::~Scale() {
}

double Scale::calcValue(int pos) {
	return ( m_inVec1->at(pos) * m_scaleBy );
}

bool Scale::canCalc(int pos) {
	return ( pos < m_inVec1->size() );
}
