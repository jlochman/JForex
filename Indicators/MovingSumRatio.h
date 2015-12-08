/*
 * MovingSumRatio.h
 *
 *  Created on: Sep 3, 2015
 *      Author: jlochman
 */

#ifndef INDICATORS_MOVINGSUMRATIO_H_
#define INDICATORS_MOVINGSUMRATIO_H_

#include "../DataController/IndicatorDataController.h"

class MovingSumRatio: public IndicatorDataController {
public:
	MovingSumRatio(string branchName, int calculateSize, const vector<double>* in_vec1, const vector<double>* in_vec2);
	virtual ~MovingSumRatio();

	static double getMovingSumRatio(const vector<double>* in_vec1, const vector<double>* in_vec2, int fromPos, int length);

private:
	const vector<double>* m_vec1;
	const vector<double>* m_vec2;

protected:
	double calcValue(int pos);
	bool canCalc(int pos);
};

#endif /* INDICATORS_MOVINGSUMRATIO_H_ */
