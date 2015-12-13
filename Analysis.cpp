//============================================================================
// Name        : Analysis.cpp
// Author      : Jan Lochman
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

//C++
#include <iostream>
#include <ctime>
#include <vector>
#include <unistd.h>

//ROOT
#include "TH1F.h"
#include "TCanvas.h"
#include "TApplication.h"
#include "TFile.h"
#include "TBrowser.h"

//Marklar
#include "FileController/InputFileController.h"
#include "FileController/IndicatorFileController.h"
#include "FileController/MLPFileController.h"
#include "FileController/StrategyCloseFileController.h"
#include "FileController/StrategyOpenFileController.h"
#include "SubSpaces/SubSpaces.h"

//Test
#include "Indicators/MovingAverage.h"
#include "Indicators/MovingAverageLin.h"
#include "Indicators/MovingAverageQuad.h"
#include "Indicators/MovingAverageExp.h"
#include "Indicators/RelativeStrengthIndex.h"
#include "Indicators/AbsolutePriceOscilator.h"
#include "Indicators/Sigma.h"
#include "Indicators/MovingMax.h"
#include "Indicators/MovingMin.h"
#include "Indicators/MovingPreferedDirection.h"
#include "Indicators/MovingSumRatio.h"
#include "Indicators/FibonacciPivotPoints.h"
#include "Indicators/Volatility.h"
#include "Indicators/Change.h"
#include "Indicators/EfficiencyRatio.h"
#include "Indicators/VolumeByPrice.h"
#include "Indicators/Aroon.h"
#include "Indicators/BollingerDerived.h"
#include "Indicators/CommodityChannelIndex.h"
#include "Indicators/MACD.h"
#include "Indicators/MassIndex.h"
#include "Indicators/MoneyFlowIndex.h"
#include "Indicators/UlcerIndex.h"

#include "Tester/Tester.h"


#include "StrategySelector/StrategySelector.h"

using namespace std;

const string fixedPath = "/Users/jlochman/Desktop/JForex/Analysis/";
const string jForexFile = "/Users/jlochman/Desktop/JForex/Analysis/mFile6.txt";

void test() {
	vector<double> my_vec;
	my_vec.resize(0);
	for ( int i = 0; i < 200; i++ ) {
		my_vec.push_back(i*i);
	}
	my_vec.at(20) = 5;

	int fromPos = 0;
	int length = 80;
	cout << MovingPreferedDirection::getPrefDirection(&my_vec, fromPos, length) << endl;
	cout << MoneyFlowIndex::getMFI(&my_vec, &my_vec, fromPos, length) << endl;
	cout << MovingSumRatio::getMovingSumRatio(&my_vec, &my_vec, fromPos, length) << endl;
	cout << Change::getChange(&my_vec, fromPos, length) << endl;
	cout << EfficiencyRatio::getEffRatio(&my_vec, fromPos, length) << endl;
	cout << VolumeByPrice::getVolumeByPrice(&my_vec, &my_vec, fromPos, length) << endl;
	cout << Aroon::getAroon(&my_vec, fromPos, length) << endl;
	cout << BollingerDerived::getBollingerDerived(&my_vec, fromPos, length) << endl;
	cout << CommodityChannelIndex::getCCI(&my_vec, fromPos, length) << endl;
	cout << RelativeStrengthIndex::getRSI(&my_vec, fromPos, length, 0.98) << endl;
	cout << UlcerIndex::getUlicerIndex(&my_vec, fromPos, length) << endl;
	cout << "MACD: " << MACD::getMACD(&my_vec, fromPos, length, 0.98) << endl;
	cout << AbsolutePriceOscilator::getAPO(&my_vec, fromPos, length, 0.98, 0) << endl;
	cout << Volatility::getVolatility(&my_vec, fromPos, length) << endl;
	cout << MassIndex::getMassIndex(&my_vec, fromPos, length, 0.98, 0) << endl;
}

void advancedTest() {
	Tester myTester;
	myTester.loadData();
	//myTester.printData();
	myTester.testData();
}

int main(int argc, char** argv) {
	clock_t begin = clock();

	bool trainNN = false;
	bool calculate = false;
	InputFileController JForexData(fixedPath+"JForex.root", "JForex", calculate, jForexFile);
	IndicatorFileController Indicators(fixedPath+"Indicators.root", "Indicators", calculate, &JForexData);
	MLPFileController MLP(fixedPath+"MLP.root", "MLP", calculate, trainNN, fixedPath, &Indicators);

	SubSpaces subSpace(fixedPath+"SubSpace.root", "SubSpace", &Indicators, &MLP);
	calculate = true;
	trainNN = true;
	MLPFileController MLPFilter(fixedPath+"MLPFilter.root", "MLPFilter", calculate, trainNN, fixedPath, &subSpace);

	if ( false ) {
		//StrategyCloseFileController StratClose(fixedPath+"StratClose.root", "StratClose", calculate, &JForexData, &Indicators, &MLP);
		//StrategyOpenFileController StratOpen(fixedPath+"StratOpen.root", "StratOpen", calculate, &JForexData, &Indicators, &MLP);
		//StrategySelector StratSelector( &StratOpen, &StratClose );
	}

	if ( true ) {
		cout << "MERGING" << endl;
		TFile *newFile = new TFile( (fixedPath+"all.root").c_str() ,"recreate");
		TTree *newTree = new TTree("all", "all");
		newFile->cd();
		cout << "Indicators" << endl;
		Indicators.save(newTree);
		cout << "MLP" << endl;
		MLP.save(newTree);

		TFile *newFileFilter = new TFile( (fixedPath+"allFilter.root").c_str() ,"recreate");
		TTree *newTreeFilter = new TTree("allFilter", "allFilter");
		newFileFilter->cd();
		cout << "subSpaces" << endl;
		subSpace.save(newTreeFilter);
		cout << "MLPFilter" << endl;
		MLPFilter.save(newTreeFilter);
	}

	clock_t end = clock();
	cout << "TIME: " << double(end - begin) / CLOCKS_PER_SEC << " seconds" << endl;

	cout << "!!! DONE !!!" << endl;
	return 0;
}




