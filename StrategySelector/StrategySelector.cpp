/*
 * StrategySelector.cpp
 *
 *  Created on: Aug 5, 2015
 *      Author: jlochman
 */

#include <iostream>
#include <algorithm>

#include "StrategySelector.h"
#include "Strategy/SSimple.h"
#include "Strategy/SAnd.h"
#include "Strategy/SAndAnd.h"

StrategySelector::StrategySelector(
		StrategyOpenFileController* sOFileController,
		StrategyCloseFileController* sCFileController) {

	cout << "[CALC]  === Strategy Selector ===" << endl;

	m_SCFileController = sCFileController;
	m_SOFileController = sOFileController;

	m_size = min( m_SOFileController->getMinVecSize(), m_SCFileController->getMinVecSize() );

	this->init();
	this->calc();
	this->coutResult();
}

StrategySelector::~StrategySelector() {
}

void StrategySelector::init() {
	for ( int i_close = 0; i_close < m_SCFileController->getGenDCCount(); i_close++ ) {
		for ( int i = 0; i < m_SOFileController->getGenDCCount(); i++ ) {
			for ( int j = i+1; j < m_SOFileController->getGenDCCount(); j++ ) {
				strategy_vec.push_back( new SAnd( m_size, m_SOFileController->getGenDCByIndex(i),
						m_SOFileController->getGenDCByIndex(j),
						m_SCFileController->getGenDCByIndex(i_close) ) );
				for ( int k = j+1; k < m_SOFileController->getGenDCCount(); k++ ) {
					strategy_vec.push_back( new SAndAnd( m_size, m_SOFileController->getGenDCByIndex(i),
							m_SOFileController->getGenDCByIndex(j),
							m_SOFileController->getGenDCByIndex(k),
							m_SCFileController->getGenDCByIndex(i_close) ) );
				}
			}
		}
	}
}

void StrategySelector::calc() {
	for ( int i = 0; i < strategy_vec.size(); i++ ) {
		strategy_vec.at(i)->calculate();
	}
}

void StrategySelector::coutResult() {
	vector<stratSort> stratSort;
	int size = 0;
	for ( int i = 0; i < strategy_vec.size(); i++ ) {

		if ( strategy_vec.at(i)->getNumberOfTrades() > 9
				&& strategy_vec.at(i)->getProfit() > 0
				&& strategy_vec.at(i)->getNumberOfGoodTrades() > strategy_vec.at(i)->getNumberOfBadTrades() ) {
			size++;
			stratSort.resize(size);
			stratSort.at(size-1).pos = i;
			stratSort.at(size-1).profit = strategy_vec.at(i)->getProfit();
			stratSort.at(size-1).profit_per_trade = strategy_vec.at(i)->getProfitPerTrade();
			stratSort.at(size-1).profit_stat_min = strategy_vec.at(i)->getProfit()
					- strategy_vec.at(i)->getProfitSigma();
		}
	}
	sort( stratSort.begin(), stratSort.end(), cmpProfit);
	cout << "=== HIGHEST PROFIT ===" << endl;
	for ( int i = 0; i < 5; i++ ) {
		strategy_vec.at( stratSort.at(i).pos )->coutOverview();
		strategy_vec.at( stratSort.at(i).pos )->coutAllTrades();
	}
	sort( stratSort.begin(), stratSort.end(), cmpProfitStatMin);
	cout << "=== HIGHEST PROFIT STATISTICAL MINIMUM ===" << endl;
	for ( int i = 0; i < 5; i++ ) {
		strategy_vec.at( stratSort.at(i).pos )->coutOverview();
		strategy_vec.at( stratSort.at(i).pos )->coutAllTrades();
	}
}

bool cmpProfit(const stratSort& s1, const stratSort& s2)
{
	return s1.profit > s2.profit;
}

bool cmpProfitPerTrade(const stratSort& s1, const stratSort & s2)
{
	return s1.profit_per_trade > s2.profit_per_trade;
}

bool cmpProfitStatMin(const stratSort& s1, const stratSort & s2) {
	return s1.profit_stat_min > s2.profit_stat_min;
}
