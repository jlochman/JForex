/*
 * VolumeByPriceDerived.h
 *
 *  Created on: Sep 16, 2015
 *      Author: jlochman
 */

#ifndef INDICATORS_VOLUMEBYPRICEDERIVED_H_
#define INDICATORS_VOLUMEBYPRICEDERIVED_H_

#include "../DataController/IndicatorDataController.h"

class VolumeByPriceDerived: public IndicatorDataController {
public:
	VolumeByPriceDerived(string branchName, int calculateSize, const vector<double>* priceVec,
			const vector<double>* volumeVec);
	virtual ~VolumeByPriceDerived();

	static double getVolumeByPriceDerived(const vector<double>* priceVec, const vector<double>* volumeVec, int fromPos, int length);

	private:
		const vector<double>* m_priceVec;
		const vector<double>* m_volumeVec;

	protected:
		double calcValue(int pos);
		bool canCalc(int pos);
};

#endif /* INDICATORS_VOLUMEBYPRICEDERIVED_H_ */
