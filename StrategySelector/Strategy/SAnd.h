/*
 * SAnd.h
 *
 *  Created on: Aug 7, 2015
 *      Author: jlochman
 */

#ifndef STRATEGYSELECTOR_STRATEGY_SAND_H_
#define STRATEGYSELECTOR_STRATEGY_SAND_H_

#include "../GenericStrategy.h"

class SAnd: public GenericStrategy {
public:
	SAnd(int size, GenericDataController* stratOpen1,
		GenericDataController* stratOpen2,
		GenericDataController* stratClose);
	virtual ~SAnd();

	string getName();
	bool checkTradeOpen(int pos);

private:
	GenericDataController* m_stratOpen2;
};

#endif /* STRATEGYSELECTOR_STRATEGY_SAND_H_ */
