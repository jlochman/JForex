/*
 * CorrelationCoefficient.h
 *
 *  Created on: Sep 2, 2015
 *      Author: jlochman
 */

#ifndef HELPERS_CORRELATIONCOEFFICIENT_H_
#define HELPERS_CORRELATIONCOEFFICIENT_H_

#include <vector>

using namespace std;

class CorrelationCoefficient {
public:
	static double getCoefficient(const vector<double>* vec1, const vector<double>* vec2);
};

#endif /* HELPERS_CORRELATIONCOEFFICIENT_H_ */
