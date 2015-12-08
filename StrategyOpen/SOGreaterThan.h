/*
 * SOGreaterThan.h
 *
 *  Created on: Aug 5, 2015
 *      Author: jlochman
 */

#ifndef STRATEGYOPEN_SOGREATERTHAN_H_
#define STRATEGYOPEN_SOGREATERTHAN_H_

#include "../DataController/StrategyOpenDataController.h"

class SOGreaterThan: public StrategyOpenDataController {
public:
	SOGreaterThan(string branchName, double x, const vector<double>* vec1);
	virtual ~SOGreaterThan();

private:
	bool canCalc(int pos);
	bool checkOpen(int pos);

	const vector<double>* m_vec;
	double m_value;
};

#endif /* STRATEGYOPEN_SOGREATERTHAN_H_ */
