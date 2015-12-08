/*
 * SSimple.h
 *
 *  Created on: Aug 6, 2015
 *      Author: jlochman
 */

#ifndef STRATEGYSELECTOR_STRATEGY_SSIMPLE_H_
#define STRATEGYSELECTOR_STRATEGY_SSIMPLE_H_

#include "../GenericStrategy.h"

class SSimple: public GenericStrategy {
public:
	SSimple(int size, GenericDataController* stratOpen1,
			GenericDataController* stratClose);
	virtual ~SSimple();

	string getName();
	bool checkTradeOpen(int pos);
};

#endif /* STRATEGYSELECTOR_STRATEGY_SSIMPLE_H_ */
