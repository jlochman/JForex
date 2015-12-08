/*
 * WinningFixedStop.h
 *
 *  Created on: Sep 24, 2015
 *      Author: jlochman
 */

#ifndef INDICATORS_WINNINGFIXEDSTOP_H_
#define INDICATORS_WINNINGFIXEDSTOP_H_

#include "../DataController/IndicatorDataController.h"

class WinningFixedStop: public IndicatorDataController {
public:
	WinningFixedStop(string branchName, int calculateSize, const vector<double>* in_vec);
	virtual ~WinningFixedStop();

	static double getWinningFixedStop(const vector<double>* in_vec, int fromPos, int length);

	private:
		const vector<double>* input_vec;

	protected:
		double calcValue(int pos);
		bool canCalc(int pos);
};

#endif /* INDICATORS_WINNINGFIXEDSTOP_H_ */
