/*
 * StrategyCloseFileConroller.h
 *
 *  Created on: Jul 13, 2015
 *      Author: jlochman
 */

#ifndef FILECONTROLLER_STRATEGYCLOSEFILECONTROLLER_H_
#define FILECONTROLLER_STRATEGYCLOSEFILECONTROLLER_H_

#include "GenericFileController.h"
#include "InputFileController.h"
#include "IndicatorFileController.h"
#include "MLPFileController.h"

class StrategyCloseFileController: public GenericFileController {
public:
	StrategyCloseFileController(string fileName, string treeName, bool build,
			InputFileController* inputFileController,
			IndicatorFileController* indicatorFileController,
			MLPFileController* mlpFileController);
	virtual ~StrategyCloseFileController();

private:
	void init();
	void calculate();
	void coutCorrelation(string scName);

	InputFileController* 		m_InputFileController;
	IndicatorFileController* 	m_IndicatorFileController;
	MLPFileController* 			m_MLPFileController;
};

#endif /* FILECONTROLLER_STRATEGYCLOSEFILECONTROLLER_H_ */
