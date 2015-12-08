/*
 * StrategyOpenDataController.cpp
 *
 *  Created on: Jul 16, 2015
 *      Author: jlochman
 */

#include "StrategyOpenDataController.h"

StrategyOpenDataController::StrategyOpenDataController(string branchName)
	: GenericDataController(branchName) {
	m_className = "SODataController";

	DEAD_TIME_AFTER_ORDER = 30;
}

StrategyOpenDataController::~StrategyOpenDataController() {
}

void StrategyOpenDataController::calculate(int maxCount) {
	m_vec.resize(0);
	int counter = 0;
	for ( int i = 0; i < maxCount; i++ ) {
		if ( this->canCalc(i) ) {
			if ( counter == 0 ) {
				if ( this->checkOpen(i) ) {
					this->addValue(1);
					counter = DEAD_TIME_AFTER_ORDER;
				} else this->addValue(0);
			} else {
				this->addValue(0);
				counter--;
			}
		} else break;
	}
}
