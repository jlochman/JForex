/*
 * GenericStrategy.cpp
 *
 *  Created on: Aug 6, 2015
 *      Author: jlochman
 */

#include <iostream>

#include "GenericStrategy.h"
#include "../Indicators/Sigma.h"

GenericStrategy::GenericStrategy(int size, GenericDataController* stratOpen1,
		GenericDataController* stratClose) {
	MAX_NUMBER_OF_TRADES_TO_COUT = 300;

	m_stratOpen1 = stratOpen1;
	m_stratClose = stratClose;
	m_size = size;

	clear();
}

GenericStrategy::~GenericStrategy() {
}

void GenericStrategy::clear() {
	m_profit_vec.resize(0);
	m_pos_vec.resize(0);
	m_name = "";

	m_profit = 0;
	m_goodProfit = 0;
	m_badProfit = 0;

	m_profitSigma = 0;

	m_numTrades = 0;
	m_numGoodTrades = 0;
	m_numBadTrades = 0;

	m_profitPerTrade = 0;
	m_profitPerGoodTrade = 0;
	m_profitPerBadTrade = 0;
}

void GenericStrategy::calculate() {
	m_name = this->getName();

	for ( int i = 0; i < m_size; i++ ) {
		if ( this->checkTradeOpen(i) ) {
			m_profit_vec.push_back( m_stratClose->getValue(i) );
			m_pos_vec.push_back( i );
		}
	}

	m_profit = getProfit();
	m_goodProfit = getGoodProfit();
	m_badProfit = getBadProfit();

	m_profitSigma = getProfitSigma();

	m_numTrades = getNumberOfTrades();
	m_numGoodTrades = getNumberOfGoodTrades();
	m_numBadTrades = getNumberOfBadTrades();

	m_profitPerTrade = getProfitPerTrade();
	m_profitPerGoodTrade = getProfitPerGoodTrade();
	m_profitPerBadTrade = getProfitPerBadTrade();
}

double GenericStrategy::getProfit() {
	if ( m_profit != 0 ) return m_profit;
	double x = 0;
	for ( int i = 0; i < m_profit_vec.size(); i++ ) {
		x += m_profit_vec.at(i);
	}
	return x;
}

double GenericStrategy::getGoodProfit() {
	if ( m_goodProfit != 0 ) return m_goodProfit;
	double x = 0;
	for ( int i = 0; i < m_profit_vec.size(); i++ ) {
		if ( m_profit_vec.at(i) >= 0 ) x += m_profit_vec.at(i);
	}
	return x;
}

double GenericStrategy::getBadProfit() {
	if ( m_badProfit != 0 ) return m_badProfit;
	double x = 0;
	for ( int i = 0; i < m_profit_vec.size(); i++ ) {
		if ( m_profit_vec.at(i) < 0 ) x += m_profit_vec.at(i);
	}
	return x;
}

double GenericStrategy::getProfitSigma() {
	if ( m_profitSigma != 0 ) return m_profitSigma;
	return Sigma::getSigma( &m_profit_vec, 0, m_profit_vec.size() );
}

int GenericStrategy::getNumberOfTrades() {
	return m_profit_vec.size();
}

int GenericStrategy::getNumberOfGoodTrades() {
	if ( m_numGoodTrades != 0 ) return m_numGoodTrades;
	int num = 0;
	for ( int i = 0; i < m_profit_vec.size(); i++ ) {
		if ( m_profit_vec.at(i) >= 0 ) num++;
	}
	return num;
}

int GenericStrategy::getNumberOfBadTrades() {
	if ( m_numBadTrades != 0 ) return m_numBadTrades;
	int num = 0;
	for ( int i = 0; i < m_profit_vec.size(); i++ ) {
		if ( m_profit_vec.at(i) < 0 ) num++;
	}
	return num;
}

double GenericStrategy::getProfitPerTrade() {
	if ( m_profitPerTrade != 0 ) return m_profitPerTrade;
	if ( m_numTrades == 0 ) return 0;
	return ( m_profit / m_numTrades );
}

double GenericStrategy::getProfitPerGoodTrade() {
	if ( m_profitPerGoodTrade != 0 ) return m_profitPerGoodTrade;
	if ( m_numGoodTrades == 0 ) return 0;
	return m_goodProfit / m_numGoodTrades;
}

double GenericStrategy::getProfitPerBadTrade() {
	if ( m_profitPerBadTrade != 0 ) return m_profitPerBadTrade;
	if ( m_numBadTrades == 0 ) return 0;
	return m_badProfit / m_numBadTrades;
}

void GenericStrategy::coutOverview() {
	cout << m_name << endl;
	cout << "   Profit: " << m_profit << " ± " << m_profitSigma * sqrt(m_numTrades);
	cout << " [ " << m_goodProfit << " / " << m_badProfit << " ]";
	cout << "  Trades: " << m_numTrades;
	cout << " [ " << m_numGoodTrades << " / " << m_numBadTrades << " ]";
	if ( m_numTrades > 0 )
		cout << " ( " << 100 * m_numGoodTrades / m_numTrades << " % )";
	cout << "  ProfitPerTrade: " << m_profitPerTrade << " ± " << m_profitSigma;
	cout << " [ " << m_profitPerGoodTrade << " / " << m_profitPerBadTrade << " ]";
	cout << endl;
}

void GenericStrategy::coutAllTrades() {
	cout << "   ";
	for ( int i = 0; i < min(m_numTrades, MAX_NUMBER_OF_TRADES_TO_COUT); i++ ) {
		cout << "[" << m_pos_vec.at(i) << "]: ";
		cout << m_profit_vec.at(i) << " , ";
	}
	cout << endl;
}
