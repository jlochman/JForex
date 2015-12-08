/*
 * SmallerThan.cpp
 *
 *  Created on: Jul 14, 2015
 *      Author: jlochman
 */

#include "SCSmallerThan.h"

SCSmallerThan::SCSmallerThan(string branchName, InputFileController* inputFileController,
		string buySell, const vector< double >* vec1, double cutOff)
	: StrategyCloseDataController(branchName, inputFileController, buySell) {

	m_vec1 = vec1;
	m_cutoff = cutOff;
}

SCSmallerThan::~SCSmallerThan() {
}

bool SCSmallerThan::canCalc(int pos) {
	return ( pos <= m_vec1->size() );
}

bool SCSmallerThan::checkClose(int pos) {
	return ( m_vec1->at(pos) < m_cutoff );
}
