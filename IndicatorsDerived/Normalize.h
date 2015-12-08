/*
 * Normalize.h
 *
 *  Created on: Sep 1, 2015
 *      Author: jlochman
 */

#ifndef INDICATORSDERIVED_NORMALIZE_H_
#define INDICATORSDERIVED_NORMALIZE_H_

#include "../DataController/IndicatorDerivedDataController.h"

class Normalize: public IndicatorDerivedDataController {
public:
	Normalize(string branchName, const vector<double>* vec1);
	virtual ~Normalize();

protected:
	double m_mean;
	double m_range;

	double calcValue(int pos);
	bool canCalc(int pos);
};

#endif /* INDICATORSDERIVED_NORMALIZE_H_ */
