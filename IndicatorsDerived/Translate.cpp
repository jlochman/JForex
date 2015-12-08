/*
 * Translate.cpp
 *
 *  Created on: Jul 13, 2015
 *      Author: jlochman
 */

#include "Translate.h"

Translate :: Translate(string branchName, int translateBy, const vector<double>* vec1)
	: IndicatorDerivedDataController(branchName, vec1)
{
	m_translateBy = translateBy;
}

Translate::~Translate() {
}

double Translate::calcValue(int pos) {
	if ( pos + m_translateBy < 0 ) return m_inVec1->at(0);
	return ( m_inVec1->at(pos + m_translateBy) );
}

bool Translate::canCalc(int pos) {
	return ( pos < m_inVec1->size() - m_translateBy );
}
