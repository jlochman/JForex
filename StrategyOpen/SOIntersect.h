/*
 * SOIntersect.h
 *
 *  Created on: Jul 16, 2015
 *      Author: jlochman
 */

#ifndef STRATEGYOPEN_SOINTERSECT_H_
#define STRATEGYOPEN_SOINTERSECT_H_

#include "../DataController/StrategyOpenDataController.h"

class SOIntersect: public StrategyOpenDataController {
public:
	SOIntersect(string branchName, const vector<double>* vec1, const vector<double>* vec2);
	virtual ~SOIntersect();

private:
	bool canCalc(int pos);
	bool checkOpen(int pos);

	const vector<double>* m_vec1;
	const vector<double>* m_vec2;
};

#endif /* STRATEGYOPEN_SOINTERSECT_H_ */
