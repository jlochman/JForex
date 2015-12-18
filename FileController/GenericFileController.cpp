/*
 * GenericFileController.cpp
 *
 *  Created on: Jun 22, 2015
 *      Author: jlochman
 */

#include <iostream>

#include "GenericFileController.h"

GenericFileController::GenericFileController(string fileName, string treeName, bool build) {
	const char* option = "";
	if ( build ) option = "RECREATE"; else option = "READ";
	m_File = new TFile(fileName.c_str(), option);
	if ( m_File->GetListOfKeys()->Contains( (treeName).c_str() ) ) {
		m_Tree = (TTree*) m_File->Get( treeName.c_str() );
	} else {
		m_Tree = new TTree(treeName.c_str(), treeName.c_str());
	}
	// pozor... int je do 2,147,483,647
	MAX_VEC_LENGTH = (int) 1e9;

	if ( build ) cout << "[BUILD] ";
	else cout << "[LOAD]  ";
}

GenericFileController::~GenericFileController() {
}

void GenericFileController::load() {
	for ( unsigned int i = 0; i < data_vec.size(); i++ ) {
		cout << "... loading [" << i+1 << "/" << data_vec.size() << "] " << data_vec.at(i)->getName() << endl;
		data_vec.at(i)->read(m_Tree);
	}
/*
	std::vector<double> x_vec;
	x_vec.resize( data_vec.size() );
	for ( unsigned int i = 0; i < data_vec.size(); i++ ) {
		m_Tree->SetBranchAddress( data_vec.at(i)->getName().c_str(), &x_vec.at(i));
		data_vec.at(i)->setVecSize( (int) m_Tree->GetEntries() );
	}
	for ( unsigned int i = 0; i < m_Tree->GetEntries(); i++ ) {
		m_Tree->GetEntry(i);
		for ( unsigned int k = 0; k < data_vec.size(); k++ ) {
			//data_vec.at(k)->addValue( x_vec.at(k));
			data_vec.at(k)->setValue(i, x_vec.at(k));
		}
	}
*/
}

void GenericFileController::save(TTree* toTree) {
	int vec_length = getMinVecSize();
	if ( toTree == 0 ) toTree = m_Tree;
	for ( unsigned int i = 0; i < data_vec.size(); i++ ) {
		cout << "... saving [" << i+1 << "/" << data_vec.size() << "] " << data_vec.at(i)->getName() << endl;
		data_vec.at(i)->write(toTree, vec_length, toTree->GetEntries() == 0);
	}
	/*
	int vec_length = getMinVecSize();
	if ( toTree == 0 ) toTree = m_Tree;

	std::vector<double> x_vec;
	x_vec.resize( data_vec.size() );

	if ( toTree->GetEntries() == 0 ) {
		for ( unsigned int i = 0; i < data_vec.size(); i++ ) {
			toTree->Branch( data_vec.at(i)->getName().c_str(), &x_vec.at(i), (data_vec.at(i)->getName()+"/D").c_str() );
		}
		for ( unsigned int i = 0; i < vec_length; i++ ) {
			for ( unsigned int k = 0; k < data_vec.size(); k++ ) {
				x_vec.at(k) = data_vec.at(k)->getValue(i);
			}
			toTree->Fill();
		}
		toTree->Write("", TObject::kOverwrite);
	} else {
		for ( unsigned int i = 0; i < data_vec.size(); i++ ) {
			cout << "... saving " << data_vec.at(i)->getName() << endl;
			data_vec.at(i)->write(toTree, vec_length, false);
		}
	}
	*/
}

int GenericFileController::getMinVecSize() {
	int result = MAX_VEC_LENGTH;
	int k = 0;
	for ( unsigned int i = 0; i < data_vec.size(); i++ ) {
		k = data_vec.at(i)->getVec().size();
		if ( k < result ) result = k;
	}
	return result;
}

void GenericFileController::clear() {
	data_vec.resize(0);
}

const vector<double>* GenericFileController::getVecByName(string vecName) {
	int k = -1;
	for ( int i = 0; i < data_vec.size(); i++ ) {
		if ( data_vec.at(i)->getName() == vecName ) {
			k = i;
			break;
		}
	}
	if ( k >= 0 ) return &data_vec.at(k)->getVec();
	else {
		cerr << "data_vec not found " << vecName << endl;
		return 0;
	}
}

GenericDataController* GenericFileController::getGenDCByName(string genDCName) {
	int k = -1;
	for ( int i = 0; i < data_vec.size(); i++ ) {
		if ( data_vec.at(i)->getName() == genDCName ) {
			k = i;
			break;
		}
	}
	if ( k >= 0 ) return data_vec.at(k);
	else {
		cerr << "generic Data Controller not found " << genDCName << endl;
		return 0;
	}
}


const double GenericFileController::getValue(string genDCName, int pos) {
	double result = 0;
	for ( int i = 0; i < data_vec.size(); i++ ) {
		if ( data_vec.at(i)->getName() == genDCName ) {
			result = data_vec.at(i)->getValue( pos );
			break;
		}
	}
	return result;
}

GenericDataController* GenericFileController::getGenDCByIndex(int index) {
	if ( index < 0 ) return 0;
	if ( index > getGenDCCount() ) return 0;
	return data_vec.at(index);
}

const int GenericFileController::getGenDCCount() {
	return data_vec.size();
}

const vector<double>* GenericFileController::getVecByIndex(int index) {
	if ( index < 0 ) return 0;
	if ( index > getGenDCCount() ) return 0;
	return &data_vec.at(index)->getVec();
}

TTree* GenericFileController::getTree() {
	return m_Tree;
}
