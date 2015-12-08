/*
 * SubtractAndNormalize.cpp
 *
 *  Created on: Sep 11, 2015
 *      Author: jlochman
 */

#include <iostream>

#include "../Indicators/MovingMax.h"
#include "../Indicators/MovingMin.h"
#include "../Indicators/MovingAverage.h"

#include "SubtractAndNormalize.h"

SubtractAndNormalize::SubtractAndNormalize(string branchName,
		const vector<double>* vec1, const vector<double>* vec2)
	: IndicatorDerivedDataController(branchName, vec1) {

	m_inVec2 = vec2;
	m_mean = 0;
	m_range = 0;
}

SubtractAndNormalize::~SubtractAndNormalize() {
}

double SubtractAndNormalize::calcValue(int pos) {
	if ( m_range == 0 ) {
		if ( m_inVec1->size() == 0 ) return 0;
		if ( m_inVec2->size() == 0 ) return 0;
		calcMeanAndRange();
	}
	return ( ( ( m_inVec1->at(pos) - m_inVec2->at(pos) ) - m_mean ) / m_range );
}

void SubtractAndNormalize::calcMeanAndRange() {
	vector<double> myVec;
	for ( int i = 0; i < min( m_inVec1->size(), m_inVec2->size() ); i++ ) {
		myVec.push_back( m_inVec1->at(i) - m_inVec2->at(i) );
	}

	double min  = MovingMin::getMin( &myVec, 0, myVec.size() );
	double max  = MovingMax::getMax( &myVec, 0, myVec.size() );
	m_mean 		= MovingAverage::getMean( &myVec, 0, myVec.size() );
	m_range		= TMath::Max( max - m_mean, m_mean - min );
	if ( m_range == 0 ) {
		cerr << "range == 0" << endl;
		m_range = 1;
	}
}

bool SubtractAndNormalize::canCalc(int pos) {
	return ( pos < m_inVec1->size() && pos < m_inVec2->size() );
}
