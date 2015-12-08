/*
 * Subtract.h
 *
 *  Created on: Jul 17, 2015
 *      Author: jlochman
 */

#ifndef INDICATORSDERIVED_SUBTRACT_H_
#define INDICATORSDERIVED_SUBTRACT_H_

#include "../DataController/IndicatorDerivedDataController.h"

class Subtract: public IndicatorDerivedDataController {
public:
	Subtract(string branchName, double subtractBy, const vector<double>* vec1);
	virtual ~Subtract();

protected:
	double calcValue(int pos);
	bool canCalc(int pos);
	int m_subtractBy;
};

#endif /* INDICATORSDERIVED_SUBTRACT_H_ */
