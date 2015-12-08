/*
 * StrategySelector.h
 *
 *  Created on: Aug 5, 2015
 *      Author: jlochman
 */

#ifndef STRATEGYSELECTOR_STRATEGYSELECTOR_H_
#define STRATEGYSELECTOR_STRATEGYSELECTOR_H_

#include "../DataController/GenericDataController.h"
#include "../FileController/StrategyCloseFileController.h"
#include "../FileController/StrategyOpenFileController.h"
#include "GenericStrategy.h"

struct stratSort {
	int pos;
	double profit;
	double profit_per_trade;
	double profit_stat_min;
};

bool cmpProfit(const stratSort& s1, const stratSort & s2);
bool cmpProfitPerTrade(const stratSort& s1, const stratSort & s2);
bool cmpProfitStatMin(const stratSort& s1, const stratSort & s2);

class StrategySelector {
public:
	StrategySelector(StrategyOpenFileController* sOFileController,
			StrategyCloseFileController* sCFileController);
	virtual ~StrategySelector();

	void init();
	void calc();
	void coutResult();

private:
	StrategyOpenFileController* m_SOFileController;
	StrategyCloseFileController* m_SCFileController;
	vector<GenericStrategy*> strategy_vec;
	int m_size;
};

#endif /* STRATEGYSELECTOR_STRATEGYSELECTOR_H_ */
