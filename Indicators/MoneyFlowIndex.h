/*
 * MoneyFlowIndex.h
 *
 *  Created on: Sep 6, 2015
 *      Author: jlochman
 */

#ifndef INDICATORS_MONEYFLOWINDEX_H_
#define INDICATORS_MONEYFLOWINDEX_H_

#include "../DataController/IndicatorDataController.h"

class MoneyFlowIndex: public IndicatorDataController {
public:
	MoneyFlowIndex(string branchName, int calculateSize, const vector<double>* price_vec, const vector<double>* volume_vec);
	virtual ~MoneyFlowIndex();

	static double getMFI(const vector<double>* price_vec, const vector<double>* volume_vec, int fromPos, int length);

private:
	const vector<double>* m_price_vec;
	const vector<double>* m_volume_vec;

protected:
	double calcValue(int pos);
	bool canCalc(int pos);
};

#endif /* INDICATORS_MONEYFLOWINDEX_H_ */
