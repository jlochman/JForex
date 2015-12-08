/*
 * FibonacciPivotPoints.cpp
 *
 *  Created on: Sep 5, 2015
 *      Author: jlochman
 */

#include "MovingMax.h"
#include "MovingMin.h"

#include "FibonacciPivotPoints.h"

FibonacciPivotPoints::FibonacciPivotPoints(string branchName, int calculateSize,
		Fib fib, const vector<double>* in_vec)
	: IndicatorDataController(branchName, calculateSize) {

	input_vec = in_vec;
	m_fib = fib;
}

FibonacciPivotPoints::FibonacciPivotPoints(string branchName, int calculateSize,
		const vector<double>* in_vec)
	: IndicatorDataController(branchName, calculateSize) {

	input_vec = in_vec;
	m_fib = R3;
}

FibonacciPivotPoints::~FibonacciPivotPoints() {
}

double FibonacciPivotPoints::getFibPivotPoint(const vector<double>* in_vec,
		int fromPos, int length, Fib fib) {
	if ( fromPos + length > in_vec->size() ) return 0;
	if ( length <= 0 ) return 0;

	double max = MovingMax::getMax( in_vec, fromPos, length );
	double min = MovingMin::getMin( in_vec, fromPos, length );
	double range = max - min;
	return range * fib / 1000;
}

double FibonacciPivotPoints::calcValue(int pos) {
	return getFibPivotPoint( input_vec, pos, calcSize, m_fib );
}

bool FibonacciPivotPoints::canCalc(int pos) {
	return ( pos < input_vec->size() - getHistNeeded() );
}
