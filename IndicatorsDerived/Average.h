/*
 * Average.h
 *
 *  Created on: Sep 10, 2015
 *      Author: jlochman
 */

#ifndef INDICATORSDERIVED_AVERAGE_H_
#define INDICATORSDERIVED_AVERAGE_H_

#include "../DataController/IndicatorDerivedDataController.h"

class Average: public IndicatorDerivedDataController {
public:
	Average(string branchName, const vector<double>* vec1, const vector<double>* vec2);
	virtual ~Average();

protected:
	const vector<double>* m_inVec2;

	double calcValue(int pos);
	bool canCalc(int pos);
};

#endif /* INDICATORSDERIVED_AVERAGE_H_ */
