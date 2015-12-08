/*
 * SOGreaterThan.cpp
 *
 *  Created on: Aug 5, 2015
 *      Author: jlochman
 */

#include "SOGreaterThan.h"

SOGreaterThan::SOGreaterThan(string branchName, double x, const vector<double>* vec1)
	: StrategyOpenDataController(branchName) {

	m_vec = vec1;
	m_value = x;
}

SOGreaterThan::~SOGreaterThan() {
}

bool SOGreaterThan::canCalc(int pos) {
	return ( pos < m_vec->size() - 1 );
}

bool SOGreaterThan::checkOpen(int pos) {
	return ( m_vec->at(pos) > m_value );
}
