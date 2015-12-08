/*
 * Sigma.h
 *
 *  Created on: Jul 17, 2015
 *      Author: jlochman
 */

#ifndef INDICATORS_SIGMA_H_
#define INDICATORS_SIGMA_H_

#include "../DataController/IndicatorDataController.h"
#include "MovingAverage.h"

class Sigma: public IndicatorDataController {
public:
	Sigma(string branchName, int calculateSize, const vector<double>* in_vec);
	Sigma(string branchName, int calculateSize, double power, const vector<double>* in_vec);
	virtual ~Sigma();

	static double getSigma(const vector<double>* in_vec, int fromPos, int length, double power = 2);

private:
	const vector<double>* input_vec;
	double m_power;

protected:
	double calcValue(int pos);
	bool canCalc(int pos);
};

#endif /* INDICATORS_SIGMA_H_ */
