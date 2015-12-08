/*
 * FixedStop.cpp
 *
 *  Created on: Jul 14, 2015
 *      Author: jlochman
 */

#include "SCFixedStop.h"

#include <iostream>


SCFixedStop::SCFixedStop(string branchName, InputFileController* inputFileController,
		string buySell, double askStop, double bidStop)
	: StrategyCloseDataController(branchName, inputFileController, buySell){

	m_askStop = askStop;
	m_bidStop = bidStop;

	askOpen = 0;
	bidOpen = 0;
	posStart = 0;
}

SCFixedStop::SCFixedStop(string branchName, InputFileController* inputFileController, string buySell, double stop)
	: StrategyCloseDataController(branchName, inputFileController, buySell) {

	m_askStop = stop;
	m_bidStop = stop;

	askOpen = 0;
	bidOpen = 0;
	posStart = 0;
}

SCFixedStop::~SCFixedStop() {
}

bool SCFixedStop::canCalc(int pos) {
	bool result = ( pos < m_InputFileController->getMinVecSize() ) ;
	if ( result ) {
		askOpen = m_InputFileController->getValue("ask",pos);
		bidOpen = m_InputFileController->getValue("bid",pos);
		posStart = pos;
	}
	return ( result );
}

bool SCFixedStop::checkClose(int pos) {
	bool result = false;
	if ( m_InputFileController->getValue("ask",pos) > askOpen + m_askStop ) {
		result = true;
	}
	if ( m_InputFileController->getValue("bid",pos) < bidOpen - m_bidStop ) {
		result = true;
	}
	return ( result );
}
