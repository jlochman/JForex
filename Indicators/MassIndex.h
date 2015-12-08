/*
 * MassIndex.h
 *
 *  Created on: Sep 6, 2015
 *      Author: jlochman
 */

#ifndef INDICATORS_MASSINDEX_H_
#define INDICATORS_MASSINDEX_H_

#include "../DataController/IndicatorDataController.h"

class MassIndex: public IndicatorDataController {
public:
	MassIndex(string branchName, int calculateSize, double alpha, const vector<double>* in_vec);
	virtual ~MassIndex();

	static double getMassIndex(const vector<double>* in_vec, int fromPos, int length, double alpha, double weight = 0);

private:
	const vector<double>* input_vec;
	double m_alpha;
	double m_weight;

protected:
	double calcValue(int pos);
	bool canCalc(int pos);
};

#endif /* INDICATORS_MASSINDEX_H_ */
