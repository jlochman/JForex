/*
 * GreaterThan.cpp
 *
 *  Created on: Jul 13, 2015
 *      Author: jlochman
 */

#include "SCGreaterThan.h"

SCGreaterThan::SCGreaterThan(string branchName, InputFileController* inputFileController,
		string buySell, const vector< double >* vec1, double cutOff)
	: StrategyCloseDataController(branchName, inputFileController, buySell) {

	m_vec1 = vec1;
	m_cutoff = cutOff;
}

SCGreaterThan::~SCGreaterThan() {
}

bool SCGreaterThan::canCalc(int pos) {
	return ( pos <= m_vec1->size() );
}

bool SCGreaterThan::checkClose(int pos) {
	return ( m_vec1->at(pos) > m_cutoff );
}
