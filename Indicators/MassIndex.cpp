/*
 * MassIndex.cpp
 *
 *  Created on: Sep 6, 2015
 *      Author: jlochman
 */

#include "MovingAverage.h"
#include "MovingAverageExp.h"

#include "MassIndex.h"

MassIndex::MassIndex(string branchName, int calculateSize, double alpha,
		const vector<double>* in_vec)
	: IndicatorDataController( branchName, calculateSize )	{

	input_vec = in_vec;
	m_alpha = alpha;
	m_weight = MovingAverageExp::calcTotalWeight( alpha, calculateSize );
}

MassIndex::~MassIndex() {
}

double MassIndex::getMassIndex(const vector<double>* in_vec, int fromPos,
		int length, double alpha, double weight) {
	int ema_length = (int) ( ( length * 9 ) / 25 );

	if ( weight == 0 ) weight = MovingAverageExp::calcTotalWeight( alpha, length );
	if ( fromPos + length > in_vec->size() - ema_length ) return 0;
	if ( length <= 0 ) return 0;

	double weightEMA = MovingAverageExp::calcTotalWeight( alpha, ema_length );

	vector<double> singleEMA;
	vector<double> doubleEMA;
	vector<double> EMA_ratio;

	for ( int i = 0; i < length + ema_length; i++ ) {
		singleEMA.push_back( MovingAverageExp::getMeanExp( in_vec, fromPos+i, ema_length, alpha, weightEMA ) );
	}
	for ( int i = 0; i < length; i++ ) {
		doubleEMA.push_back( MovingAverageExp::getMeanExp( &singleEMA, i, ema_length, alpha, weightEMA ) );
	}
	for ( int i = 0; i < length; i++ ) {
		if ( doubleEMA.at(i) != 0 )
			EMA_ratio.push_back( singleEMA.at(i) / doubleEMA.at(i) );
		else EMA_ratio.push_back( 0 );
	}
	return 1 - MovingAverage::getMean( &EMA_ratio, 0, EMA_ratio.size() );
}

double MassIndex::calcValue(int pos) {
	return getMassIndex( input_vec, pos, calcSize, m_alpha, m_weight );
}

bool MassIndex::canCalc(int pos) {
	return ( pos < input_vec->size() - getHistNeeded() - ( calcSize * (9/25) ) );
}
