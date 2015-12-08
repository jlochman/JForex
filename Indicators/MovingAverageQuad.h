/*
 * MovingAverageQuad.h
 *
 *  Created on: Jul 17, 2015
 *      Author: jlochman
 */

#ifndef INDICATORS_MOVINGAVERAGEQUAD_H_
#define INDICATORS_MOVINGAVERAGEQUAD_H_

#include "../DataController/IndicatorDataController.h"

class MovingAverageQuad: public IndicatorDataController {
public:
	MovingAverageQuad(string branchName, int calculateSize, const vector<double>* in_vec);
	virtual ~MovingAverageQuad();

	static double getMeanQuad(const vector<double>* in_vec, int fromPos, int length, double weight = 0);

private:
	const vector<double>* input_vec;
	int m_weight;

	static double calcTotalWeight(int length);

protected:
	double calcValue(int pos);
	bool canCalc(int pos);
};

#endif /* INDICATORS_MOVINGAVERAGEQUAD_H_ */
