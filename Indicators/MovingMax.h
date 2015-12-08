/*
 * MovingMax.h
 *
 *  Created on: Aug 28, 2015
 *      Author: jlochman
 */

#ifndef INDICATORS_MOVINGMAX_H_
#define INDICATORS_MOVINGMAX_H_

#include "../DataController/IndicatorDataController.h"

class MovingMax: public IndicatorDataController {
public:
	MovingMax(string branchName, int calculateSize, const vector<double>* in_vec);
	virtual ~MovingMax();

	static double getMax(const vector<double>* in_vec, int fromPos, int length);
	static int getMaxPos(const vector<double>* in_vec, int fromPos, int length);

private:
	const vector<double>* input_vec;

protected:
	double calcValue(int pos);
	bool canCalc(int pos);
};

#endif /* INDICATORS_MOVINGMAX_H_ */
