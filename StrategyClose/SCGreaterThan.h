/*
 * SCGreaterThan.h
 *
 *  Created on: Jul 13, 2015
 *      Author: jlochman
 */

#ifndef STRATEGYCLOSE_SCGREATERTHAN_H_
#define STRATEGYCLOSE_SCGREATERTHAN_H_

#include "../DataController/StrategyCloseDataController.h"

class SCGreaterThan: public StrategyCloseDataController {
public:
	SCGreaterThan(string branchName, InputFileController* inputFileController,
			string buySell, const vector< double >* vec1, double cutOff);
	virtual ~SCGreaterThan();

private:
	const vector< double >* m_vec1;
	double m_cutoff;

	bool canCalc(int pos);
	bool checkClose(int pos);
};

#endif /* STRATEGYCLOSE_SCGREATERTHAN_H_ */
