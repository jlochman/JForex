/*
 * BollingerDerived.h
 *
 *  Created on: Sep 5, 2015
 *      Author: jlochman
 */

#ifndef INDICATORS_BOLLINGERDERIVED_H_
#define INDICATORS_BOLLINGERDERIVED_H_

#include "../DataController/IndicatorDataController.h"

class BollingerDerived: public IndicatorDataController {
public:
	BollingerDerived(string branchName, int calculateSize, const vector<double>* in_vec);
	virtual ~BollingerDerived();

	static double getBollingerDerived(const vector<double>* in_vec, int fromPos, int length);

	private:
		const vector<double>* input_vec;

	protected:
		double calcValue(int pos);
		bool canCalc(int pos);
};

#endif /* INDICATORS_BOLLINGERDERIVED_H_ */
