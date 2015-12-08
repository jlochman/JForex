/*
 * SOIntersect.cpp
 *
 *  Created on: Jul 16, 2015
 *      Author: jlochman
 */

#include "SOIntersect.h"

SOIntersect::SOIntersect(string branchName, const vector<double>* vec1, const vector<double>* vec2)
	: StrategyOpenDataController(branchName) {

	m_vec1 = vec1;
	m_vec2 = vec2;
}

SOIntersect::~SOIntersect() {
}

bool SOIntersect::canCalc(int pos) {
	return ( pos < m_vec1->size() - 1 && pos < m_vec2->size() - 1 );
}

bool SOIntersect::checkOpen(int pos) {
	return ( m_vec1->at(pos) > m_vec2->at(pos)
			&& m_vec1->at(pos+1) < m_vec2->at(pos+1) );
}
