/*
 * IndicatorDerivedDataController.h
 *
 *  Created on: Jun 24, 2015
 *      Author: jlochman
 */

#ifndef DATACONTROLLER_INDICATORDERIVEDDATACONTROLLER_H_
#define DATACONTROLLER_INDICATORDERIVEDDATACONTROLLER_H_

#include "GenericDataController.h"

class IndicatorDerivedDataController: public GenericDataController {
public:
	IndicatorDerivedDataController(string branchName, const vector<double>* vec);
	virtual ~IndicatorDerivedDataController();

	void calculate(int maxCount);

protected:
	const vector<double>* m_inVec1;

	virtual double calcValue(int pos) = 0;
	virtual bool canCalc(int pos) = 0;
};

#endif /* DATACONTROLLER_INDICATORDERIVEDDATACONTROLLER_H_ */
