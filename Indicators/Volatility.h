/*
 * Volatility.h
 *
 *  Created on: Sep 5, 2015
 *      Author: jlochman
 */

#ifndef INDICATORS_VOLATILITY_H_
#define INDICATORS_VOLATILITY_H_

#include "../DataController/IndicatorDataController.h"

class Volatility: public IndicatorDataController {
public:
	Volatility(string branchName, int calculateSize, const vector<double>* in_vec);
	virtual ~Volatility();

	static double getVolatility(const vector<double>* in_vec, int fromPos, int length);

private:
	const vector<double>* input_vec;

protected:
	double calcValue(int pos);
	bool canCalc(int pos);
};

#endif /* INDICATORS_VOLATILITY_H_ */
