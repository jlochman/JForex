/*
 * MACD.h
 *
 *  Created on: Sep 5, 2015
 *      Author: jlochman
 */

#ifndef INDICATORS_MACD_H_
#define INDICATORS_MACD_H_

#include "../DataController/IndicatorDataController.h"

class MACD: public IndicatorDataController {
public:
	MACD(string branchName, int calculateSize, double alpha, const vector<double>* in_vec);
	virtual ~MACD();

	static double getMACD(const vector<double>* in_vec, int fromPos, int length, double alpha, double weight_short = 0, double weight_long = 0);

private:
	const vector<double>* input_vec;
	double m_alpha;
	double m_weight_short;
	double m_weight_long;

protected:
	double calcValue(int pos);
	bool canCalc(int pos);
};

#endif /* INDICATORS_MACD_H_ */
