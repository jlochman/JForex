/*
 * CommodityChannelIndex.h
 *
 *  Created on: Sep 5, 2015
 *      Author: jlochman
 */

#ifndef INDICATORS_COMMODITYCHANNELINDEX_H_
#define INDICATORS_COMMODITYCHANNELINDEX_H_

#include "../DataController/IndicatorDataController.h"

class CommodityChannelIndex: public IndicatorDataController {
public:
	CommodityChannelIndex(string branchName, int calculateSize, const vector<double>* in_vec);
	virtual ~CommodityChannelIndex();

	static double getCCI(const vector<double>* in_vec, int fromPos, int length);

private:
	const vector<double>* input_vec;

protected:
	double calcValue(int pos);
	bool canCalc(int pos);
};

#endif /* INDICATORS_COMMODITYCHANNELINDEX_H_ */
