/*
 * Tester.h
 *
 *  Created on: Oct 1, 2015
 *      Author: jlochman
 */

#include <vector>

using namespace std;

#ifndef TESTER_TESTER_H_
#define TESTER_TESTER_H_


class Tester {

public:
	Tester();
	virtual ~Tester();

	void loadData();
	void printData();
	void testData();

private:
	string m_File;

	vector<double> m_askbidVec;
	vector<double> m_askVolVec;
	vector<double> m_bidVolVec;
	vector<double> m_askVolbidVolVec;

	void reverseOrder(vector<double> &m_vec) { reverse( m_vec.begin(), m_vec.end() ); }

};

#endif /* TESTER_TESTER_H_ */
