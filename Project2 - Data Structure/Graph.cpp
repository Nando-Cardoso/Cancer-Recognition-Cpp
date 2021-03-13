// Fernando Rodrigues Cardoso
// Nov. 28, 2019
//Definign Graphs class attributes
#include "Graph.h"
#include "NodeGraph.h"
#include <iomanip>
#include <sstream>
#include <fstream>

using namespace std;

//Graph class constructor
Graph::Graph(int numVertices) {
	this->numVertices_ = numVertices;
	vector<NodeGraph*> rows;
	for (int i = 0; i < numVertices; i++) {
		adjMatrix.push_back(rows);
		for (int j = 0; j < numVertices; j++)
			adjMatrix[i].push_back(new NodeGraph(0,0));
	}
}

//Add an edge
void Graph::addEdge(int gender, int age) {		
	adjMatrix[gender][age]->next_ = adjMatrix[age][gender];
	adjMatrix[age][gender]->next_ = adjMatrix[gender][age];
}

//Change weight of an edge
void Graph::changeWeight(int gender, int age, int weight) {
	adjMatrix[gender][age]->data_ += weight;
}

//Function prints graph content and also output a csv file with the output.
void Graph::printAndOutputGraph(int cancerType) {
	stringstream ss;
	vector<string> riskFactors{ "Gender", "Age", "Genetic", "Family", "Overweight", "Alcoholic", "Smoking", "HRT" };
	ofstream benignOutput, malignOutput;
	if (cancerType == 2) {
		cout << "         Benign       Gender     Age     Genetic    Family Overweight Alcoholic    Smoking   HRT" << endl;
		ss << "Benign;Gender;Age;Genetic;Family;Overweight;Alcoholic;Smoking;HRT\n";
		benignOutput.open("adjMatrixBenign.csv");
	}

	else {
		cout << "         Malign       Gender     Age     Genetic    Family Overweight Alcoholic    Smoking   HRT" << endl;
		ss << "Malign;Gender;Age;Genetic;Family;Overweight;Alcoholic;Smoking;HRT\n";
		malignOutput.open("adjMatrixMalign.csv");
	}

	for (int i = 0; i < numVertices_; i++) {
		ss << riskFactors[i] << ":;";
		cout << setw(14) << right << riskFactors[i] << ":";
		for (int j = 0; j < numVertices_; j++) {
			ss << adjMatrix[i][j]->data_ << ";";
			cout << setw(10) << adjMatrix[i][j]->data_;
		}
		ss << "\n";
		cout << "\n";
	}
	ss << "\n";
	cout << endl;

	
	if (benignOutput.is_open()) {
		benignOutput << ss.str();
		benignOutput.close();
	}

	else {
		malignOutput << ss.str();
		malignOutput.close();
	}
}

//Graph class destrcutor definition
Graph::~Graph() {
	for (int i = 0; i < numVertices_; i++) {
		for (int j = 0; j < numVertices_; j++)
			delete adjMatrix[i][j];
	}

}