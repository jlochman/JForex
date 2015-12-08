/*
 * Change.h
 *
 *  Created on: Sep 5, 2015
 *      Author: jlochman
 */

#ifndef INDICATORS_CHANGE_H_
#define INDICATORS_CHANGE_H_

#include "../DataController/IndicatorDataController.h"

class Change: public IndicatorDataController {
public:
	Change(string branchName, int calculateSize, const vector<double>* in_vec);
	virtual ~Change();

	static double getChange(const vector<double>* in_vec, int fromPos, int length);

private:
	const vector<double>* input_vec;

protected:
	double calcValue(int pos);
	bool canCalc(int pos);
};

#endif /* INDICATORS_CHANGE_H_ */
