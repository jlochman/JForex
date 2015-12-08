/*
 * GenericStrategy.h
 *
 *  Created on: Aug 6, 2015
 *      Author: jlochman
 */

#ifndef STRATEGYSELECTOR_GENERICSTRATEGY_H_
#define STRATEGYSELECTOR_GENERICSTRATEGY_H_

#include "assert.h"

#include "../DataController/GenericDataController.h"

class GenericStrategy {
public:
	GenericStrategy(int size, GenericDataController* stratOpen1,
			GenericDataController* stratClose);
	virtual ~GenericStrategy();

	void clear();
	void calculate();

	double getProfit();
	double getGoodProfit();
	double getBadProfit();

	double getProfitSigma();

	int getNumberOfTrades();
	int getNumberOfGoodTrades();
	int getNumberOfBadTrades();

	double getProfitPerTrade();
	double getProfitPerGoodTrade();
	double getProfitPerBadTrade();

	void coutOverview();
	void coutAllTrades();

	virtual string getName() = 0;
	virtual bool checkTradeOpen(int pos) = 0;

private:
	int		MAX_NUMBER_OF_TRADES_TO_COUT;

protected:
	vector<double>	m_profit_vec;
	vector<double>	m_pos_vec;
	int				m_size;
	string			m_name;

	double 			m_profit;
	double 			m_goodProfit;
	double 			m_badProfit;

	double			m_profitSigma;

	int 			m_numTrades;
	int 			m_numGoodTrades;
	int				m_numBadTrades;

	double 			m_profitPerTrade;
	double			m_profitPerGoodTrade;
	double			m_profitPerBadTrade;

	GenericDataController* m_stratOpen1;
	GenericDataController* m_stratClose;
};

#endif /* STRATEGYSELECTOR_GENERICSTRATEGY_H_ */
