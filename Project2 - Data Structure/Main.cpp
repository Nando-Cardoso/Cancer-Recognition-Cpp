// Fernando Rodrigues Cardoso
// Nov. 28, 2019
// Main for cancer imaging project

#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <crtdbg.h>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include "BinaryTree.h"
#include "Graph.h"

using namespace std;

int main() {
#if defined(_DEBUG)	
	int dbgFlags = ::_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);	
	dbgFlags |= _CRTDBG_CHECK_ALWAYS_DF;	
	dbgFlags |= _CRTDBG_DELAY_FREE_MEM_DF;	
	_CrtSetDbgFlag(dbgFlags);
#endif

	//Opening filestream to read csv files
	fstream csvFile("wisconsin data.csv");
	fstream csvRiskFile("risk factor data.csv");

	//Checking if file opening went well
	if (!csvFile || !csvRiskFile) {
		cout << "Error Opening File(s)!" << endl;
		return EXIT_FAILURE;
	}
	
	//Declaring all variables that are going to be used
	string line = "", line2 = "";
	int count1 = 0, count2 = 0;
	int numberOfBenign = 0, numberOfMalign = 0, numberOfPatients = 0, uniformityCellSize = 0, bareNuclei = 0, clumpThickness = 0, blandChromatin = 0, marginalAdhesion = 0, uniformityCellShape = 0;
	enum typeOfCancer {Benign = 2, Malign = 4};
	stringstream ss;
	vector<int> valuesInt;
	vector<string> valuesString;
	Graph *benignGraph = new Graph(8);
	Graph *malignGraph = new Graph(8);

	cout << "Parsing Files...\n" << endl;
	//While loop that will read wisconsin data.csv data
	while (getline(csvFile, line, ',')) {

		//Counter to know when an entire line has been read
		count2++;

		//If an entire line has been read enter this if statement
		if (count2 == 11) {
			count2 = 1;

			//Putting data parsed into variables
			clumpThickness = valuesInt[0];
			uniformityCellSize = valuesInt[1];
			uniformityCellShape = valuesInt[2];
			marginalAdhesion = valuesInt[3];
			bareNuclei = valuesInt[5];
			blandChromatin = valuesInt[6];

			//binary tree object
			BinaryTree* bTree = new BinaryTree();

			//binary tree hierarchy definition
			bTree->insert(uniformityCellSize, 2, bTree->root_);
			bTree->insert(bareNuclei, 3,  bTree->root_->left_);
			bTree->insert(Benign, 0, bTree->root_->left_->left_);
			bTree->insert(clumpThickness, 3, bTree->root_->left_->right_);
			bTree->insert(Benign, 0, bTree->root_->left_->right_->left_);
			bTree->insert(blandChromatin, 2, bTree->root_->left_->right_->right_);
			bTree->insert(marginalAdhesion, 3, bTree->root_->left_->right_->right_->left_);
			bTree->insert(Malign, 0, bTree->root_->left_->right_->right_->right_);
			bTree->insert(Malign, 0, bTree->root_->left_->right_->right_->left_->left_);
			bTree->insert(Benign, 0, bTree->root_->left_->right_->right_->left_->right_);

			bTree->insert(uniformityCellShape, 2, bTree->root_->right_);
			bTree->insert(clumpThickness, 5, bTree->root_->right_->left_);
			bTree->insert(Benign, 0, bTree->root_->right_->left_->left_);
			bTree->insert(Malign, 0, bTree->root_->right_->left_->right_);
			bTree->insert(uniformityCellSize, 4, bTree->root_->right_->right_);
			bTree->insert(Malign, 0, bTree->root_->right_->right_->right_);
			bTree->insert(bareNuclei, 2, bTree->root_->right_->right_->left_);
			bTree->insert(marginalAdhesion, 3, bTree->root_->right_->right_->left_->left_);
			bTree->insert(Benign, 0, bTree->root_->right_->right_->left_->left_->left_);
			bTree->insert(Malign, 0, bTree->root_->right_->right_->left_->left_->right_);
			bTree->insert(clumpThickness, 6, bTree->root_->right_->right_->left_->right_);
			bTree->insert(Malign, 0, bTree->root_->right_->right_->left_->right_->right_);
			bTree->insert(uniformityCellSize, 3, bTree->root_->right_->right_->left_->right_->left_);
			bTree->insert(Malign, 0, bTree->root_->right_->right_->left_->right_->left_->left_);
			bTree->insert(marginalAdhesion, 5, bTree->root_->right_->right_->left_->right_->left_->right_);
			bTree->insert(Benign, 0, bTree->root_->right_->right_->left_->right_->left_->right_->left_);
			bTree->insert(Malign, 0, bTree->root_->right_->right_->left_->right_->left_->right_->right_);

			//Using binary tree recursive search to determine if patient is benign or malign
			int cancerType = bTree->recursiveSearch(bTree->root_, 0, bTree->root_->condition_);
			
			//If patient is benign, increment benign patients counter and check for patient risk factors
			if (cancerType == Benign) {
				numberOfBenign++;
				while (getline(csvRiskFile, line2)) {

					ss << line2;
					while (getline(ss, line2, ',')) {
						if (line2.length() < 3)
							valuesString.push_back(line2);
					}

					ss.str(string());
					ss.clear();

					//checking for risk factors relation adding edge and adding weight
					for (size_t i = 0; i < benignGraph->numVertices_; i++) {
						for (size_t j = 0; j < benignGraph->numVertices_; j++) {
							if (valuesString[i] == "T") {
								if (valuesString[j] == "T" && j != i) {
									if (benignGraph->adjMatrix[i][j]->data_ == 0)
										benignGraph->addEdge(i, j);
									benignGraph->changeWeight(i, j, 1);
								}
							}
							else {
								break;
							}
						}
					}

					//clearing csv data string
					valuesString.clear();
					break;
				}
			}

			//If patient is malign, increment malign patients counter and check for patient risk factors
			else if (cancerType == Malign) {
				numberOfMalign++;
				while (getline(csvRiskFile, line2)) {

					ss << line2;
					while (getline(ss, line2, ',')) {
						if (line2.length() < 3)
							valuesString.push_back(line2);
					}

					ss.str(string());
					ss.clear();

					//checking for risk factors relation adding edge and adding weight
					for (size_t i = 0; i < malignGraph->numVertices_; i++) {
						for (size_t j = 0; j < malignGraph->numVertices_ ; j++) {
							if (valuesString[i] == "T") {
								if (valuesString[j] == "T" && j != i) {
									if (malignGraph->adjMatrix[i][j]->data_ == 0)
										malignGraph->addEdge(i, j);
									malignGraph->changeWeight(i, j, 1);
								}
							}
							else {
								break;
							}
						}
					}
					//clearing csv data string
					valuesString.clear();
					break;
				}
			}
			
			//Clearing first csv file vector data
			valuesInt.clear();
		}

		//If data parsed is a "?" push "1" to vector
		if (line == "?")
			valuesInt.push_back(1);
		//else, convert data to int with stoi and push to vector
		else if (line.length() < 3 && line != "0")
			valuesInt.push_back(stoi(line));
	}

	//calculating total patients
	numberOfPatients = numberOfBenign + numberOfMalign;

	//OUTPUT
	stringstream os;
	cout << "Number of patients is: " << numberOfPatients << endl;
	cout << "Number of benign patients is: " << numberOfBenign << endl;
	cout << "Number of malign patients is: " << numberOfMalign << endl << endl;
	os << "Number of patients is:;;;" << numberOfPatients << endl;
	os << "Number of benign patients is:;;;" << numberOfBenign << endl;
	os << "Number of malign patients is:;;;" << numberOfMalign << endl;
	benignGraph->printAndOutputGraph(Benign);
	cout << endl;
	malignGraph->printAndOutputGraph(Malign);
	ofstream outputFile;
	outputFile.open("wisconsin-results.csv");
	outputFile << os.str();

	//Closing files
	outputFile.close();
	csvFile.close();
}
