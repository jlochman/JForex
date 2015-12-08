/*
 * IndicatorDataController.cpp
 *
 *  Created on: Jun 22, 2015
 *      Author: jlochman
 */

#include <iostream>

#include "IndicatorDataController.h"

IndicatorDataController::IndicatorDataController(string branchName, int calculateSize)
	: GenericDataController(branchName) {
	m_className = "IndicatorDataController";

	calcSize = calculateSize;
	calcHistNeeded();
}

IndicatorDataController::~IndicatorDataController() {
}

void IndicatorDataController::calculate(int maxCount) {
	m_vec.resize( 0 );
	for ( int i = 0; i < maxCount; i = i + m_calcIncrement ) {
		if ( this->canCalc(i) )
			this->addValue( this->calcValue(i) );
		else break;
	}
}

void IndicatorDataController::calcHistNeeded() {
	histNeeded = calcSize;
}
