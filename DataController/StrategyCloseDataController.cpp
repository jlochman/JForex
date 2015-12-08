/*
 * StrategyCloseDataController.cpp
 *
 *  Created on: Jul 13, 2015
 *      Author: jlochman
 */

#include <iostream>

#include "StrategyCloseDataController.h"

StrategyCloseDataController::StrategyCloseDataController(string branchName, InputFileController* inputFileController,
		string buySell)
	: GenericDataController(branchName) {
	m_className = "SCDataController";

	m_InputFileController = inputFileController;
	m_BuySell = buySell;
}

StrategyCloseDataController::~StrategyCloseDataController() {
}

void StrategyCloseDataController::calculate(int maxCount) {
	m_vec.resize( 0 );
	int orderDurationSum = 0;
	int orderCount = 0;

	/*
	for ( int i = 0; i < maxCount; i++ ) {
		if ( this->canCalc(i) ) {
			bool found = false;
			double result = 0;
			for (int j = i-1; j >= 0; j-- ) {
				if ( this->checkClose(j) ) {
					found = true;
					if ( m_BuySell == "BUY" ) {
						result = m_InputFileController->getVecByName("bid")->at(j)
								- m_InputFileController->getVecByName("ask")->at(i);
					} else if ( m_BuySell == "SELL" ) {
						result = m_InputFileController->getVecByName("bid")->at(i)
								- m_InputFileController->getVecByName("ask")->at(j);
					}
					orderDurationSum += i - j;
					orderCount++;
					break;
				}
			}
			result *= 1000;
			this->addValue(result);
		}
		else break; // if this->canCalc
	}
	*/
	for ( int i = 0; i < maxCount; i = i + m_calcIncrement ) {
		if ( this->canCalc(i) ) {
			bool found = false;
			double result = 0;
			for (int j = i-1; j >= 0; j-- ) {
				if ( this->checkClose(j) ) {
					found = true;
					if ( m_BuySell == "BUY" ) {
						result = m_InputFileController->getVecByName("bid")->at(j)
								- m_InputFileController->getVecByName("ask")->at(i);
					} else if ( m_BuySell == "SELL" ) {
						result = m_InputFileController->getVecByName("bid")->at(i)
								- m_InputFileController->getVecByName("ask")->at(j);
					}
					orderDurationSum += i - j;
					orderCount++;
					break;
				}
			}
			result *= 1000;
			this->addValue(result);
		}
		else break; // if this->canCalc
	}

	if ( orderCount > 0 )
		cout << " Average ticks before order closed: " << orderDurationSum / orderCount << endl;
}
