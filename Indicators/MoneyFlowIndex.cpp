/*
 * MoneyFlowIndex.cpp
 *
 *  Created on: Sep 6, 2015
 *      Author: jlochman
 */

#include "MoneyFlowIndex.h"

MoneyFlowIndex::MoneyFlowIndex(string branchName, int calculateSize,
		const vector<double>* price_vec, const vector<double>* volume_vec)
	: IndicatorDataController(branchName, calculateSize) {

	m_price_vec = price_vec;
	m_volume_vec = volume_vec;
}

MoneyFlowIndex::~MoneyFlowIndex() {
}

double MoneyFlowIndex::getMFI(const vector<double>* price_vec, const vector<double>* volume_vec,
		int fromPos, int length) {

	if ( fromPos + length > price_vec->size() - 1 ) return 0;
	if ( fromPos + length > volume_vec->size() - 1 ) return 0;
	if ( length <= 0 ) return 0;

	double posMoneyFlow = 0;
	double negMoneyFlow = 0;
	double priceChange = 0;

	for ( int i = fromPos; i < fromPos + length - 1; i++ ) {
		priceChange = price_vec->at( i ) - price_vec->at( i+1 );
		if ( priceChange > 0 )
			posMoneyFlow += price_vec->at( i + 1 ) * volume_vec->at( i + 1 );
		else negMoneyFlow += price_vec->at( i + 1 ) * volume_vec->at( i + 1 );
	}

	double moneyFlowRatio;
	if ( negMoneyFlow != 0 ) moneyFlowRatio = posMoneyFlow / negMoneyFlow;
	else moneyFlowRatio = 0;

	return ( 1 - 1/(1+moneyFlowRatio) );
}

double MoneyFlowIndex::calcValue(int pos) {
	return getMFI( m_price_vec, m_volume_vec, pos, calcSize );
}

bool MoneyFlowIndex::canCalc(int pos) {
	return ( pos < m_price_vec->size() - getHistNeeded() - 1
			&& pos < m_volume_vec->size() - getHistNeeded() - 1 );
}
