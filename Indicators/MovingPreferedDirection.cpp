/*
 * MovingPreferedDirection.cpp
 *
 *  Created on: Sep 3, 2015
 *      Author: jlochman
 */

#include "MovingMin.h"
#include "MovingMax.h"

#include "MovingPreferedDirection.h"

MovingPreferedDirection::MovingPreferedDirection(string branchName,
		int calculateSize, const vector<double>* in_vec1)
	: IndicatorDataController(branchName, calculateSize) {

	m_vec1 = in_vec1;
}

MovingPreferedDirection::~MovingPreferedDirection() {
}

double MovingPreferedDirection::getPrefDirection(const vector<double>* in_vec1, int fromPos, int length) {
	if ( fromPos + length > in_vec1->size() ) return 0;
	if ( length <= 0 ) return 0;
	double x_max = MovingMax::getMax( in_vec1, fromPos, length );
	double x_min = MovingMin::getMin( in_vec1, fromPos, length	);
	double x_0 = in_vec1->at(fromPos + length - 1);
	return ( (x_max - x_0) - (x_0 - x_min) );
}

double MovingPreferedDirection::calcValue(int pos) {
	return getPrefDirection( m_vec1, pos, calcSize);
}

bool MovingPreferedDirection::canCalc(int pos) {
	return ( pos < m_vec1->size() - getHistNeeded() );
}
