/*
 * AddIndicators.h
 *
 *  Created on: Aug 9, 2015
 *      Author: jlochman
 */

#ifndef INDICATORSDERIVED_ADDINDICATORS_H_
#define INDICATORSDERIVED_ADDINDICATORS_H_

#include "../DataController/IndicatorDerivedDataController.h"

class AddIndicators: public IndicatorDerivedDataController {
public:
	AddIndicators(string branchName, const vector<double>* vec1, const vector<double>* vec2);
	virtual ~AddIndicators();

protected:
	const vector<double>* m_inVec2;

	double calcValue(int pos);
	bool canCalc(int pos);
};

#endif /* INDICATORSDERIVED_ADDINDICATORS_H_ */
