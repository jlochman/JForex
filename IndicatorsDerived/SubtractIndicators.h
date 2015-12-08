/*
 * Subtraction.h
 *
 *  Created on: Jun 24, 2015
 *      Author: jlochman
 */

#ifndef INDICATORSDERIVED_SUBTRACTINDICATORS_H_
#define INDICATORSDERIVED_SUBTRACTINDICATORS_H_

#include "../DataController/IndicatorDerivedDataController.h"

class SubtractIndicators: public IndicatorDerivedDataController {
public:
	SubtractIndicators(string branchName, const vector<double>* vec1, const vector<double>* vec2);
	virtual ~SubtractIndicators();

protected:
	const vector<double>* m_inVec2;

	double calcValue(int pos);
	bool canCalc(int pos);
};

#endif /* INDICATORSDERIVED_SUBTRACTION_H_ */
