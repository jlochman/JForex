/*
 * RelativeStrengthIndex.h
 *
 *  Created on: Jul 17, 2015
 *      Author: jlochman
 */

#ifndef INDICATORS_RELATIVESTRENGTHINDEX_H_
#define INDICATORS_RELATIVESTRENGTHINDEX_H_

#include "../DataController/IndicatorDataController.h"

class RelativeStrengthIndex: public IndicatorDataController {
public:
	RelativeStrengthIndex(string branchName, int calculateSize, double alpha, const vector<double>* in_vec);
	virtual ~RelativeStrengthIndex();

	static double getRSI(const vector<double>* in_vec, int fromPos, int length, double alpha, double weight = 0);

private:
	const vector<double>* input_vec;
	double m_alpha;
	double m_weight;

	static double calcTotalWeight(double alpha, int length);

protected:
	double calcValue(int pos);
	bool canCalc(int pos);
};

#endif /* INDICATORS_RELATIVESTRENGTHINDEX_H_ */
