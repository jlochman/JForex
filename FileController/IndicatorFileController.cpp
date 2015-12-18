/*
 * IndicatorFileController.cpp
 *
 *  Created on: Jun 22, 2015
 *      Author: jlochman
 */

#include <iostream>

#include "IndicatorFileController.h"

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
#include "../Indicators/TypicalPrice.h"

#include "../Helpers/CorrelationCoefficient.h"

#include "../IndicatorsDerived/SubtractIndicators.h"
#include "../IndicatorsDerived/Translate.h"
#include "../IndicatorsDerived/Scale.h"
#include "../IndicatorsDerived/AddIndicators.h"
#include "../IndicatorsDerived/Normalize.h"
#include "../IndicatorsDerived/SubtractAndNormalize.h"

IndicatorFileController::IndicatorFileController(string fileName, string treeName, bool build, InputFileController* inputFileController)
	: GenericFileController(fileName, treeName, build) {
	if ( inputFileController ) {
		m_InputFC = inputFileController;

		cout << "=== Indicator File Controller ===" << endl;

		this->init();
		//this->test();
		if ( build ) {
			this->calculate();
			this->save();
		} else {
			this->load();
		}
	}
}

IndicatorFileController::~IndicatorFileController() {
}

void IndicatorFileController::init() {

	data_vec.push_back( new MovingAverageLin("avgLin_50", 50, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new MovingAverageLin("avgLin_100", 100, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new MovingAverageLin("avgLin_200", 200, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new MovingAverageLin("avgLin_500", 500, m_InputFC->getVecByName("AskBid") ) );

	data_vec.push_back( new MovingMax("movMax_2000__2000", 2000, m_InputFC->getVecByName("AskBid__2000") ) );
	data_vec.push_back( new MovingMin("movMin_2000__2000", 2000, m_InputFC->getVecByName("AskBid__2000") ) );
	data_vec.push_back( new SubtractIndicators("MLPmax2000Out", this->getVecByName("movMax_2000__2000"), this->getVecByName("avgLin_50") ) );
	data_vec.push_back( new SubtractIndicators("MLPmin2000Out", this->getVecByName("movMin_2000__2000"), this->getVecByName("avgLin_50") ) );

	data_vec.push_back( new MovingMax("movMax_1000__1000", 1000, m_InputFC->getVecByName("AskBid__1000") ) );
	data_vec.push_back( new MovingMin("movMin_1000__1000", 1000, m_InputFC->getVecByName("AskBid__1000") ) );
	data_vec.push_back( new AddIndicators("mavMinMax_1000__1000", this->getVecByName("movMax_1000__1000"), this->getVecByName("movMin_1000__1000") ) );
	data_vec.push_back( new Scale("2avgLin_50", 2, this->getVecByName("avgLin_50") ) );
	data_vec.push_back( new SubtractIndicators("MLPmaxmin1000Out", this->getVecByName("mavMinMax_1000__1000"), this->getVecByName("2avgLin_50") ) );

	//data_vec.push_back( new TypicalPrice("typPrice_2000__2000",   2000,  m_InputFC->getVecByName("AskBid__2000") ) );
	//data_vec.push_back( new SubtractIndicators("MLPtypPrice2000Out", this->getVecByName("typPrice_2000__2000"), this->getVecByName("avgLin_50") ) );

	data_vec.push_back( new MovingSumRatio("srAskVolBidVol_10",   10,  m_InputFC->getVecByName("askVol"), m_InputFC->getVecByName("bidVol") ) );
	data_vec.push_back( new MovingSumRatio("srAskVolBidVol_20",   20,  m_InputFC->getVecByName("askVol"), m_InputFC->getVecByName("bidVol") ) );
	data_vec.push_back( new MovingSumRatio("srAskVolBidVol_50",   50,  m_InputFC->getVecByName("askVol"), m_InputFC->getVecByName("bidVol") ) );
	data_vec.push_back( new MovingSumRatio("srAskVolBidVol_100", 100,  m_InputFC->getVecByName("askVol"), m_InputFC->getVecByName("bidVol") ) );
	data_vec.push_back( new MovingSumRatio("srAskVolBidVol_200", 200,  m_InputFC->getVecByName("askVol"), m_InputFC->getVecByName("bidVol") ) );
	data_vec.push_back( new MovingSumRatio("srAskVolBidVol_400", 400,  m_InputFC->getVecByName("askVol"), m_InputFC->getVecByName("bidVol") ) );
	data_vec.push_back( new MovingSumRatio("srAskVolBidVol_700", 700,  m_InputFC->getVecByName("askVol"), m_InputFC->getVecByName("bidVol") ) );
	data_vec.push_back( new MovingSumRatio("srAskVolBidVol_1000", 1000,  m_InputFC->getVecByName("askVol"), m_InputFC->getVecByName("bidVol") ) );
	data_vec.push_back( new MovingSumRatio("srAskVolBidVol_1500", 1500,  m_InputFC->getVecByName("askVol"), m_InputFC->getVecByName("bidVol") ) );
	data_vec.push_back( new MovingSumRatio("srAskVolBidVol_2000", 2000,  m_InputFC->getVecByName("askVol"), m_InputFC->getVecByName("bidVol") ) );

	data_vec.push_back( new MovingPreferedDirection( "pdAskBid_250", 250, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new MovingPreferedDirection( "pdAskBid_500", 500, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new MovingPreferedDirection( "pdAskBid_1000", 1000, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new MovingPreferedDirection( "pdAskBid_1500", 1500, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new MovingPreferedDirection( "pdAskBid_2000", 2000, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new MovingPreferedDirection( "pdAskBid_3000", 3000, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new MovingPreferedDirection( "pdAskBid_4000", 4000, m_InputFC->getVecByName("AskBid") ) );

	data_vec.push_back( new Change( "change_2",    2, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new Change( "change_5",    5, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new Change( "change_10",   10, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new Change( "change_20",   20, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new Change( "change_50",   50, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new Change( "change_100",  100, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new Change( "change_250",  250, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new Change( "change_500",  500, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new Change( "change_750",  750, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new Change( "change_1000", 1000, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new Change( "change_1500", 1500, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new Change( "change_2000", 2000, m_InputFC->getVecByName("AskBid") ) );

	data_vec.push_back( new EfficiencyRatio( "effRatio_250",  250, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new EfficiencyRatio( "effRatio_500",  500, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new EfficiencyRatio( "effRatio_750",  750, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new EfficiencyRatio( "effRatio_1000",  1000, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new EfficiencyRatio( "effRatio_1500",  1500, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new EfficiencyRatio( "effRatio_2000",  2000, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new EfficiencyRatio( "effRatio_3000",  3000, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new EfficiencyRatio( "effRatio_4000",  4000, m_InputFC->getVecByName("AskBid") ) );

	data_vec.push_back( new VolumeByPrice( "volByPrice_250",  250, m_InputFC->getVecByName("AskBid"), m_InputFC->getVecByName("AskVolBidVol") ) );
	data_vec.push_back( new VolumeByPrice( "volByPrice_500",  500, m_InputFC->getVecByName("AskBid"), m_InputFC->getVecByName("AskVolBidVol") ) );
	data_vec.push_back( new VolumeByPrice( "volByPrice_750",  750, m_InputFC->getVecByName("AskBid"), m_InputFC->getVecByName("AskVolBidVol") ) );
	data_vec.push_back( new VolumeByPrice( "volByPrice_1000",  1000, m_InputFC->getVecByName("AskBid"), m_InputFC->getVecByName("AskVolBidVol") ) );
	data_vec.push_back( new VolumeByPrice( "volByPrice_1500",  1500, m_InputFC->getVecByName("AskBid"), m_InputFC->getVecByName("AskVolBidVol") ) );
	data_vec.push_back( new VolumeByPrice( "volByPrice_2000",  2000, m_InputFC->getVecByName("AskBid"), m_InputFC->getVecByName("AskVolBidVol") ) );

	data_vec.push_back( new Aroon( "aroon_250", 250, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new Aroon( "aroon_500", 500, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new Aroon( "aroon_750", 750, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new Aroon( "aroon_1000", 1000, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new Aroon( "aroon_1500", 1500, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new Aroon( "aroon_2000", 2000, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new Aroon( "aroon_3000", 3000, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new Aroon( "aroon_4000", 4000, m_InputFC->getVecByName("AskBid") ) );

	data_vec.push_back( new BollingerDerived( "bollingerDer_250", 250, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new BollingerDerived( "bollingerDer_500", 500, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new BollingerDerived( "bollingerDer_750", 750, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new BollingerDerived( "bollingerDer_1000", 1000, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new BollingerDerived( "bollingerDer_1500", 1500, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new BollingerDerived( "bollingerDer_2000", 2000, m_InputFC->getVecByName("AskBid") ) );

	data_vec.push_back( new CommodityChannelIndex( "cci_100", 100, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new CommodityChannelIndex( "cci_200", 200, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new CommodityChannelIndex( "cci_400", 400, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new CommodityChannelIndex( "cci_700", 700, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new CommodityChannelIndex( "cci_1000", 1000, m_InputFC->getVecByName("AskBid") ) );

	data_vec.push_back( new RelativeStrengthIndex("RSI098_100", 100, 0.98, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new RelativeStrengthIndex("RSI098_200", 200, 0.98, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new RelativeStrengthIndex("RSI098_400", 400, 0.98, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new RelativeStrengthIndex("RSI098_700", 700, 0.98, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new RelativeStrengthIndex("RSI098_1000", 1000, 0.98, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new RelativeStrengthIndex("RSI098_1500", 1500, 0.98, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new RelativeStrengthIndex("RSI098_2000", 2000, 0.98, m_InputFC->getVecByName("AskBid") ) );

	data_vec.push_back( new Volatility("Vol_100", 100, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new Volatility("Vol_200", 200, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new Volatility("Vol_400", 400, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new Volatility("Vol_700", 700, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new Volatility("Vol_1000", 1000, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new Volatility("Vol_1500", 1500, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new Volatility("Vol_2000", 2000, m_InputFC->getVecByName("AskBid") ) );

	data_vec.push_back( new MovingAverage("MovAVGAsk__Bid_20",   20, m_InputFC->getVecByName("Ask__Bid") ) );
	data_vec.push_back( new MovingAverage("MovAVGAsk__Bid_50",   50, m_InputFC->getVecByName("Ask__Bid") ) );
	data_vec.push_back( new MovingAverage("MovAVGAsk__Bid_100", 100, m_InputFC->getVecByName("Ask__Bid") ) );
	data_vec.push_back( new MovingAverage("MovAVGAsk__Bid_200", 200, m_InputFC->getVecByName("Ask__Bid") ) );
	data_vec.push_back( new MovingAverage("MovAVGAsk__Bid_400", 400, m_InputFC->getVecByName("Ask__Bid") ) );

	data_vec.push_back( new MACD("MACD098_50",   50, 0.98, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new MACD("MACD098_100", 100, 0.98, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new MACD("MACD098_200", 200, 0.98, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new MACD("MACD098_300", 300, 0.98, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new MACD("MACD098_400", 400, 0.98, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new MACD("MACD098_500", 500, 0.98, m_InputFC->getVecByName("AskBid") ) );

	data_vec.push_back( new MassIndex("MassIndex098_10",    10, 0.98, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new MassIndex("MassIndex098_20",    20, 0.98, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new MassIndex("MassIndex098_50",    50, 0.98, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new MassIndex("MassIndex098_100",  100, 0.98, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new MassIndex("MassIndex098_200",  200, 0.98, m_InputFC->getVecByName("AskBid") ) );

	data_vec.push_back( new MoneyFlowIndex("MFI_50",    50, m_InputFC->getVecByName("AskBid"), m_InputFC->getVecByName("AskVolBidVol") ) );
	data_vec.push_back( new MoneyFlowIndex("MFI_100",  100, m_InputFC->getVecByName("AskBid"), m_InputFC->getVecByName("AskVolBidVol") ) );
	data_vec.push_back( new MoneyFlowIndex("MFI_200",  200, m_InputFC->getVecByName("AskBid"), m_InputFC->getVecByName("AskVolBidVol") ) );
	data_vec.push_back( new MoneyFlowIndex("MFI_400",  400, m_InputFC->getVecByName("AskBid"), m_InputFC->getVecByName("AskVolBidVol") ) );
	data_vec.push_back( new MoneyFlowIndex("MFI_700",  700, m_InputFC->getVecByName("AskBid"), m_InputFC->getVecByName("AskVolBidVol") ) );
	data_vec.push_back( new MoneyFlowIndex("MFI_1000",  1000, m_InputFC->getVecByName("AskBid"), m_InputFC->getVecByName("AskVolBidVol") ) );
	data_vec.push_back( new MoneyFlowIndex("MFI_1500",  1500, m_InputFC->getVecByName("AskBid"), m_InputFC->getVecByName("AskVolBidVol") ) );
	data_vec.push_back( new MoneyFlowIndex("MFI_2000",  2000, m_InputFC->getVecByName("AskBid"), m_InputFC->getVecByName("AskVolBidVol") ) );

	data_vec.push_back( new UlcerIndex("UlcerIndex_50",     50, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new UlcerIndex("UlcerIndex_100",   100, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new UlcerIndex("UlcerIndex_200",   200, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new UlcerIndex("UlcerIndex_400",   400, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new UlcerIndex("UlcerIndex_600",   600, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new UlcerIndex("UlcerIndex_800",   800, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new UlcerIndex("UlcerIndex_1000", 1000, m_InputFC->getVecByName("AskBid") ) );

	data_vec.push_back( new AbsolutePriceOscilator("APO098_20",   20, 0.98, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new AbsolutePriceOscilator("APO098_50",   50, 0.98, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new AbsolutePriceOscilator("APO098_100", 100, 0.98, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new AbsolutePriceOscilator("APO098_200", 200, 0.98, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new AbsolutePriceOscilator("APO098_400", 400, 0.98, m_InputFC->getVecByName("AskBid") ) );
}

void IndicatorFileController::test() {
	data_vec.push_back( new MovingAverageLin("avgLin_50", 50, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new MovingMax("movMax_2000__2000", 2000, m_InputFC->getVecByName("AskBid__2000") ) );
	data_vec.push_back( new MovingMin("movMin_2000__2000", 2000, m_InputFC->getVecByName("AskBid__2000") ) );
	data_vec.push_back( new SubtractIndicators("MLPmax2000Out", this->getVecByName("movMax_2000__2000"), this->getVecByName("avgLin_50") ) );
	data_vec.push_back( new SubtractIndicators("MLPmin2000Out", this->getVecByName("movMin_2000__2000"), this->getVecByName("avgLin_50") ) );

	data_vec.push_back( new MovingMax("movMax_1000__1000", 1000, m_InputFC->getVecByName("AskBid__1000") ) );
	data_vec.push_back( new MovingMin("movMin_1000__1000", 1000, m_InputFC->getVecByName("AskBid__1000") ) );
	data_vec.push_back( new AddIndicators("mavMinMax_1000__1000", this->getVecByName("movMax_1000__1000"), this->getVecByName("movMin_1000__1000") ) );
	data_vec.push_back( new Scale("2avgLin_50", 2, this->getVecByName("avgLin_50") ) );
	data_vec.push_back( new SubtractIndicators("MLPmaxmin1000Out", this->getVecByName("mavMinMax_1000__1000"), this->getVecByName("2avgLin_50") ) );

	data_vec.push_back( new AbsolutePriceOscilator("APO098_20",   20, 0.98, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new MACD("MACD098_400", 400, 0.98, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new MoneyFlowIndex("MFI_50",    50, m_InputFC->getVecByName("AskBid"), m_InputFC->getVecByName("AskVolBidVol") ) );
	data_vec.push_back( new MoneyFlowIndex("MFI_2000",  2000, m_InputFC->getVecByName("AskBid"), m_InputFC->getVecByName("AskVolBidVol") ) );
	data_vec.push_back( new MassIndex("MassIndex098_10",    10, 0.98, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new RelativeStrengthIndex("RSI098_200", 200, 0.98, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new UlcerIndex("UlcerIndex_200",   200, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new UlcerIndex("UlcerIndex_400",   400, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new UlcerIndex("UlcerIndex_1000", 1000, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new Volatility("Vol_700", 700, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new Volatility("Vol_2000", 2000, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new Aroon( "aroon_2000", 2000, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new Aroon( "aroon_4000", 4000, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new BollingerDerived( "bollingerDer_250", 250, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new CommodityChannelIndex( "cci_100", 100, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new Change( "change_20",   20, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new Change( "change_2000", 2000, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new EfficiencyRatio( "effRatio_250",  250, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new EfficiencyRatio( "effRatio_4000",  4000, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new MovingPreferedDirection( "pdAskBid_500", 500, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new MovingPreferedDirection( "pdAskBid_3000", 3000, m_InputFC->getVecByName("AskBid") ) );
	data_vec.push_back( new MovingSumRatio("srAskVolBidVol_1000", 1000,  m_InputFC->getVecByName("askVol"), m_InputFC->getVecByName("bidVol") ) );
	data_vec.push_back( new VolumeByPrice( "volByPrice_250",  250, m_InputFC->getVecByName("AskBid"), m_InputFC->getVecByName("AskVolBidVol") ) );
	data_vec.push_back( new VolumeByPrice( "volByPrice_1000",  1000, m_InputFC->getVecByName("AskBid"), m_InputFC->getVecByName("AskVolBidVol") ) );
}


void IndicatorFileController::coutCorrelation(string MLPname) {
	cout << "============" << endl;
	double corrCoef = 0;
	for ( unsigned int i = 0; i < data_vec.size(); i++ ) {
		corrCoef = CorrelationCoefficient::getCoefficient( this->getVecByIndex(i), this->getVecByName( MLPname ) );
		if ( abs(corrCoef) > 0.02 )
			cout << "  Correlation Coefficient [" << MLPname << " : " << this->getGenDCByIndex(i)->getName() << "] : "<< corrCoef << endl;
	}
}

void IndicatorFileController::calculate() {
	for ( unsigned int i = 0; i < data_vec.size(); i++ ) {
		cout << "... calculating [" << i+1 << "/" << data_vec.size() << "] " << data_vec.at(i)->getName() << endl;
		data_vec.at(i)->calculate(MAX_VEC_LENGTH);
	}
	string indName;
	for ( unsigned int i = 0; i < data_vec.size(); i++ ) {
		indName = data_vec.at(i)->getName();
		if ( indName.find("MLP") != string::npos ) coutCorrelation(indName);
	}
}
