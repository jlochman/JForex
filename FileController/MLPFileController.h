/*
 * MLPFileController.h
 *
 *  Created on: Jun 24, 2015
 *      Author: jlochman
 */

#ifndef FILECONTROLLER_MLPFILECONTROLLER_H_
#define FILECONTROLLER_MLPFILECONTROLLER_H_

#include "GenericFileController.h"
#include "IndicatorFileController.h"

class MLPFileController: public GenericFileController {
public:
	MLPFileController(string fileName, string treeName, bool build, bool train_NN,
			string save_path,
			IndicatorFileController* indicatorFileController);
	virtual ~MLPFileController();

private:
	void init();
	void calculate();

	void train_NN();
	void load_NN();
	void save_NN();

	string m_savePath;
	IndicatorFileController* 	m_IndicatorFileController;
};

#endif /* FILECONTROLLER_MLPFILECONTROLLER_H_ */
