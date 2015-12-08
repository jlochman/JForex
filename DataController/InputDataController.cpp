/*
 * InputDataController.cpp
 *
 *  Created on: Jun 22, 2015
 *      Author: jlochman
 */

#include "InputDataController.h"

InputDataController :: InputDataController(string branchName) :
	GenericDataController(branchName) {
	m_className = "InputDataController";
}

InputDataController::~InputDataController() {
}

