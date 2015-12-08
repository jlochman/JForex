/*
 * MACD.cpp
 *
 *  Created on: Sep 5, 2015
 *      Author: jlochman
 */

#include <iostream>

#include "MovingAverageExp.h"

#include "MACD.h"

MACD::MACD(string branchName, int calculateSize, double alpha, const vector<double>* in_vec)
	: IndicatorDataController(branchName, calculateSize) {

	input_vec = in_vec;
	m_alpha = alpha;
	m_weight = MovingAverageExp::calcTotalWeight( m_alpha, calculateSize );
}

MACD::~MACD() {
}

double MACD::getMACD(const vector<double>* in_vec, int fromPos, int length, double alpha, double weight) {
	int longEMA_length = length;
	int shortEMA_length = (int) ( ( longEMA_length * 12 ) / 26 );
	int	signalLine_length = (int) ( ( longEMA_length * 9 ) / 26 );

	if ( weight == 0 ) weight = MovingAverageExp::calcTotalWeight( alpha, length );
	if ( fromPos + length > in_vec->size() - signalLine_length ) return 0;
	if ( length <= 0 ) return 0;

	vector<double> macdLine_vec;
	macdLine_vec.resize(0);
	double longEMA = 0;
	double shortEMA = 0;
	for ( int i = 0; i < signalLine_length; i++ ) {
		longEMA = MovingAverageExp::getMeanExp( in_vec, fromPos + i, longEMA_length, alpha, weight );
		shortEMA = MovingAverageExp::getMeanExp( in_vec, fromPos + i, shortEMA_length, alpha, weight );
		macdLine_vec.push_back( shortEMA - longEMA );
	}
	double signalLine = MovingAverageExp::getMeanExp( &macdLine_vec, 0, signalLine_length, alpha );
	double macdLine = macdLine_vec.at(0);
	return ( macdLine - signalLine );
}

double MACD::calcValue(int pos) {
	return getMACD( input_vec, pos, calcSize, m_alpha, m_weight );
}

bool MACD::canCalc(int pos) {
	return ( pos < input_vec->size() - getHistNeeded() - ( calcSize * (9/26) ) );
}
