/*
 * MovingAverageLinInv.h
 *
 *  Created on: Sep 16, 2015
 *      Author: jlochman
 */

#ifndef INDICATORS_MOVINGAVERAGELININV_H_
#define INDICATORS_MOVINGAVERAGELININV_H_

#include "../DataController/IndicatorDataController.h"

class MovingAverageLinInv: public IndicatorDataController {
public:
	MovingAverageLinInv(string branchName, int calculateSize, const vector<double>* in_vec);
	virtual ~MovingAverageLinInv();

	static double getMeanLinInv(const vector<double>* in_vec, int fromPos, int length, double weight = 0);

	private:
		const vector<double>* input_vec;
		int m_weight;

	protected:
		double calcValue(int pos);
		bool canCalc(int pos);
};

#endif /* INDICATORS_MOVINGAVERAGELININV_H_ */
