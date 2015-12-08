/*
 * Translation.h
 *
 *  Created on: Jul 13, 2015
 *      Author: jlochman
 */

#ifndef INDICATORSDERIVED_TRANSLATE_H_
#define INDICATORSDERIVED_TRANSLATE_H_

#include "../DataController/IndicatorDerivedDataController.h"

class Translate: public IndicatorDerivedDataController {
public:
	Translate(string branchName, int translateBy, const vector<double>* vec1);
	virtual ~Translate();

protected:
	double calcValue(int pos);
	bool canCalc(int pos);

	int m_translateBy;
};

#endif /* INDICATORSDERIVED_TRANSLATION_H_ */
