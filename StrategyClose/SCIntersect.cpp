/*
 * SCIntersect.cpp
 *
 *  Created on: Aug 9, 2015
 *      Author: jlochman
 */

#include "SCIntersect.h"

SCIntersect::SCIntersect(string branchName,
		InputFileController* inputFileController, string buySell,
		const vector<double>* vec1, const vector<double>* vec2)
	: StrategyCloseDataController(branchName, inputFileController, buySell) {

	m_vec1 = vec1;
	m_vec2 = vec2;
}

SCIntersect::~SCIntersect() {
}

bool SCIntersect::canCalc(int pos) {
	return ( pos < m_vec1->size() - 1 && pos < m_vec2->size() - 1 );
}

bool SCIntersect::checkClose(int pos) {
	return ( m_vec1->at(pos) > m_vec2->at(pos)
			&& m_vec1->at(pos+1) < m_vec2->at(pos+1) );
}
