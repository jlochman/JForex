/*
 * InputDataController.h
 *
 *  Created on: Jun 22, 2015
 *      Author: jlochman
 */

#ifndef DATACONTROLLER_INPUTDATACONTROLLER_H_
#define DATACONTROLLER_INPUTDATACONTROLLER_H_

#include "GenericDataController.h"

class InputDataController: public GenericDataController {
public:
	InputDataController(string branchName);
	virtual ~InputDataController();
	void calculate(int maxCount) {};
};

#endif /* DATACONTROLLER_INPUTDATACONTROLLER_H_ */
