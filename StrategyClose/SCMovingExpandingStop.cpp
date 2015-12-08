/*
 * SCMovingExpandingStop.cpp
 *
 *  Created on: Jul 16, 2015
 *      Author: jlochman
 */

#include <iostream>

#include "SCMovingExpandingStop.h"

SCMovingExpandingStop::SCMovingExpandingStop(string branchName, InputFileController* inputFileController,
		string buySell, double stopLossAbs, double stopLossRel)
	: StrategyCloseDataController(branchName, inputFileController, buySell) {

	m_stopLossAbs = stopLossAbs;
	m_stopLossRel = stopLossRel;

	askOpen = 0;
	bidOpen = 0;
	askLastChange = 0;
	bidLastChange = 0;

	posStart = 0;
	stopLoss = 0;

}

SCMovingExpandingStop::~SCMovingExpandingStop() {
}

bool SCMovingExpandingStop::canCalc(int pos) {
	bool result = ( pos < m_InputFileController->getMinVecSize() ) ;
	if ( result ) {
		setAskBidOpen(pos);
		setAskBidLastChange(pos);
		posStart = pos;
	}
	return ( result );
}

bool SCMovingExpandingStop::checkClose(int pos) {
	bool result = false;
	if ( posStart - pos > 10000 ) return true;
	if ( m_BuySell == "BUY" ) {
		if ( m_InputFileController->getValue("ask",pos) > askLastChange ) {
			setAskBidLastChange( pos );
			return false;
		} else if ( m_InputFileController->getValue("bid",pos) < bidLastChange - stopLoss ) {
			return true;
		}
	} else if ( m_BuySell == "SELL" ) {
		if ( m_InputFileController->getValue("bid",pos) < bidLastChange ) {
			setAskBidLastChange( pos );
			return false;
		} else if ( m_InputFileController->getValue("ask",pos) > askLastChange + stopLoss ) {
			return true;
		}
	}
	return result;
}

void SCMovingExpandingStop::setAskBidOpen(int pos) {
	askOpen = m_InputFileController->getValue("ask",pos);
	bidOpen = m_InputFileController->getValue("bid",pos);
	stopLoss = m_stopLossAbs;
}

void SCMovingExpandingStop::setAskBidLastChange(int pos) {
	askLastChange = m_InputFileController->getValue("ask",pos);
	bidLastChange = m_InputFileController->getValue("bid",pos);
	updateStopLoss();
}

void SCMovingExpandingStop::updateStopLoss() {
	if ( m_BuySell == "BUY" ) {
		double relative = abs( askLastChange - askOpen ) * m_stopLossRel;
		stopLoss = max( m_stopLossAbs, relative );
	} else if ( m_BuySell == "SELL" ) {
		double relative = abs( bidLastChange - bidOpen ) * m_stopLossRel;
		stopLoss = max( m_stopLossAbs, relative );
	}
}
