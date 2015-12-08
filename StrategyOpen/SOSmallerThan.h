/*
 * SOSmallerThan.h
 *
 *  Created on: Aug 5, 2015
 *      Author: jlochman
 */

#ifndef STRATEGYOPEN_SOSMALLERTHAN_H_
#define STRATEGYOPEN_SOSMALLERTHAN_H_

#include "../DataController/StrategyOpenDataController.h"

class SOSmallerThan: public StrategyOpenDataController {
public:
	SOSmallerThan(string branchName, double x, const vector<double>* vec1);
	virtual ~SOSmallerThan();

private:
	bool canCalc(int pos);
	bool checkOpen(int pos);

	const vector<double>* m_vec;
	double m_value;
};

#endif /* STRATEGYOPEN_SOSMALLERTHAN_H_ */
