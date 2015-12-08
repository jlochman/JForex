/*
 * TypicalPrice.h
 *
 *  Created on: Nov 26, 2015
 *      Author: jlochman
 */

#ifndef INDICATORS_TYPICALPRICE_H_
#define INDICATORS_TYPICALPRICE_H_

#include "../DataController/IndicatorDataController.h"

class TypicalPrice: public IndicatorDataController {
public:
	TypicalPrice(string branchName, int calculateSize, const vector<double>* in_vec);
	virtual ~TypicalPrice();

	static double getTypicalPrice(const vector<double>* in_vec, int fromPos, int length);

private:
	const vector<double>* input_vec;

protected:
	double calcValue(int pos);
	bool canCalc(int pos);
};

#endif /* INDICATORS_TYPICALPRICE_H_ */
