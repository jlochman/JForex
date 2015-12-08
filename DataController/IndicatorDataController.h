/*
 * IndicatorDataController.h
 *
 *  Created on: Jun 22, 2015
 *      Author: jlochman
 */

#ifndef DATACONTROLLER_INDICATORDATACONTROLLER_H_
#define DATACONTROLLER_INDICATORDATACONTROLLER_H_

#include "GenericDataController.h"

class IndicatorDataController: public GenericDataController {
public:
	IndicatorDataController(string branchName, int calculateSize);
	virtual ~IndicatorDataController();

	void calculate(int maxCount);

protected:
	int calcInHist;
	int calcSize;

	virtual double calcValue(int pos) = 0;
	virtual bool canCalc(int pos) = 0;
	void calcHistNeeded();
};

#endif /* DATACONTROLLER_INDICATORDATACONTROLLER_H_ */
