/*
 * Change.cpp
 *
 *  Created on: Sep 5, 2015
 *      Author: jlochman
 */

#include "Change.h"

Change::Change(string branchName, int calculateSize,
		const vector<double>* in_vec)
	: IndicatorDataController(branchName, calculateSize) {

	input_vec = in_vec;
}

Change::~Change() {
}

double Change::getChange(const vector<double>* in_vec, int fromPos,
		int length) {

	if ( fromPos + length > in_vec->size() ) return 0;
	if ( length <= 0 ) return 0;

	return in_vec->at(fromPos) - in_vec->at(fromPos + length - 1);
}

double Change::calcValue(int pos) {
	return getChange( input_vec, pos, calcSize );
}

bool Change::canCalc(int pos) {
	return ( pos < input_vec->size() - getHistNeeded() );
}
