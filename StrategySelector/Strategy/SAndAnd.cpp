/*
 * SAndAnd.cpp
 *
 *  Created on: Aug 7, 2015
 *      Author: jlochman
 */

#include "SAndAnd.h"

SAndAnd::SAndAnd(int size, GenericDataController* stratOpen1,
		GenericDataController* stratOpen2, GenericDataController* stratOpen3,
		GenericDataController* stratClose)
	: GenericStrategy(size, stratOpen1, stratClose) {

	m_stratOpen2 = stratOpen2;
	m_stratOpen3 = stratOpen3;
}

SAndAnd::~SAndAnd() {
}

string SAndAnd::getName() {
	return ( "[ANDAND] " + m_stratOpen1->getName() +
			 " AND " + m_stratOpen2->getName() +
			 " AND " + m_stratOpen3->getName() +
			 " :VS: " + m_stratClose->getName() );
}

bool SAndAnd::checkTradeOpen(int pos) {
	return ( m_stratOpen1->getValue(pos) == 1 && m_stratOpen2->getValue(pos)
			&& m_stratOpen3->getValue(pos) == 1 );
}
