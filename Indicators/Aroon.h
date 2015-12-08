/*
 * Aroon.h
 *
 *  Created on: Sep 5, 2015
 *      Author: jlochman
 */

#ifndef INDICATORS_AROON_H_
#define INDICATORS_AROON_H_

#include "../DataController/IndicatorDataController.h"

class Aroon: public IndicatorDataController {
public:
	Aroon(string branchName, int calculateSize, const vector<double>* in_vec);
	virtual ~Aroon();

	static double getAroon(const vector<double>* in_vec, int fromPos, int length);

private:
	const vector<double>* input_vec;

protected:
	double calcValue(int pos);
	bool canCalc(int pos);
};

#endif /* INDICATORS_AROON_H_ */
