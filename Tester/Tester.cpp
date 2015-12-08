/*
 * Tester.cpp
 *
 *  Created on: Oct 1, 2015
 *      Author: jlochman
 */

#include <iostream>
#include <fstream>
#include <sstream>

#include "Tester.h"

#include "../Indicators/MovingAverage.h"
#include "../Indicators/MovingAverageLin.h"
#include "../Indicators/MovingAverageQuad.h"
#include "../Indicators/MovingAverageExp.h"
#include "../Indicators/RelativeStrengthIndex.h"
#include "../Indicators/AbsolutePriceOscilator.h"
#include "../Indicators/Sigma.h"
#include "../Indicators/MovingMax.h"
#include "../Indicators/MovingMin.h"
#include "../Indicators/MovingPreferedDirection.h"
#include "../Indicators/MovingSumRatio.h"
#include "../Indicators/FibonacciPivotPoints.h"
#include "../Indicators/Volatility.h"
#include "../Indicators/Change.h"
#include "../Indicators/EfficiencyRatio.h"
#include "../Indicators/VolumeByPrice.h"
#include "../Indicators/Aroon.h"
#include "../Indicators/BollingerDerived.h"
#include "../Indicators/CommodityChannelIndex.h"
#include "../Indicators/MACD.h"
#include "../Indicators/MassIndex.h"
#include "../Indicators/MoneyFlowIndex.h"
#include "../Indicators/UlcerIndex.h"
#include "../Indicators/MovingAverageLinInv.h"
#include "../Indicators/VolumeByPriceDerived.h"
#include "../Indicators/WinningFixedStop.h"

Tester::Tester() {
	m_File = "/Users/jlochman/Desktop/data.txt";

	m_askbidVec.resize(0);
	m_askVolVec.resize(0);
	m_askVolbidVolVec.resize(0);
	m_bidVolVec.resize(0);
}

Tester::~Tester() {

}

void Tester::loadData() {
	string line;
	double x, ask, askVol, bid, bidVol;
	ifstream input_file( m_File );
	if (input_file.is_open()) {
		while ( getline(input_file, line) ) {
			stringstream ss(line);
			ss >> x;
			ss >> ask;
			ss >> askVol;
			ss >> bid;
			ss >> bidVol;
			m_askbidVec.push_back( (ask + bid) / 2 );
			m_askVolVec.push_back(askVol);
			m_bidVolVec.push_back(bidVol);
			m_askVolbidVolVec.push_back(askVol + bidVol);
		}
	}

	reverseOrder(m_askbidVec);
	reverseOrder(m_askVolVec);
	reverseOrder(m_bidVolVec);
	reverseOrder(m_askVolbidVolVec);

}

void Tester::printData() {
	cout << "askbid askVol bidBod askVolbidVol" << endl;
	for ( int i = 0; i < m_askbidVec.size(); i++ ) {
		cout << "[" << i+1 << "]  "
				<< m_askbidVec.at(i) << " "
				<< m_askVolVec.at(i) << " "
				<< m_bidVolVec.at(i) << " "
				<< m_askVolbidVolVec.at(i) << endl;
	}
}

void Tester::testData() {
	for ( int i = 0; i < 999; i++ ) {
		cout << "[" << i+1 << "]  ";
		//		<< AbsolutePriceOscilator::getAPO(&m_askbidVec, i, 20, 0.98, 0) << endl;
		//		<< MACD::getMACD(&m_askbidVec, i, 400, 0.98, 0) << endl;
		//		<< MoneyFlowIndex::getMFI(&m_askbidVec, &m_askVolbidVolVec, i, 50) << endl;
		//		<< MoneyFlowIndex::getMFI(&m_askbidVec, &m_askVolbidVolVec, i, 2000) << endl;
		//		<< MassIndex::getMassIndex(&m_askbidVec, i, 10, 0.98, 0) << endl;
		//		<< RelativeStrengthIndex::getRSI(&m_askbidVec, i, 200, 0.98, 0) << endl;
		//		<< UlcerIndex::getUlicerIndex(&m_askbidVec, i, 200) << endl;
		//		<< UlcerIndex::getUlicerIndex(&m_askbidVec, i, 400) << endl;
		//		<< UlcerIndex::getUlicerIndex(&m_askbidVec, i, 1000) << endl;
		//		<< Volatility::getVolatility(&m_askbidVec, i, 700) << endl;
		//		<< Volatility::getVolatility(&m_askbidVec, i, 2000) << endl;
		//		<< BollingerDerived::getBollingerDerived(&m_askbidVec, i, 250) << endl;
		//		<< CommodityChannelIndex::getCCI(&m_askbidVec, i, 100) << endl;
		//		<< Change::getChange(&m_askbidVec, i, 20) << endl;
		//		<< Change::getChange(&m_askbidVec, i, 2000) << endl;
		//		<< EfficiencyRatio::getEffRatio(&m_askbidVec, i, 250) << endl;
		//		<< EfficiencyRatio::getEffRatio(&m_askbidVec, i, 4000) << endl;
		//		<< MovingPreferedDirection::getPrefDirection(&m_askbidVec, i, 500) << endl;
		//		<< MovingPreferedDirection::getPrefDirection(&m_askbidVec, i, 3000) << endl;
		//		<< MovingSumRatio::getMovingSumRatio(&m_askVolVec, &m_bidVolVec, i, 1000) << endl;
		//		<< VolumeByPrice::getVolumeByPrice(&m_askbidVec, &m_askVolbidVolVec, i, 250) << endl;
		//		<< VolumeByPrice::getVolumeByPrice(&m_askbidVec, &m_askVolbidVolVec, i, 1000) << endl;
	}
}
