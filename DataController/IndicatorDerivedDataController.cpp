/*
 * IndicatorDerivedDataController.cpp
 *
 *  Created on: Jun 24, 2015
 *      Author: jlochman
 */

#include "IndicatorDerivedDataController.h"

IndicatorDerivedDataController::IndicatorDerivedDataController(
		string branchName, const vector<double>* vec)
	: GenericDataController(branchName) {
	m_className = "IndicatorDerivedDataController";

	m_inVec1 = vec;
}

IndicatorDerivedDataController::~IndicatorDerivedDataController() {
}

void IndicatorDerivedDataController::calculate(int maxCount) {
	m_vec.resize( 0 );
	for ( int i = 0; i < maxCount; i++ ) {
		if ( this->canCalc(i) )
			this->addValue( this->calcValue(i) );
		else break;
	}
}
