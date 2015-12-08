/*
 * StrategyOpenFileController.h
 *
 *  Created on: Jul 16, 2015
 *      Author: jlochman
 */

#ifndef FILECONTROLLER_STRATEGYOPENFILECONTROLLER_H_
#define FILECONTROLLER_STRATEGYOPENFILECONTROLLER_H_

#include "GenericFileController.h"
#include "InputFileController.h"
#include "IndicatorFileController.h"
#include "MLPFileController.h"

class StrategyOpenFileController: public GenericFileController {
public:
	StrategyOpenFileController(string fileName, string treeName, bool build,
			InputFileController* inputFileController,
			IndicatorFileController* indicatorFileController,
			MLPFileController* mlpFileController);
	virtual ~StrategyOpenFileController();

private:
	void init();
	void calculate();

	InputFileController* 		m_InputFileController;
	IndicatorFileController* 	m_IndicatorFileController;
	MLPFileController* 			m_MLPFileController;
};

#endif /* FILECONTROLLER_STRATEGYOPENFILECONTROLLER_H_ */
