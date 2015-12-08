/*
 * MovingMin.h
 *
 *  Created on: Aug 28, 2015
 *      Author: jlochman
 */

#ifndef INDICATORS_MOVINGMIN_H_
#define INDICATORS_MOVINGMIN_H_

#include "../DataController/IndicatorDataController.h"

class MovingMin: public IndicatorDataController {
public:
	MovingMin(string branchName, int calculateSize, const vector<double>* in_vec);
	virtual ~MovingMin();

	static double getMin(const vector<double>* in_vec, int fromPos, int length);
	static int getMinPos(const vector<double>* in_vec, int fromPos, int length);

private:
	const vector<double>* input_vec;

protected:
	double calcValue(int pos);
	bool canCalc(int pos);
};

#endif /* INDICATORS_MOVINGMIN_H_ */
