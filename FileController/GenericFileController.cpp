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
	MAX_VEC_LENGTH = (int) 2e9;

	if ( build ) cout << "[BUILD] ";
	else cout << "[LOAD]  ";
}

GenericFileController::~GenericFileController() {
}

void GenericFileController::load() {
	for ( unsigned int i = 0; i < data_vec.size(); i++ ) {
		data_vec.at(i)->read(m_Tree);
	}
}

void GenericFileController::save(TTree* toTree) {
	int vec_length = getMinVecSize();
	if ( toTree == 0 ) toTree = m_Tree;
	for ( unsigned int i = 0; i < data_vec.size(); i++ ) {
		cout << "... saving " << data_vec.at(i)->getName() << endl;
		data_vec.at(i)->write(toTree, vec_length, toTree->GetEntries() == 0);
	}
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
