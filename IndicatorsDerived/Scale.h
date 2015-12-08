/*
 * Scale.h
 *
 *  Created on: Jul 17, 2015
 *      Author: jlochman
 */

#ifndef INDICATORSDERIVED_SCALE_H_
#define INDICATORSDERIVED_SCALE_H_

#include "../DataController/IndicatorDerivedDataController.h"

class Scale: public IndicatorDerivedDataController {
public:
	Scale(string branchName, double scaleBy, const vector<double>* vec1);
	virtual ~Scale();

protected:
	double calcValue(int pos);
	bool canCalc(int pos);
	double m_scaleBy;
};

#endif /* INDICATORSDERIVED_SCALE_H_ */
