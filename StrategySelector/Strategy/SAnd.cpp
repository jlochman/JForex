/*
 * SAnd.cpp
 *
 *  Created on: Aug 7, 2015
 *      Author: jlochman
 */

#include "SAnd.h"

SAnd::SAnd(int size, GenericDataController* stratOpen1, GenericDataController* stratOpen2,
		GenericDataController* stratClose)
	: GenericStrategy(size, stratOpen1, stratClose) {

	m_stratOpen2 = stratOpen2;
}

SAnd::~SAnd() {
}

string SAnd::getName() {
	return ( "[AND] " + m_stratOpen1->getName() +
			 " AND " + m_stratOpen2->getName() +
			 " :VS: " + m_stratClose->getName() );
}

bool SAnd::checkTradeOpen(int pos) {
	return ( m_stratOpen1->getValue(pos) == 1 && m_stratOpen2->getValue(pos) );
}
