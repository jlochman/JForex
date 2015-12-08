/*
 * SAndAnd.h
 *
 *  Created on: Aug 7, 2015
 *      Author: jlochman
 */

#ifndef STRATEGYSELECTOR_STRATEGY_SANDAND_H_
#define STRATEGYSELECTOR_STRATEGY_SANDAND_H_

#include "../GenericStrategy.h"

class SAndAnd: public GenericStrategy {
public:
	SAndAnd(int size, GenericDataController* stratOpen1,
			GenericDataController* stratOpen2,
			GenericDataController* stratOpen3,
			GenericDataController* stratClose);
	virtual ~SAndAnd();

	string getName();
	bool checkTradeOpen(int pos);

private:
	GenericDataController* m_stratOpen2;
	GenericDataController* m_stratOpen3;
};

#endif /* STRATEGYSELECTOR_STRATEGY_SANDAND_H_ */
