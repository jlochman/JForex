/*
 * EfficiencyRatio.h
 *
 *  Created on: Sep 5, 2015
 *      Author: jlochman
 */

#ifndef INDICATORS_EFFICIENCYRATIO_H_
#define INDICATORS_EFFICIENCYRATIO_H_

#include "../DataController/IndicatorDataController.h"

class EfficiencyRatio: public IndicatorDataController {
public:
	EfficiencyRatio(string branchName, int calculateSize, const vector<double>* in_vec);
	virtual ~EfficiencyRatio();

	static double getEffRatio(const vector<double>* in_vec, int fromPos, int length);

private:
	const vector<double>* input_vec;

protected:
	double calcValue(int pos);
	bool canCalc(int pos);
};

#endif /* INDICATORS_EFFICIENCYRATIO_H_ */
