/*
 * SSimple.cpp
 *
 *  Created on: Aug 6, 2015
 *      Author: jlochman
 */

#include "SSimple.h"

SSimple::SSimple(int size, GenericDataController* stratOpen1,
		GenericDataController* stratClose)
	: GenericStrategy(size, stratOpen1, stratClose) {
}

SSimple::~SSimple() {
}

string SSimple::getName() {
	return ( "[SIMPLE] " + m_stratOpen1->getName() + " :VS: " + m_stratClose->getName() );
}

bool SSimple::checkTradeOpen(int pos) {
	return ( m_stratOpen1->getValue(pos) == 1 );
}
