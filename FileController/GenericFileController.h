/*
 * GenericFileController.h
 *
 *  Created on: Jun 22, 2015
 *      Author: jlochman
 */

#include <vector>

#include "TFile.h"
#include "TTree.h"

#include "../DataController/GenericDataController.h"

using namespace std;

#ifndef FILECONTROLLER_GENERICFILECONTROLLER_H_
#define FILECONTROLLER_GENERICFILECONTROLLER_H_

class GenericFileController {
public:
	GenericFileController(string fileName, string treeName, bool build);
	virtual ~GenericFileController();

	void load();
	void save(TTree* toTree = 0 );
	void clear();
	int getMinVecSize();

	virtual void init() = 0;
	virtual void calculate() = 0;

	const vector<double>* getVecByName(string vecName);
	const vector<double>* getVecByIndex(int index);
	GenericDataController* getGenDCByName(string genDCName);
	GenericDataController* getGenDCByIndex(int index);

	const int getGenDCCount();
	const double getValue(string genDCName, int pos);

	TTree* getTree();

protected:
	TFile *m_File;
	TTree *m_Tree;
	vector< GenericDataController* > data_vec;

	int MAX_VEC_LENGTH;
};

#endif /* FILECONTROLLER_GENERICFILECONTROLLER_H_ */
