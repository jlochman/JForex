/*
 * SCMovingStop.h
 *
 *  Created on: Jul 16, 2015
 *      Author: jlochman
 */

#ifndef STRATEGYCLOSE_SCMOVINGSTOP_H_
#define STRATEGYCLOSE_SCMOVINGSTOP_H_

#include "../DataController/StrategyCloseDataController.h"

class SCMovingStop: public StrategyCloseDataController {
public:
	SCMovingStop(string branchName, InputFileController* inputFileController,
			string buySell, double stopLoss);
	virtual ~SCMovingStop();

private:
	double m_stopLoss;

	double askOpen;
	double bidOpen;

	int posStart;

	bool canCalc(int pos);
	bool checkClose(int pos);

	void setAskBid(int pos);
};

#endif /* STRATEGYCLOSE_SCMOVINGSTOP_H_ */
