/*
 * GenericDataController.h
 *
 *  Created on: Jun 22, 2015
 *      Author: jlochman
 */

#include <vector>

#include "TTree.h"

using namespace std;

#ifndef DATACONTROLLER_GENERICDATACONTROLLER_H_
#define DATACONTROLLER_GENERICDATACONTROLLER_H_

class GenericDataController {
public:
	GenericDataController(string branchName);
	virtual ~GenericDataController();

	void addValue(double x);
	void pushForwardValue(double x);
	void reverseOrder();

	void setValue(int pos, double x);
	double getValue(int pos);
	string getName();
	const string& getClassName() const;

	void write(TTree* t, int length, bool first = true);
	void read(TTree* t);
	void empty();

	const vector<double>& getVec() const;
	void setVec(const vector<double>& vec);
	int getHistNeeded() const;
	int getVecSize();

	virtual void calculate(int maxCount) = 0;

protected:
	vector<double>  m_vec;
	string 			m_branchName;
	string 			m_className;

	int				m_calcIncrement;
	int 			histNeeded;
};

#endif /* DATACONTROLLER_GENERICDATACONTROLLER_H_ */
