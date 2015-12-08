/*
 * CommodityChannelIndex.cpp
 *
 *  Created on: Sep 5, 2015
 *      Author: jlochman
 */

#include "MovingAverage.h"
#include "Sigma.h"

#include "CommodityChannelIndex.h"

CommodityChannelIndex::CommodityChannelIndex(string branchName,
		int calculateSize, const vector<double>* in_vec)
	: IndicatorDataController(branchName, calculateSize) {

	input_vec = in_vec;
}

CommodityChannelIndex::~CommodityChannelIndex() {
}

double CommodityChannelIndex::getCCI(const vector<double>* in_vec, int fromPos,
		int length) {

	if ( fromPos + length > in_vec->size() ) return 0;
	if ( length <= 0 ) return 0;

	double mean = MovingAverage::getMean( in_vec, fromPos, length );
	double sigma = Sigma::getSigma( in_vec, fromPos, length );
	double price = in_vec->at(fromPos);

	if ( sigma == 0 ) return 0;

	return ( price - mean ) / ( 5 * sigma );
}

double CommodityChannelIndex::calcValue(int pos) {
	return getCCI( input_vec, pos, calcSize );
}

bool CommodityChannelIndex::canCalc(int pos) {
	return ( pos < input_vec->size() - getHistNeeded() );
}
