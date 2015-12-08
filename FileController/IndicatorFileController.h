/*
 * IndicatorFileController.h
 *
 *  Created on: Jun 22, 2015
 *      Author: jlochman
 */

#ifndef FILECONTROLLER_INDICATORFILECONTROLLER_H_
#define FILECONTROLLER_INDICATORFILECONTROLLER_H_

#include "GenericFileController.h"
#include "InputFileController.h"

class IndicatorFileController: public GenericFileController {
public:
	IndicatorFileController(string fileName, string treeName, bool build, InputFileController* inputFileController);
	virtual ~IndicatorFileController();

private:
	void init();
	void calculate();
	void coutCorrelation(string MLPname);

	void test();

	InputFileController* m_InputFC;
};

#endif /* FILECONTROLLER_INDICATORFILECONTROLLER_H_ */
