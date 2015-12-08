/*
 * UlcerIndex.h
 *
 *  Created on: Sep 6, 2015
 *      Author: jlochman
 */

#ifndef INDICATORS_ULCERINDEX_H_
#define INDICATORS_ULCERINDEX_H_

#include "../DataController/IndicatorDataController.h"

class UlcerIndex: public IndicatorDataController {
public:
	UlcerIndex(string branchName, int calculateSize, const vector<double>* in_vec);
	virtual ~UlcerIndex();

	static double getUlicerIndex(const vector<double>* in_vec, int fromPos, int length);

private:
	const vector<double>* input_vec;

protected:
	double calcValue(int pos);
	bool canCalc(int pos);
};

#endif /* INDICATORS_ULCERINDEX_H_ */
