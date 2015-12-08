/*
 * StrategyOpenFileController.cpp
 *
 *  Created on: Jul 16, 2015
 *      Author: jlochman
 */

#include <iostream>

#include "StrategyOpenFileController.h"
#include "../StrategyOpen/SOIntersect.h"
#include "../StrategyOpen/SOGreaterThan.h"
#include "../StrategyOpen/SOSmallerThan.h"

StrategyOpenFileController::StrategyOpenFileController(string fileName, string treeName, bool build,
		InputFileController* inputFileController,
		IndicatorFileController* indicatorFileController,
		MLPFileController* mlpFileController)
	: GenericFileController(fileName, treeName, build) {

	m_InputFileController = inputFileController;
	m_IndicatorFileController = indicatorFileController;
	m_MLPFileController = mlpFileController;

	cout << "=== Strategy Open File Controller ===" << endl;

	this->init();
	if ( build ) {
		this->calculate();
		this->save();
	} else {
		this->load();
	}

}

StrategyOpenFileController::~StrategyOpenFileController() {
}

void StrategyOpenFileController::init() {

	/*
	data_vec.push_back( new SOIntersect("MLP2_Ask_50_Intersect",
			m_MLPFileController->getVecByName("MLP2AddAsk"),
			m_IndicatorFileController->getVecByName("movAvg_Ask_50") ) );
	data_vec.push_back( new SOIntersect("Ask_50_MLP2_Intersect",
			m_IndicatorFileController->getVecByName("movAvg_Ask_50"),
			m_MLPFileController->getVecByName("MLP2AddAsk") ) );

	data_vec.push_back( new SOIntersect("MLP2_AskLin_50_Intersect",
			m_MLPFileController->getVecByName("MLP2AddAsk"),
			m_IndicatorFileController->getVecByName("movAvgLin_Ask_50") ) );
	data_vec.push_back( new SOIntersect("AskLin_50_MLP2_Intersect",
			m_IndicatorFileController->getVecByName("movAvgLin_Ask_50"),
			m_MLPFileController->getVecByName("MLP2AddAsk") ) );
	*/

	/*
	data_vec.push_back( new SOIntersect("MLP1_MLP2_Intersect",
			m_MLPFileController->getVecByName("MLP1AddAsk"),
			m_IndicatorFileController->getVecByName("MLP2AddAsk") ) );
	data_vec.push_back( new SOIntersect("MLP2_MLP1_Intersect",
			m_IndicatorFileController->getVecByName("MLP2AddAsk"),
			m_MLPFileController->getVecByName("MLP1AddAsk") ) );
	*/
	//data_vec.push_back( new SOGreaterThan("Angle_MLP1_movAvgQuad_Ask_20_Grater_10", 1, m_MLPFileController->getVecByName("Angle_MLP1_movAvgQuad_Ask_20") ) );
	//data_vec.push_back( new SOSmallerThan("Angle_MLP1_movAvgQuad_Ask_20_Smaller__10", -1, m_MLPFileController->getVecByName("Angle_MLP1_movAvgQuad_Ask_20") ) );

	//data_vec.push_back( new SOGreaterThan("Angle_MLP2_movAvgLin_Ask_50_Grater_10", 1, m_MLPFileController->getVecByName("Angle_MLP2_movAvgLin_Ask_50") ) );
	//data_vec.push_back( new SOSmallerThan("Angle_MLP2_movAvgLin_Ask_50_Smaller__10", -1, m_MLPFileController->getVecByName("Angle_MLP2_movAvgLin_Ask_50") ) );

	//data_vec.push_back( new SOGreaterThan("Angle_MLP2_movAvgLin_Ask_50_Greater_0", 0, m_MLPFileController->getVecByName("Angle_MLP2_movAvgLin_Ask_50") ) );
	//data_vec.push_back( new SOSmallerThan("Angle_MLP2_movAvgLin_Ask_50_Smaller_0", 0, m_MLPFileController->getVecByName("Angle_MLP2_movAvgLin_Ask_50") ) );

	//data_vec.push_back( new SOGreaterThan("MLP1_Greater_5e_4", 5e-4, m_MLPFileController->getVecByName("MLP1") ) );
	//data_vec.push_back( new SOSmallerThan("MLP1_Smaller__5e_4", -5e-4, m_MLPFileController->getVecByName("MLP1") ) );

	data_vec.push_back( new SOGreaterThan("MLP1_Greater_0",  0,      m_MLPFileController->getVecByName("MLP1") ) );
	data_vec.push_back( new SOSmallerThan("MLP1_Smaller_0",   0,      m_MLPFileController->getVecByName("MLP1") ) );

	data_vec.push_back( new SOGreaterThan("MLP1Test_Greater_0",  0,      m_MLPFileController->getVecByName("MLP1Test") ) );
	data_vec.push_back( new SOSmallerThan("MLP1Test_Smaller_0",   0,      m_MLPFileController->getVecByName("MLP1Test") ) );


	data_vec.push_back( new SOGreaterThan("MLP2_Greater_0",   0,       m_MLPFileController->getVecByName("MLP2") ) );
	data_vec.push_back( new SOSmallerThan("MLP2_Smaller_0",    0,       m_MLPFileController->getVecByName("MLP2") ) );

	data_vec.push_back( new SOGreaterThan("MLP2Test_Greater_0",   0,       m_MLPFileController->getVecByName("MLP2Test") ) );
	data_vec.push_back( new SOSmallerThan("MLP2Test_Smaller_0",    0,       m_MLPFileController->getVecByName("MLP2Test") ) );



	//data_vec.push_back( new SOGreaterThan("MLP2_Greater_1", 1e-6, m_MLPFileController->getVecByName("MLP2") ) );
	//data_vec.push_back( new SOSmallerThan("MLP2_Smaller__1", -1e-6, m_MLPFileController->getVecByName("MLP2") ) );

	//data_vec.push_back( new SOGreaterThan("RSI095_Ask_50_GREATER_0", 0, m_IndicatorFileController->getVecByName("RSI095_Ask_50") ) );
	//data_vec.push_back( new SOSmallerThan("RSI095_Ask_50_SMALLER_0", 0, m_IndicatorFileController->getVecByName("RSI095_Ask_50") ) );

	//data_vec.push_back( new SOGreaterThan("APO095_Ask_30_GREATER", 0, m_IndicatorFileController->getVecByName("APO095_Ask_30") ) );
	//data_vec.push_back( new SOSmallerThan("APO095_Ask_30_SMALLER", 0, m_IndicatorFileController->getVecByName("APO095_Ask_30") ) );
}

void StrategyOpenFileController::calculate() {
	for ( unsigned int i = 0; i < data_vec.size(); i++ ) {
		cout << data_vec.at(i)->getName() << endl;
		data_vec.at(i)->calculate(MAX_VEC_LENGTH);
	}
}
