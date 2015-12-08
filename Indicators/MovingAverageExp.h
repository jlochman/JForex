/*
 * MovingAverageExp.h
 *
 *  Created on: Jul 17, 2015
 *      Author: jlochman
 */

#ifndef INDICATORS_MOVINGAVERAGEEXP_H_
#define INDICATORS_MOVINGAVERAGEEXP_H_

#include "../DataController/IndicatorDataController.h"

class MovingAverageExp: public IndicatorDataController {
public:
	MovingAverageExp(string branchName, int calculateSize, double alpha, const vector<double>* in_vec);
	virtual ~MovingAverageExp();

	static double getMeanExp(const vector<double>* in_vec, int fromPos, int length, double alpha, double weight = 0);
	static double calcTotalWeight(double alpha, int length);

private:
	const vector<double>* input_vec;
	double m_alpha;
	double m_weight;

protected:
	double calcValue(int pos);
	bool canCalc(int pos);
};

#endif /* INDICATORS_MOVINGAVERAGEEXP_H_ */
