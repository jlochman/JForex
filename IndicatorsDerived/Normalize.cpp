/*
 * Normalize.cpp
 *
 *  Created on: Sep 1, 2015
 *      Author: jlochman
 */

#include <iostream>

#include "TMath.h"

#include "../Indicators/MovingAverage.h"
#include "../Indicators/MovingMin.h"
#include "../Indicators/MovingMax.h"

#include "Normalize.h"

Normalize::Normalize(string branchName, const vector<double>* vec1)
	: IndicatorDerivedDataController(branchName, vec1) {

	m_mean = 0;
	m_range = 0;
}

Normalize::~Normalize() {
}

double Normalize::calcValue(int pos) {
	if ( m_range == 0 ) {
		double min  = MovingMin::getMin( m_inVec1, 0, m_inVec1->size() );
		double max  = MovingMax::getMax( m_inVec1, 0, m_inVec1->size() );
		//if ( min * max < 0 ) m_mean = 0; else
		m_mean 		= MovingAverage::getMean( m_inVec1, 0, m_inVec1->size() );
		m_range		= TMath::Max( max - m_mean, m_mean - min );
		if ( m_range == 0 ) {
			cerr << "range == 0" << endl;
			m_range = 1;
		}
	}

	return ( ( m_inVec1->at(pos) - m_mean ) / m_range );
}

bool Normalize::canCalc(int pos) {
	return ( pos < m_inVec1->size() );
}
