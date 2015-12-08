/*
 * SCMovingExpandingStop.h
 *
 *  Created on: Jul 16, 2015
 *      Author: jlochman
 */

#ifndef STRATEGYCLOSE_SCMOVINGEXPANDINGSTOP_H_
#define STRATEGYCLOSE_SCMOVINGEXPANDINGSTOP_H_

#include "../DataController/StrategyCloseDataController.h"

class SCMovingExpandingStop: public StrategyCloseDataController {
public:
	SCMovingExpandingStop(string branchName, InputFileController* inputFileController,
			string buySell, double stopLossAbs, double stopLossRel = 0.5);
	virtual ~SCMovingExpandingStop();

private:
	double m_stopLossAbs;
	double m_stopLossRel;
	double stopLoss;

	double askOpen;
	double bidOpen;
	double askLastChange;
	double bidLastChange;

	int posStart;

	bool canCalc(int pos);
	bool checkClose(int pos);

	void setAskBidOpen(int pos);
	void setAskBidLastChange(int pos);
	void updateStopLoss();
};

#endif /* STRATEGYCLOSE_SCMOVINGEXPANDINGSTOP_H_ */
