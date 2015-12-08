/*
 * UlcerIndex.cpp
 *
 *  Created on: Sep 6, 2015
 *      Author: jlochman
 */

#include "MovingMax.h"
#include "MovingAverage.h"

#include "UlcerIndex.h"

UlcerIndex::UlcerIndex(string branchName, int calculateSize,
		const vector<double>* in_vec)
	: IndicatorDataController( branchName, calculateSize ) {

	input_vec = in_vec;
}

UlcerIndex::~UlcerIndex() {
}

double UlcerIndex::getUlicerIndex(const vector<double>* in_vec, int fromPos,
		int length) {
	if ( fromPos + 2*length > in_vec->size() ) return 0;
	if ( length <= 0 ) return 0;

	vector<double> percentDrawDown;
	double maxClose = 0;

	for ( int i = fromPos; i < fromPos + length; i++ ) {
		if ( i == fromPos ) {
			maxClose = MovingMax::getMax( in_vec, fromPos, length );
		} else {
			if ( in_vec->at(i+length-1) > maxClose ) {
				maxClose = in_vec->at(i+length-1);
			}
			if ( in_vec->at(i-1) > maxClose ) {
				maxClose = MovingMax::getMax( in_vec, i, length );
			}
		}
		if ( maxClose != 0 ) percentDrawDown.push_back( pow( 100 * ( in_vec->at(i) - maxClose ) / maxClose, 2 ) );
		else percentDrawDown.push_back( 0 );
	}

	double squareAverage = MovingAverage::getMean( &percentDrawDown, 0, percentDrawDown.size() );
	return sqrt( squareAverage );

}

double UlcerIndex::calcValue(int pos) {
	return getUlicerIndex( input_vec, pos, calcSize );
}

bool UlcerIndex::canCalc(int pos) {
	return ( pos < input_vec->size() - getHistNeeded() - calcSize );
}
