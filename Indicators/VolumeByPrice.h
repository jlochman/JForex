/*
 * VolumeByPrice.h
 *
 *  Created on: Sep 5, 2015
 *      Author: jlochman
 */

#ifndef INDICATORS_VOLUMEBYPRICE_H_
#define INDICATORS_VOLUMEBYPRICE_H_

#include "../DataController/IndicatorDataController.h"

class VolumeByPrice: public IndicatorDataController {
public:
	VolumeByPrice(string branchName, int calculateSize, const vector<double>* priceVec,
			const vector<double>* volumeVec);
	virtual ~VolumeByPrice();

	static double getVolumeByPrice(const vector<double>* priceVec, const vector<double>* volumeVec, int fromPos, int length);

	private:
		const vector<double>* m_priceVec;
		const vector<double>* m_volumeVec;

	protected:
		double calcValue(int pos);
		bool canCalc(int pos);
};

#endif /* INDICATORS_VOLUMEBYPRICE_H_ */
