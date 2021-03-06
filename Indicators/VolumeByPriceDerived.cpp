/*
 * VolumeByPriceDerived.cpp
 *
 *  Created on: Sep 16, 2015
 *      Author: jlochman
 */

#include <iostream>

#include "MovingMax.h"
#include "MovingMin.h"

#include <TH1F.h>

#include "VolumeByPriceDerived.h"

VolumeByPriceDerived::VolumeByPriceDerived(string branchName, int calculateSize,
		const vector<double>* priceVec, const vector<double>* volumeVec)
	: IndicatorDataController(branchName, calculateSize) {

	m_priceVec = priceVec;
	m_volumeVec = volumeVec;
}

VolumeByPriceDerived::~VolumeByPriceDerived() {
}

double VolumeByPriceDerived::getVolumeByPriceDerived(
		const vector<double>* priceVec, const vector<double>* volumeVec,
		int fromPos, int length) {

	if ( fromPos + length > priceVec->size() ) return 0;
	if ( fromPos + length > volumeVec->size() ) return 0;
	if ( length <= 0 ) return 0;

	double min = MovingMin::getMin( priceVec, fromPos, length );
	double max = MovingMax::getMax( priceVec, fromPos, length );
	double eps = ( max - min ) * 1e-6;
	TH1F* hist = new TH1F("myHist", "myHist", 50, min - eps, max + eps);

	for ( int i = fromPos; i < fromPos + length; i++ ) {
		hist->Fill( priceVec->at(i), volumeVec->at(i) );
	}

	double x = hist->GetMean() - priceVec->at(fromPos);
	delete hist;
	return x;
}

double VolumeByPriceDerived::calcValue(int pos) {
	return getVolumeByPriceDerived( m_priceVec, m_volumeVec, pos, calcSize );
}

bool VolumeByPriceDerived::canCalc(int pos) {
	return ( pos < m_priceVec->size() - getHistNeeded()
			&& pos < m_volumeVec->size() - getHistNeeded() );
}
