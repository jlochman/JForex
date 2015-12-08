/*
 * InputFileController.cpp
 *
 *  Created on: Jun 22, 2015
 *      Author: jlochman
 */

#include <iostream>
#include <fstream>
#include <sstream>

#include "InputFileController.h"
#include "../DataController/InputDataController.h"

#include "../IndicatorsDerived/SubtractIndicators.h"
#include "../IndicatorsDerived/AddIndicators.h"
#include "../IndicatorsDerived/Average.h"
#include "../IndicatorsDerived/Translate.h"

InputFileController :: InputFileController(string fileName, string treeName, bool build, string forexFileName)
		: GenericFileController(fileName, treeName, build) {
	m_JForexFileName = forexFileName;
	m_inputValuesCount = 5;

	cout << "=== Input File Controller ===" << endl;

	this->init();
	if ( build ) {
		this->calculate();
		this->save();
	} else {
		this->load();
	}

}

InputFileController::~InputFileController() {
}

void InputFileController::init() {
	data_vec.push_back( new InputDataController("time") );
	data_vec.push_back( new InputDataController("ask") );
	data_vec.push_back( new InputDataController("askVol") );
	data_vec.push_back( new InputDataController("bid") );
	data_vec.push_back( new InputDataController("bidVol") );

	data_vec.push_back( new SubtractIndicators( "Ask__Bid", this->getVecByName("ask"), this->getVecByName("bid") ) );
	data_vec.push_back( new SubtractIndicators( "AskVol__BidVol", this->getVecByName("askVol"), this->getVecByName("bidVol") ) );
	data_vec.push_back( new AddIndicators( "AskVolBidVol", this->getVecByName("askVol"), this->getVecByName("bidVol") ) );
	data_vec.push_back( new Average("AskBid", this->getVecByName("ask"), this->getVecByName("bid") ) );

	data_vec.push_back( new Translate("AskBid__1000", -1000, this->getVecByName("AskBid") ) );
	data_vec.push_back( new Translate("AskBid__2000", -2000, this->getVecByName("AskBid") ) );
}

void InputFileController::calculate() {
	// in this case means loadFromJForexFile
	string line;
	double x;
	int count = 0;
	ifstream input_file( m_JForexFileName );
	if (input_file.is_open()) {
		// one title line will be ignored
		getline(input_file, line);
		// and now the cycle over remaining lines
		while ( getline(input_file, line) ) {
			count++;
			if ( count % 50000 == 0 ) cout << count << endl;
			if ( count > MAX_VEC_LENGTH ) break;
			stringstream ss(line);
			for ( unsigned int i = 0; i < m_inputValuesCount; i++ ) {
				ss >> x;
				data_vec.at(i)->addValue(x);
			}
		}
	}

	for ( unsigned int i = 0; i < m_inputValuesCount; i++ ) {
		data_vec.at(i)->reverseOrder();
	}

	for ( unsigned int i = m_inputValuesCount; i < data_vec.size(); i++ ) {
		cout << data_vec.at(i)->getName() << endl;
		data_vec.at(i)->calculate( MAX_VEC_LENGTH );
	}

}
