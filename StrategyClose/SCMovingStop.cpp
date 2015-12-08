/*
 * SCMovingStop.cpp
 *
 *  Created on: Jul 16, 2015
 *      Author: jlochman
 */

#include "SCMovingStop.h"

SCMovingStop::SCMovingStop(string branchName, InputFileController* inputFileController,
		string buySell, double stopLoss)
	: StrategyCloseDataController(branchName, inputFileController, buySell) {

	m_stopLoss = stopLoss;

	askOpen = 0;
	bidOpen = 0;
	posStart = 0;
}

SCMovingStop::~SCMovingStop() {
}

bool SCMovingStop::canCalc(int pos) {
	bool result = ( pos < m_InputFileController->getMinVecSize() ) ;
	if ( result ) {
		setAskBid(pos);
		posStart = pos;
	}
	return ( result );
}

bool SCMovingStop::checkClose(int pos) {
	bool result = false;
	if ( m_BuySell == "BUY" ) {
		if ( m_InputFileController->getValue("ask",pos) > askOpen ) {
			setAskBid( pos );
			return false;
		} else if ( m_InputFileController->getValue("bid",pos) < bidOpen - m_stopLoss ) {
			return true;
		}
	} else if ( m_BuySell == "SELL" ) {
		if ( m_InputFileController->getValue("bid",pos) < bidOpen ) {
			setAskBid( pos );
			return false;
		} else if ( m_InputFileController->getValue("ask",pos) > askOpen + m_stopLoss ) {
			return true;
		}
	}
	return result;
}

void SCMovingStop::setAskBid(int pos) {
	askOpen = m_InputFileController->getValue("ask",pos);
	bidOpen = m_InputFileController->getValue("bid",pos);
}
