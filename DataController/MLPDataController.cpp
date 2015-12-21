/*
 * MLPDataController.cpp
 *
 *  Created on: Jun 24, 2015
 *      Author: jlochman
 */

#include <iostream>
#include <fstream>
#include <algorithm>

#include "TTree.h"
#include "TDirectory.h"

#include "MLPDataController.h"

MLPDataController::MLPDataController(std::string branchName, TTree* in_Tree, const std::string topology, const std::string weight_file, int train_cycles)
	: GenericDataController(branchName) {
	m_className = "MLP";

	m_inTree = in_Tree;
	m_topology = topology;
	m_weightFile = weight_file;
	NUMBER_OF_TRAIN_CYCLES = train_cycles;

	cout << "=::: preparing TMultiLayerPerceptron " << branchName << endl;
	cout << "=::: topology: " << topology << endl;
	cout << "=::: weightFile: " << weight_file << endl;
	cout << "=::: TTree: " << m_inTree->GetName() << "; entries: " << m_inTree->GetEntries() << endl;

	m_MLP = new TMultiLayerPerceptron(m_topology.c_str(), m_inTree, "Entry$%2==0", "", TNeuron::kTanh);

	//m_inTree->Draw((">>"+branchName+"Train").c_str(), "Entry$>=2000 && Entry$ % 2 == 0" );
	//m_inTree->Draw((">>"+branchName+"Test").c_str(), "Entry$>=2000 && Entry$ % 2 == 1");

	m_inTree->Draw((">>"+branchName+"Train").c_str(), "Entry$ % 2 == 0" );
	m_inTree->Draw((">>"+branchName+"Test").c_str(), "Entry$ % 2 == 1");

	TEventList *elistTrain = (TEventList*)gDirectory->Get((branchName+"Train").c_str());
	TEventList *elistTest = (TEventList*)gDirectory->Get((branchName+"Test").c_str());
	m_MLP->SetTrainingDataSet( elistTrain );
	m_MLP->SetTestDataSet( elistTest );
}

MLPDataController::~MLPDataController() {
}

void MLPDataController::calculate(int maxCount) {
	vector<string> inputs = this->getInputs();
	double *params = new double[ inputs.size() ];

	for ( unsigned int i = 0; i < inputs.size(); i++ ) {
		m_inTree->SetBranchAddress( inputs.at(i).c_str(), &params[i] );
	}

	cout << "  " + m_MLP->GetStructure() << endl;

	for ( int i = 0; i < m_inTree->GetEntries(); i++ ) {
		m_inTree->GetEntry(i);
		m_vec.push_back( m_MLP->Evaluate(0, params) );
	}
}

void MLPDataController::save_Weights() {
	m_MLP->DumpWeights( (m_weightFile+".weights").c_str() );
}

void MLPDataController::export_NN() {
	m_MLP->Export( m_weightFile.c_str(), "C++" );

	string s_header = 	m_weightFile+".h";
	string s_source = 	m_weightFile+".cxx";
	string s_java = 	m_weightFile+".java";
	ifstream header( s_header );
	ifstream source( s_source );
	ofstream javaFile( s_java );
	string line;
	string myClass;
	int i = m_weightFile.find_last_of('/');
	if ( i != string::npos )
	    myClass = m_weightFile.substr(i+1);
	else myClass = this->getName();

	javaFile << "package cz.jlochman.jforex.mlp;" << endl;
	javaFile << "" << endl;
	javaFile << "public class " + myClass + " extends MLP {" << endl;
	javaFile << "" << endl;
	javaFile << "public " + myClass + "(String inputs) {" << endl;
	javaFile << "   super(inputs);" << endl;
	javaFile << "}" << endl;
	javaFile << "" << endl;

	if (header.is_open()) {
		while ( getline(header, line) ) {
			if ( line.find("input") != string::npos
					&& line.find("x") == string::npos ) {
				javaFile << "private " << line << endl;
			}
		}
	}
	javaFile << "" << endl;

	getline(source, line);
	getline(source, line);
	getline(source, line);
	if (header.is_open()) {
		bool inSwitch = false;
		while ( getline(source, line) ) {
			if ( ContainsString(line, "switch") ) {
				inSwitch = true;
			}
			if ( inSwitch ) {
				if ( ContainsString(line, "switch") )
					javaFile << line << endl;
				if ( ContainsString(line, "case") )
					javaFile << line << endl;
				if ( ContainsString(line, "default") ) {
					javaFile << line << endl;
				}
				if ( ContainsString(line, "return") ) {
					ReplaceString( line, "return", "m_values.insert(");
					ReplaceString( line, ";", " );");
					javaFile << line << endl;
					javaFile << "         break;" << endl;
				}
				if ( ContainsString(line, "}") ) {
					javaFile << line << endl;
					inSwitch = false;
				}
			} else {
				ReplaceString( line, myClass+"::", "" );
				ReplaceString( line, "double*", "double[]" );
				ReplaceString( line, "exp", "Math.exp" );
				ReplaceString( line, "double Value", "public void Value" );
				ReplaceString( line, "double neuron0x", "private double neuron0x" );
				ReplaceString( line, "double input0x", "private double input0x" );
				ReplaceString( line, "double synapse0x", "private double synapse0x" );
				javaFile << line << endl;
			}
		}
	}

	javaFile << "}" << endl;
	javaFile.close();

	remove( s_header.c_str() );
	remove( s_source.c_str() );
}

void MLPDataController::load_Weights() {
	m_MLP->LoadWeights( (m_weightFile+".weights").c_str() );
}

void MLPDataController::train_NN() {
	std::cout << m_MLP->GetName() << std::endl;
	std::cout << m_MLP->GetStructure() << std::endl;
	m_MLP->Train( NUMBER_OF_TRAIN_CYCLES, "text,update=1,+" );
}

vector<string> MLPDataController::getInputs() {
	vector<string> result;

	stringstream ssTopology(m_topology);
	string token;
	getline(ssTopology,token, ':');

	stringstream ssInput(token);
	while ( getline(ssInput,token, ',') ) {
		ReplaceString(token, "@", "");
		result.push_back(token);
	}
	return result;
}

string MLPDataController::getOutputBranchName() {
	string result = "";
	stringstream ssTopology(m_topology);
	string token;

	while ( getline(ssTopology,token, ':') ) {
		result = token;
	}

	return result;
}

void MLPDataController::ReplaceString(string &subject, const string &search, const string &replace) {
    if ( subject.empty() ) return;
    size_t start_pos = 0;
    while ( ( start_pos = subject.find(search, start_pos) ) != std::string::npos) {
    	subject.replace(start_pos, search.length(), replace);
        start_pos += replace.length();
    }
}



bool MLPDataController::ContainsString(const string &subject, const string &search) {
	if (subject.find(search) != string::npos) {
	    return true;
	} else return false;
}

