/*
 * SCSmallerThan.h
 *
 *  Created on: Jul 14, 2015
 *      Author: jlochman
 */

#ifndef STRATEGYCLOSE_SCSMALLERTHAN_H_
#define STRATEGYCLOSE_SCSMALLERTHAN_H_

#include "../DataController/StrategyCloseDataController.h"

class SCSmallerThan: public StrategyCloseDataController {
public:
	SCSmallerThan(string branchName, InputFileController* inputFileController,
			string buySell, const vector< double >* vec1, double cutOff);
	virtual ~SCSmallerThan();

private:
	const vector< double >* m_vec1;
	double m_cutoff;

	bool canCalc(int pos);
	bool checkClose(int pos);
};

#endif /* STRATEGYCLOSE_SCSMALLERTHAN_H_ */
