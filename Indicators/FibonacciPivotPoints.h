/*
 * FibonacciPivotPoints.h
 *
 *  Created on: Sep 5, 2015
 *      Author: jlochman
 */

#ifndef INDICATORS_FIBONACCIPIVOTPOINTS_H_
#define INDICATORS_FIBONACCIPIVOTPOINTS_H_

#include "../DataController/IndicatorDataController.h"

class FibonacciPivotPoints: public IndicatorDataController {
public:
	enum Fib {S1 = -382, S2 = -618, S3 = -1000,
		  	  R1 =  382, R2 =  618, R3 =  1000};

	FibonacciPivotPoints(string branchName, int calculateSize, Fib fib, const vector<double>* in_vec);
	FibonacciPivotPoints(string branchName, int calculateSize, const vector<double>* in_vec);
	virtual ~FibonacciPivotPoints();

	static double getFibPivotPoint(const vector<double>* in_vec, int fromPos, int length, Fib fib);

private:
	const vector<double>* input_vec;
	Fib m_fib;

protected:
	double calcValue(int pos);
	bool canCalc(int pos);
};

#endif /* INDICATORS_FIBONACCIPIVOTPOINTS_H_ */
