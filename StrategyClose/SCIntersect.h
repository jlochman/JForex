/*
 * SCIntersect.h
 *
 *  Created on: Aug 9, 2015
 *      Author: jlochman
 */

#ifndef STRATEGYCLOSE_SCINTERSECT_H_
#define STRATEGYCLOSE_SCINTERSECT_H_

#include "../DataController/StrategyCloseDataController.h"

class SCIntersect: public StrategyCloseDataController {
public:
	SCIntersect(string branchName, InputFileController* inputFileController,
			string buySell, const vector< double >* vec1, const vector< double >* vec2);
	virtual ~SCIntersect();

private:
	const vector< double >* m_vec1;
	const vector< double >* m_vec2;

	bool canCalc(int pos);
	bool checkClose(int pos);
};

#endif /* STRATEGYCLOSE_SCINTERSECT_H_ */
