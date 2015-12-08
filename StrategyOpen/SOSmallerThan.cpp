/*
 * SOSmallerThan.cpp
 *
 *  Created on: Aug 5, 2015
 *      Author: jlochman
 */

#include "SOSmallerThan.h"

SOSmallerThan::SOSmallerThan(string branchName, double x,
		const vector<double>* vec1)
	: StrategyOpenDataController(branchName) {

	m_vec = vec1;
	m_value = x;
}

SOSmallerThan::~SOSmallerThan() {
}

bool SOSmallerThan::canCalc(int pos) {
	return ( pos < m_vec->size() - 1 );
}

bool SOSmallerThan::checkOpen(int pos) {
	return ( m_vec->at(pos) < m_value );
}
