/*
 * Angle.cpp
 *
 *  Created on: Aug 25, 2015
 *      Author: jlochman
 */

#include "Angle.h"

Angle::Angle(string branchName, const vector<double>* vec1,
		const vector<double>* vec2)
	: IndicatorDerivedDataController(branchName, vec1) {

	m_inVec2 = vec2;
}

Angle::~Angle() {
}

double Angle::calcValue(int pos) {
	double change1 = m_inVec1->at(pos) - m_inVec1->at(pos+1);
	double change2 = m_inVec2->at(pos) - m_inVec2->at(pos+1);
	if ( change1 == 0 && change2 == 0 ) return 0;
	double divisor = TMath::Max( TMath::Abs(change1), TMath::Abs(change2) );
	return ( change1 - change2 ) / divisor;
}

bool Angle::canCalc(int pos) {
	return ( pos < m_inVec1->size() - 1 && pos < m_inVec2->size() - 1 );
}
