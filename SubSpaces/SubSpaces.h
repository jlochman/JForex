/*
 * SubSpaces.h
 *
 *  Created on: Dec 2, 2015
 *      Author: jlochman
 */

#include <vector>

#include "../FileController/InputFileController.h"
#include "../FileController/IndicatorFileController.h"
#include "../FileController/MLPFileController.h"

#ifndef SUBSPACES_SUBSPACES_H_
#define SUBSPACES_SUBSPACES_H_

class SubSpaces : public IndicatorFileController {


public:
	SubSpaces(string fileName, string treeName, bool caculate, IndicatorFileController* indFC, MLPFileController* mlpFC);
	virtual ~SubSpaces();

	void getDistances();
	void applyFilter();
	void test();

private:
	void init();

	std::vector<double> getBorders(const std::vector<double>* vec, int borderCount);
	double getDistance(const std::vector<double>* vec, std::string indName, double min, double max);
	void getNNInputsOutputs();

	double DISTANCE_CUTOFF;

	IndicatorFileController* m_indFC;
	MLPFileController* m_mlpFC;

	std::vector<std::string> nnInputs_vec;
	std::vector<std::string> nnOutput_vec;

};

#endif /* SUBSPACES_SUBSPACES_H_ */
