/*
 * StrategyCloseDataController.h
 *
 *  Created on: Jul 13, 2015
 *      Author: jlochman
 */

#ifndef DATACONTROLLER_STRATEGYCLOSEDATACONTROLLER_H_
#define DATACONTROLLER_STRATEGYCLOSEDATACONTROLLER_H_

#include "GenericDataController.h"
#include "../FileController/InputFileController.h"

class StrategyCloseDataController: public GenericDataController {
public:

	StrategyCloseDataController(string branchName, InputFileController* inputFileController,
			string buySell);
	virtual ~StrategyCloseDataController();

	void calculate(int maxCount);

	virtual bool canCalc(int pos) = 0;
	virtual bool checkClose(int pos) = 0;

protected:
	InputFileController* 		m_InputFileController;
	string	m_BuySell;
};

#endif /* DATACONTROLLER_STRATEGYCLOSEDATACONTROLLER_H_ */
