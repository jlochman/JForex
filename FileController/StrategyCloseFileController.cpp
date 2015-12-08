/*
 * StrategyCloseFileConroller.cpp
 *
 *  Created on: Jul 13, 2015
 *      Author: jlochman
 */

#include "StrategyCloseFileController.h"

#include <iostream>

#include "../DataController/StrategyCloseDataController.h"
#include "../StrategyClose/SCFixedStop.h"
#include "../StrategyClose/SCGreaterThan.h"
#include "../StrategyClose/SCSmallerThan.h"
#include "../StrategyClose/SCMovingStop.h"
#include "../StrategyClose/SCMovingExpandingStop.h"
#include "../StrategyClose/SCIntersect.h"
#include "../Helpers/CorrelationCoefficient.h"

StrategyCloseFileController::StrategyCloseFileController(string fileName, string treeName, bool build,
		InputFileController* inputFileController,
		IndicatorFileController* indicatorFileController,
		MLPFileController* mlpFileController)
	: GenericFileController(fileName, treeName, build) {

	m_InputFileController = inputFileController;
	m_IndicatorFileController = indicatorFileController;
	m_MLPFileController = mlpFileController;

	cout << "=== Strategy Close File Controller ===" << endl;

	this->init();
	if ( build ) {
		this->calculate();
		this->save();
	} else {
		this->load();
	}
}

StrategyCloseFileController::~StrategyCloseFileController() {
}

void StrategyCloseFileController::init() {
	data_vec.push_back( new SCFixedStop("fixedStopBUY_5",  m_InputFileController, "BUY", 5e-4) );
	data_vec.push_back( new SCFixedStop("fixedStopBUY_10", m_InputFileController, "BUY", 10e-4) );
	data_vec.push_back( new SCFixedStop("fixedStopBUY_15", m_InputFileController, "BUY", 15e-4) );
	data_vec.push_back( new SCFixedStop("fixedStopBUY_20", m_InputFileController, "BUY", 20e-4) );

	data_vec.push_back( new SCMovingStop("movingStopBUY_5",   m_InputFileController, "BUY", 5e-4) );
	data_vec.push_back( new SCMovingStop("movingStopBUY_10",  m_InputFileController, "BUY", 10e-4) );
	data_vec.push_back( new SCMovingStop("movingStopSELL_5",  m_InputFileController, "SELL", 5e-4) );
	data_vec.push_back( new SCMovingStop("movingStopSELL_10", m_InputFileController, "SELL", 10e-4) );
}

void StrategyCloseFileController::calculate() {
	for ( unsigned int i = 0; i < data_vec.size(); i++ ) {
		cout << data_vec.at(i)->getName() << endl;
		data_vec.at(i)->calculate(MAX_VEC_LENGTH);
	}

	for ( unsigned int i = 0; i < data_vec.size(); i++ ) {
		coutCorrelation( data_vec.at(i)->getName() );
	}
}

void StrategyCloseFileController::coutCorrelation(string scName) {
	cout << "============" << endl;
	double corrCoef = 0;
	for ( unsigned int i = 0; i < m_IndicatorFileController->getGenDCCount(); i++ ) {
		corrCoef = CorrelationCoefficient::getCoefficient( m_IndicatorFileController->getVecByIndex(i), this->getVecByName( scName ) );
		if ( abs(corrCoef) > 0.02 )
			cout << "  Correlation Coefficient [" << scName << " : " <<
			m_IndicatorFileController->getGenDCByIndex(i)->getName() << "] : "<< corrCoef << endl;
	}
}
