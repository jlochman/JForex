/*
 * MLPDataController.h
 *
 *  Created on: Jun 24, 2015
 *      Author: jlochman
 */

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "TMultiLayerPerceptron.h"

#include "GenericDataController.h"

#ifndef DATACONTROLLER_MLPDATACONTROLLER_H_
#define DATACONTROLLER_MLPDATACONTROLLER_H_

using namespace std;

class MLPDataController: public GenericDataController {
public:
	MLPDataController(string branchName, TTree* in_Tree, string topology, string weight_file, int train_cycles = 50);
	virtual ~MLPDataController();
	void calculate(int maxCount);

	void save_Weights();
	void load_Weights();
	void train_NN();
	void export_NN();

	vector<string> getInputs();
	string getOutputBranchName();
private:
	TTree* m_inTree;
	TMultiLayerPerceptron* m_MLP;

	string m_topology;
	string m_weightFile;

	int NUMBER_OF_TRAIN_CYCLES;

	void ReplaceString(string &subject, const string &search, const string &replace);
	bool ContainsString(const string &subject, const string &search);
};

#endif /* DATACONTROLLER_MLPDATACONTROLLER_H_ */
