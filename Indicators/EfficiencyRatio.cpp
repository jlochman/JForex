/*
 * EfficiencyRatio.cpp
 *
 *  Created on: Sep 5, 2015
 *      Author: jlochman
 */

#include "Change.h"
#include "Volatility.h"

#include "EfficiencyRatio.h"

EfficiencyRatio::EfficiencyRatio(string branchName, int calculateSize,
		const vector<double>* in_vec)
	: IndicatorDataController(branchName, calculateSize) {

	input_vec = in_vec;
}

EfficiencyRatio::~EfficiencyRatio() {
}

double EfficiencyRatio::getEffRatio(const vector<double>* in_vec, int fromPos,
		int length) {

	if ( fromPos + length > in_vec->size() ) return 0;
	if ( length <= 0 ) return 0;

	double change = Change::getChange( in_vec, fromPos, length );
	double volatility = Volatility::getVolatility( in_vec, fromPos, length );
	if ( volatility == 0 ) return 0;

	return change / volatility;
}

double EfficiencyRatio::calcValue(int pos) {
	return getEffRatio( input_vec, pos, calcSize );
}

bool EfficiencyRatio::canCalc(int pos) {
	return ( pos < input_vec->size() - getHistNeeded() );
}
