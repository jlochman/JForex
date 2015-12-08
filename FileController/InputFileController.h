/*
 * InputFileController.h
 *
 *  Created on: Jun 22, 2015
 *      Author: jlochman
 */

#ifndef FILECONTROLLER_INPUTFILECONTROLLER_H_
#define FILECONTROLLER_INPUTFILECONTROLLER_H_

#include "GenericFileController.h"

class InputFileController: public GenericFileController {
public:
	InputFileController(string fileName, string treeName, bool build, string forexFileName);
	virtual ~InputFileController();

private:
	void init();
	void calculate();

	string m_JForexFileName;
	int m_inputValuesCount;
};

#endif /* FILECONTROLLER_INPUTFILECONTROLLER_H_ */
