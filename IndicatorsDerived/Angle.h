/*
 * Angle.h
 *
 *  Created on: Aug 25, 2015
 *      Author: jlochman
 */

#ifndef INDICATORSDERIVED_ANGLE_H_
#define INDICATORSDERIVED_ANGLE_H_

#include "../DataController/IndicatorDerivedDataController.h"

class Angle: public IndicatorDerivedDataController {
public:
	Angle(string branchName, const vector<double>* vec1, const vector<double>* vec2);
	virtual ~Angle();

protected:
	const vector<double>* m_inVec2;

	double calcValue(int pos);
	bool canCalc(int pos);
};

#endif /* INDICATORSDERIVED_ANGLE_H_ */
