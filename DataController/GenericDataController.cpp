/*
 * GenericDataController.cpp
 *
 *  Created on: Jun 22, 2015
 *      Author: jlochman
 */

#include <iostream>

#include "TBranch.h"

#include "GenericDataController.h"

GenericDataController::GenericDataController(string branchName) {
	m_branchName = branchName;
	m_className = "GenericDataContoller";
	histNeeded = 0;
	m_calcIncrement = 10;
}

GenericDataController::~GenericDataController() {
}

const vector<double>& GenericDataController::getVec() const {
	return m_vec;
}

void GenericDataController::write(TTree* t, int length, bool first) {
	double x = 0;
	if ( first ) {
		t->Branch( m_branchName.c_str(), &x, (m_branchName+"/D").c_str() );
		for ( unsigned int i = 0; i < length; i++ ) {
			x = m_vec.at(i);
			t->Fill();
		}
		t->Write("", TObject::kOverwrite);
	} else {
		TBranch *b = t->Branch( m_branchName.c_str(), &x, (m_branchName+"/D").c_str() );
		for ( unsigned int i = 0; i < length; i++ ) {
			t->GetEntry(i);
			x = m_vec.at(i);
			b->Fill();
		}
		t->Write("", TObject::kOverwrite);
	}
}

void GenericDataController::read(TTree* t) {
	double x = 0;
	t->SetBranchAddress(m_branchName.c_str(), &x);
	m_vec.resize( t->GetEntries() );
	for ( unsigned int i = 0; i < t->GetEntries(); i++ ) {
		t->GetEntry(i);
		m_vec.at(i) = x;
	}
}

void GenericDataController::empty() {
	m_vec.resize(0);
}

void GenericDataController::addValue(double x) {
	m_vec.push_back(x);
}

void GenericDataController::pushForwardValue(double x) {
	m_vec.insert( m_vec.begin(), x );
}

void GenericDataController::reverseOrder() {
	std::reverse( m_vec.begin(), m_vec.end() );
}

void GenericDataController::setValue(int pos, double x) {
	m_vec.at(pos) = x;
}

double GenericDataController::getValue(int pos) {
	return m_vec.at(pos);
}

void GenericDataController::setVec(const vector<double>& vec) {
	m_vec = vec;
}

string GenericDataController::getName() {
	return m_branchName;
}

int GenericDataController::getHistNeeded() const {
	return histNeeded;
}

int GenericDataController::getVecSize() {
	return m_vec.size();
}

const string& GenericDataController::getClassName() const {
	return m_className;
}
