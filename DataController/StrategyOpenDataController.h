/*
 * StrategyOpenDataController.h
 *
 *  Created on: Jul 16, 2015
 *      Author: jlochman
 */

#ifndef DATACONTROLLER_STRATEGYOPENDATACONTROLLER_H_
#define DATACONTROLLER_STRATEGYOPENDATACONTROLLER_H_

#include "GenericDataController.h"

class StrategyOpenDataController: public GenericDataController {
public:
	StrategyOpenDataController(string branchName);
	virtual ~StrategyOpenDataController();

	void calculate(int maxCount);

	virtual bool canCalc(int pos) = 0;
	virtual bool checkOpen(int pos) = 0;

private:
	int DEAD_TIME_AFTER_ORDER;
};

#endif /* DATACONTROLLER_STRATEGYOPENDATACONTROLLER_H_ */
