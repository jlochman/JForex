/*
 * MovingAverageLin.h
 *
 *  Created on: Jul 17, 2015
 *      Author: jlochman
 */

#ifndef INDICATORS_MOVINGAVERAGELIN_H_
#define INDICATORS_MOVINGAVERAGELIN_H_

#include "../DataController/IndicatorDataController.h"

class MovingAverageLin: public IndicatorDataController {
public:
	MovingAverageLin(string branchName, int calculateSize, const vector<double>* in_vec);
	virtual ~MovingAverageLin();

	static double getMeanLin(const vector<double>* in_vec, int fromPos, int length, double weight = 0);
	static double calcTotalWeight(int length);

private:
	const vector<double>* input_vec;
	int m_weight;

protected:
	double calcValue(int pos);
	bool canCalc(int pos);
};

#endif /* INDICATORS_MOVINGAVERAGELIN_H_ */
