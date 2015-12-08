/*
 * AbsolutePriceOscilator.h
 *
 *  Created on: Jul 24, 2015
 *      Author: jlochman
 */

#ifndef INDICATORS_ABSOLUTEPRICEOSCILATOR_H_
#define INDICATORS_ABSOLUTEPRICEOSCILATOR_H_

#include "../DataController/IndicatorDataController.h"

class AbsolutePriceOscilator: public IndicatorDataController {

public:
	AbsolutePriceOscilator(string branchName, int calculateSize, double alpha, const vector<double>* in_vec);
	virtual ~AbsolutePriceOscilator();

	static double getAPO(const vector<double>* in_vec, int fromPos, int length, double alpha, double weight = 0);

private:
	const vector<double>* input_vec;
	double m_alpha;
	double m_weight;

	static double calcTotalWeight(double alpha, int length);

protected:
	double calcValue(int pos);
	bool canCalc(int pos);
};

#endif /* INDICATORS_ABSOLUTEPRICEOSCILATOR_H_ */
