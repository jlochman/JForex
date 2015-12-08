/*
 * MovingAverage.h
 *
 *  Created on: Jun 22, 2015
 *      Author: jlochman
 */

#ifndef INDICATORS_MOVINGAVERAGE_H_
#define INDICATORS_MOVINGAVERAGE_H_

#include "../DataController/IndicatorDataController.h"

class MovingAverage: public IndicatorDataController {
public:
	MovingAverage(string branchName, int calculateSize, const vector<double>* in_vec);
	virtual ~MovingAverage();

	static double getMean(const vector<double>* in_vec, int fromPos, int length);

private:
	const vector<double>* input_vec;

protected:
	double calcValue(int pos);
	bool canCalc(int pos);
};

#endif /* INDICATORS_MOVINGAVERAGE_H_ */
