/*
 * MLPFileController.cpp
 *
 *  Created on: Jun 24, 2015
 *      Author: jlochman
 */

#include <iostream>

#include "MLPFileController.h"
#include "../DataController/MLPDataController.h"

#include "../Helpers/CorrelationCoefficient.h"
#include "../IndicatorsDerived/AddIndicators.h"
#include "../IndicatorsDerived/Scale.h"
#include "../IndicatorsDerived/Angle.h"
#include "../IndicatorsDerived/Translate.h"

MLPFileController::MLPFileController(string fileName, string treeName, bool build, bool train_NN,
		string save_path, IndicatorFileController* indicatorFileController)
	: GenericFileController(fileName, treeName, build) {

	m_IndicatorFileController 	= indicatorFileController;
	m_savePath 					= save_path;

	if ( train_NN ) cout << "[TRAIN] ";
	cout << "=== MLP File Controller ===" << endl;

	this->init();
	if ( train_NN ) {
		this->train_NN();
		this->save_NN();
	} else {
		this->load_NN();
	}

	if ( build ) {
		this->calculate();
		this->save();
	} else {
		this->load();
	}
}

MLPFileController::~MLPFileController() {
}

void MLPFileController::init() {

	std::string in_mlp;
	int cycles = 200;

	cout << "MLP init" << endl;
	/*
	in_mlp = "change_20,effRatio_3000,volByPrice_250,aroon_3000,bollingerDer_250,"
			"cci_100,RSI098_100,Vol_1000,MovAVGAsk__Bid_400,MassIndex098_10,MFI_50,MFI_2000,"
			"UlcerIndex_1000,APO098_20:14:";
	data_vec.push_back( new MLPDataController("MLPmax2000_200", m_IndicatorFileController->getTree(),
					in_mlp + "MLPmax2000Out", m_savePath+this->getTree()->GetName()+"max2000_200", cycles) );

	in_mlp = "pdAskBid_3000,change_20,change_2000,effRatio_3000,volByPrice_250,"
			"volByPrice_2000,bollingerDer_250,cci_100,RSI098_100,Vol_1000,MovAVGAsk__Bid_400,MassIndex098_10,"
			"MFI_2000,UlcerIndex_1000,APO098_20:15:";
	data_vec.push_back( new MLPDataController("MLPmin2000_200", m_IndicatorFileController->getTree(),
					in_mlp + "MLPmin2000Out", m_savePath+this->getTree()->GetName()+"min2000_200", cycles) );

	in_mlp = "pdAskBid_3000,change_20,change_2000,effRatio_3000,volByPrice_250,bollingerDer_250,"
			"cci_100,RSI098_100,MassIndex098_10,MFI_50,UlcerIndex_50,APO098_20:12:";
	data_vec.push_back( new MLPDataController("MLPmaxmin1000_200", m_IndicatorFileController->getTree(),
					in_mlp + "MLPmaxmin1000Out", m_savePath+this->getTree()->GetName()+"maxmin1000_200", cycles) );
	*/

	in_mlp = "srAskVolBidVol_1000,change_20,effRatio_3000,volByPrice_250,aroon_3000,bollingerDer_250,"
			"cci_100,RSI098_100,Vol_1000,MovAVGAsk__Bid_400,MassIndex098_10,MFI_50,MFI_2000,"
			"UlcerIndex_1000,APO098_20:15:";
	data_vec.push_back( new MLPDataController("MLPmax2000_200", m_IndicatorFileController->getTree(),
					in_mlp + "MLPmax2000Out", m_savePath+this->getTree()->GetName()+"max2000_200", cycles) );

	in_mlp = "srAskVolBidVol_2000,pdAskBid_3000,change_20,change_2000,effRatio_3000,volByPrice_250,"
			"volByPrice_2000,bollingerDer_250,cci_100,RSI098_100,Vol_1000,MovAVGAsk__Bid_400,MassIndex098_10,"
			"MFI_2000,UlcerIndex_1000,APO098_20:16:";
	data_vec.push_back( new MLPDataController("MLPmin2000_200", m_IndicatorFileController->getTree(),
					in_mlp + "MLPmin2000Out", m_savePath+this->getTree()->GetName()+"min2000_200", cycles) );

	in_mlp = "srAskVolBidVol_20,pdAskBid_3000,change_20,change_2000,effRatio_3000,volByPrice_250,bollingerDer_250,"
			"cci_100,RSI098_100,Vol_100,MACD098_50,MassIndex098_10,MFI_50,UlcerIndex_50,APO098_20:15:";
	data_vec.push_back( new MLPDataController("MLPmaxmin1000_200", m_IndicatorFileController->getTree(),
					in_mlp + "MLPmaxmin1000Out", m_savePath+this->getTree()->GetName()+"maxmin1000_200", cycles) );
}


void MLPFileController::calculate() {
	cout << "calculation NN output" << endl;

	for ( unsigned int i = 0; i < data_vec.size(); i++ ) {
		cout << "... calculating [" << i+1 << "/" << data_vec.size() << "] " << data_vec.at(i)->getName() << endl;
		data_vec.at(i)->calculate(MAX_VEC_LENGTH);

		cout << "calculation Corr" << endl;
		if ( data_vec.at(i)->getClassName() == "MLP" ) {
			MLPDataController* test = (MLPDataController*) data_vec.at(i);
			string mlpBranch = test->getName();
			string output    = test->getOutputBranchName();
			cout << "==============" << endl;
			cout << "  Correlation Coefficient [" << mlpBranch << " : " << output << "] : " <<
					CorrelationCoefficient::getCoefficient(
					this->getVecByName( mlpBranch ),
					m_IndicatorFileController->getVecByName( output ) )
			<< endl;
			cout << "==============" << endl;
		}
	}
}

void MLPFileController::train_NN() {
	cout << "training NN" << endl;

	for ( unsigned int i = 0; i < data_vec.size(); i++ ) {
		cout << data_vec.at(i)->getName() << endl;
		if ( data_vec.at(i)->getClassName() == "MLP" ) {
			MLPDataController* test = (MLPDataController*) data_vec.at(i);
			test->train_NN();
		}
	}
}

void MLPFileController::load_NN() {
	cout << "loading NN" << endl;

	for ( unsigned int i = 0; i < data_vec.size(); i++ ) {
		if ( data_vec.at(i)->getClassName() == "MLP" ) {
			MLPDataController* test = (MLPDataController*) data_vec.at(i);
			test->load_Weights();
		}
	}
}

void MLPFileController::save_NN() {
	cout << "saving NN" << endl;

	for ( unsigned int i = 0; i < data_vec.size(); i++ ) {
		if ( data_vec.at(i)->getClassName() == "MLP" ) {
			MLPDataController* test = (MLPDataController*) data_vec.at(i);
			test->save_Weights();
			test->export_NN();
		}
	}
}
