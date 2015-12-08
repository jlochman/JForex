/*
 * SCFixedStop.h
 *
 *  Created on: Jul 14, 2015
 *      Author: jlochman
 */

#ifndef STRATEGYCLOSE_SCFIXEDSTOP_H_
#define STRATEGYCLOSE_SCFIXEDSTOP_H_

#include "../DataController/StrategyCloseDataController.h"

class SCFixedStop: public StrategyCloseDataController {
public:
	SCFixedStop(string branchName, InputFileController* inputFileController,
			string buySell, double askStop, double bidStop);
	SCFixedStop(string branchName, InputFileController* inputFileController,
			string buySell, double Stop);
	virtual ~SCFixedStop();

private:
	double m_askStop;
	double m_bidStop;

	double askOpen;
	double bidOpen;

	int posStart;

	bool canCalc(int pos);
	bool checkClose(int pos);
};

#endif /* STRATEGYCLOSE_SCFIXEDSTOP_H_ */
