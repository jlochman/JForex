/*
 * TypicalPrice.cpp
 *
 *  Created on: Nov 26, 2015
 *      Author: jlochman
 */

#include "TypicalPrice.h"

#include "MovingMax.h"
#include "MovingMin.h"

#include <TH1F.h>

TypicalPrice::TypicalPrice(string branchName, int calculateSize,
		const vector<double>* in_vec)
: IndicatorDataController(branchName, calculateSize) {
	input_vec = in_vec;
}

TypicalPrice::~TypicalPrice() {
}

double TypicalPrice::getTypicalPrice(const vector<double>* in_vec, int fromPos,
		int length) {

	if ( fromPos + length > in_vec->size() ) return 0;
	if ( length <= 0 ) return 0;

	double min = MovingMin::getMin( in_vec, fromPos, length );
	double max = MovingMax::getMax( in_vec, fromPos, length );
	double eps = ( max - min ) * 1e-9;
	TH1F* hist = new TH1F("myHist", "myHist", 20, min - eps, max + eps);

	for ( int i = fromPos; i < fromPos + length; i++ ) {
		hist->Fill( in_vec->at(i) );
	}

	double x = hist->GetBinCenter( hist->GetMaximumBin() );
	delete hist;
	return x;
}

double TypicalPrice::calcValue(int pos) {
	return getTypicalPrice( input_vec, pos, calcSize );
}

bool TypicalPrice::canCalc(int pos) {
	return ( pos < input_vec->size() - getHistNeeded() );
}
