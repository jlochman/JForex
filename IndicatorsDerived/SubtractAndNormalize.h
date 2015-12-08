/*
 * SubtractAndNormalize.h
 *
 *  Created on: Sep 11, 2015
 *      Author: jlochman
 */

#ifndef INDICATORSDERIVED_SUBTRACTANDNORMALIZE_H_
#define INDICATORSDERIVED_SUBTRACTANDNORMALIZE_H_

#include "../DataController/IndicatorDerivedDataController.h"

class SubtractAndNormalize: public IndicatorDerivedDataController {
public:
	SubtractAndNormalize(string branchName, const vector<double>* vec1, const vector<double>* vec2);
	virtual ~SubtractAndNormalize();

protected:
	const vector<double>* m_inVec2;
	double 	m_mean;
	double 	m_range;

	void calcMeanAndRange();

	double calcValue(int pos);
	bool canCalc(int pos);
};

#endif /* INDICATORSDERIVED_SUBTRACTANDNORMALIZE_H_ */
