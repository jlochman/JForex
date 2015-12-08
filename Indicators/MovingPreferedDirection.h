/*
 * MovingPreferedDirection.h
 *
 *  Created on: Sep 3, 2015
 *      Author: jlochman
 */

#ifndef INDICATORS_MOVINGPREFEREDDIRECTION_H_
#define INDICATORS_MOVINGPREFEREDDIRECTION_H_

#include "../DataController/IndicatorDataController.h"

class MovingPreferedDirection: public IndicatorDataController {
public:
	MovingPreferedDirection(string branchName, int calculateSize, const vector<double>* in_vec1);
	virtual ~MovingPreferedDirection();

	static double getPrefDirection(const vector<double>* in_vec1, int fromPos, int length);

private:
	const vector<double>* m_vec1;

protected:
	double calcValue(int pos);
	bool canCalc(int pos);
};

#endif /* INDICATORS_MOVINGPREFEREDDIRECTION_H_ */
