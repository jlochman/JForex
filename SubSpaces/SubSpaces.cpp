/*
 * SubSpaces.cpp
 *
 *  Created on: Dec 2, 2015
 *      Author: jlochman
 */

#include <iostream>
#include <algorithm>

#include "TMath.h"

#include "../Helpers/CorrelationCoefficient.h"

#include "../DataController/IndicatorDataController.h"
#include "../DataController/MLPDataController.h"
#include "../DataController/InputDataController.h"

#include "SubSpaces.h"

SubSpaces::SubSpaces(string fileName, string treeName, bool caculate, IndicatorFileController* indFC, MLPFileController* mlpFC)
 : IndicatorFileController(fileName, treeName, caculate, NULL) {

	std::cout << "[SUB SPACES]" << std::endl;
	nnInputs_vec.resize(0);
	m_indFC = indFC;
	m_mlpFC = mlpFC;

	DISTANCE_CUTOFF = 0;

	this->init();
	if ( caculate ) {
		this->getDistances();
		this->applyFilter();
		this->save();
	} else {
		this->load();
	}

}

void SubSpaces::init() {
	this->getNNInputsOutputs();

	for ( int i = 0; i < nnInputs_vec.size(); i++ ) {
		data_vec.push_back( new InputDataController(nnInputs_vec.at(i)) );
	}
	for ( int i = 0; i < nnOutput_vec.size(); i++ ) {
		data_vec.push_back( new InputDataController(nnOutput_vec.at(i)) );
	}
}

SubSpaces::~SubSpaces() {
}

void SubSpaces::getDistances() {
	std::vector<double> border_vec;
	double distance = 0;
	double min = 0;
	double max = 0;
	std::stringstream buffer;
	for ( int i = 0; i < nnInputs_vec.size(); i++ ) {
		border_vec = getBorders( m_indFC->getVecByName( nnInputs_vec.at(i) ), 10 );
		for ( int k = 0; k < border_vec.size() - 1; k++ ) {
			std::cout << nnInputs_vec.at(i) << " [" << border_vec.at(k) << "," << border_vec.at(k+1) << "]" << std::endl;
			min = border_vec.at(k);
			max = border_vec.at(k+1);
			distance = getDistance( m_indFC->getVecByName( nnInputs_vec.at(i) ), nnInputs_vec.at(i), min, max );
			if ( distance > DISTANCE_CUTOFF ) {
				if ( k == 0 ) {
					buffer << "m_indFC->getValue( \"" << nnInputs_vec.at(i) << "\", i ) < " << max << " || "<< std::endl;
				} else if ( k == border_vec.size() - 2 ) {
					buffer << min << " < m_indFC->getValue( \"" << nnInputs_vec.at(i) << "\", i ) || " << std::endl;
				} else {
					buffer << "(" << min << " < m_indFC->getValue( \"" << nnInputs_vec.at(i) << "\", i ) && ";
					buffer << "m_indFC->getValue( \"" << nnInputs_vec.at(i) << "\", i ) < " << max << ") || " << std::endl;
				}
			}
		}
	}
	std::cout << buffer.str() << std::endl;
}

void SubSpaces::applyFilter() {
	std::vector<double> value_vec;
	std::vector<std::string> name_vec;
	for ( int i = 0; i < nnInputs_vec.size(); i++ ) {
		name_vec.push_back(nnInputs_vec.at(i));
	}
	for ( int i = 0; i < nnOutput_vec.size(); i++ ) {
		name_vec.push_back(nnOutput_vec.at(i));
	}
	value_vec.resize( name_vec.size() );

	/*
	for ( int i = 0; i < name_vec.size(); i++ ) {
		data_vec.push_back( new InputDataController(name_vec.at(i)) );
	}
	*/

	std::cout << "=== applying data cut ===" << std::endl;
	std::cout << "before cut: " << m_indFC->getMinVecSize() << std::endl;
	for ( int i = 0; i < m_indFC->getMinVecSize(); i++ ) {
		for ( int k = 0; k < name_vec.size(); k++ ) {
			value_vec.at(k) = m_indFC->getValue( name_vec.at(k), i );
		}
		if ( m_indFC->getValue( "UlcerIndex_50", i ) < 0.0104734 ||
				m_indFC->getValue( "srAskVolBidVol_1000", i ) > 0.186783 ) {
			// do nothing
		} else {
			for ( int k = 0; k < name_vec.size(); k++ ) {
				// maybe here is the problem - data_vec changes pointer after each value is added
				data_vec.at(k)->addValue( value_vec.at(k) );
			}
		}
	}
	std::cout << "after cut: " << this->getMinVecSize() << std::endl;
}

void SubSpaces::getNNInputsOutputs() {
	std::vector<std::string> vec;
	for ( int i = 0; i < m_mlpFC->getGenDCCount(); i++ ) {
		if ( m_mlpFC->getGenDCByIndex(i)->getClassName() == "MLP" ) {
			MLPDataController* mlpDC = (MLPDataController*) m_mlpFC->getGenDCByIndex(i);
			vec = mlpDC->getInputs();
			for ( int j = 0; j < vec.size(); j++ ) {
				nnInputs_vec.push_back( vec.at(j) );
			}
			nnOutput_vec.push_back( mlpDC->getOutputBranchName() );
		}
	}
	std::sort( std::begin(nnInputs_vec), std::end(nnInputs_vec) );
	nnInputs_vec.erase( std::unique( std::begin(nnInputs_vec), std::end(nnInputs_vec) ), std::end(nnInputs_vec));
}

double SubSpaces::getDistance(const std::vector<double>* vec, std::string indName, double min, double max) {
	double count = 0;
	double distance = 0;
	int range = 0;
	int mlpRange = 0;
	std::string mlpOutput;
	std::vector<std::string> mlpInput;
	std::vector<double> ind_vec;
	ind_vec.resize(0);
	std::vector<double> mlp_vec;
	mlp_vec.resize(0);
	for ( int i = 0; i < m_mlpFC->getGenDCCount(); i++ ) {
		if (m_mlpFC->getGenDCByIndex(i)->getClassName() == "MLP" ) {
			MLPDataController* mlpDC = (MLPDataController*) m_mlpFC->getGenDCByIndex(i);
			mlpOutput = mlpDC->getOutputBranchName();
			mlpInput = mlpDC->getInputs();
			if( std::find(mlpInput.begin(), mlpInput.end(), indName) != mlpInput.end() ) {
				IndicatorDataController* indDC = (IndicatorDataController*) m_indFC->getGenDCByName(mlpOutput);
				range = vec->size();
				mlpRange = m_mlpFC->getMinVecSize();
				if ( mlpRange > 0 ) range = std::min( range, mlpRange );
				for ( int k = 0; k < range; k++ ) {
					if ( vec->at(k) > min && vec->at(k) < max ) {
						ind_vec.push_back(indDC->getValue(k));
						mlp_vec.push_back(mlpDC->getValue(k));
						count++;
					}
				}
			}
		}
	}
	distance = CorrelationCoefficient::getCoefficient( &ind_vec, &mlp_vec );
	std::cout << "  distance: " << distance << " (" << count << ")" << endl;
	return distance;
}

void SubSpaces::test() {

}

std::vector<double> SubSpaces::getBorders(const std::vector<double>* vec,
		int borderCount) {
	std::vector<double> m_vec = *vec;
	std::sort( std::begin(m_vec), std::end(m_vec) );
	std::vector<double> result;
	int increment = m_vec.size() / borderCount;
	int pos = 0;
	for ( int i = 0; i <= borderCount; i++ ) {
		pos = i*increment;
		if ( pos >= m_vec.size() ) pos = m_vec.size() - 1;
		result.push_back( m_vec.at( pos ) );
	}
	return result;
}


