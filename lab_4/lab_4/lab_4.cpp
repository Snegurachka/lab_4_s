#include "pch.h"
#include <fstream> 
#include <vector>
#include <strstream>
#include <iostream>
#include <list>
#include <algorithm>
#include <functional>
#include <iterator>
#include <string>
#include <sstream>
#include <stdio.h>
#include "Parser.h"
#include "ZVector.h"
#include <chrono>
#include "Solver.h"


using namespace std;

int main() {
	double eps = 0.01;
	int timeMeasured;

	MatrixFile matrixFile;
	matrixFile.getStringMatrix();

	vector<double>* aelem1 = matrixFile.getAelemFile();
	vector<int>* jptr1 = matrixFile.getJptrFile();
	vector<int>* iptr1 = matrixFile.getIptrFile();

	Matrix matrixA;
	matrixA.createMatrix(aelem1, jptr1, iptr1);
	ZVector X;
	X.addOnes(matrixA.getSize());
	ZVector B = matrixA * X;


	auto start = std::chrono::steady_clock::now();

	auto solver = new Solver(eps, matrixA, B);
	solver->solve();

	auto end = std::chrono::steady_clock::now();
	long long int tickPerSec = 1000000000;
	timeMeasured = (end - start).count() / (tickPerSec / 1000);

	const ZVector &v = X - solver->getX();
	cout << endl << "||X - X~|| = " << v * v << endl;
	cout << "Time = " << timeMeasured << endl;


	//Matrix matrix2;
	//matrix2.createTwoMatrix(aelem1, jptr1, iptr1);


/*
	Matrix matrixA;
	matrixA.createMatrixA(aelem1, iptr1, jptr1);
*/

/*
for (int i = 0; i < matrixA.aelem->size(); i++) {
		cout << matrixA.aelem->at(i) << " ";
	}
	cout << endl;
	for (int i = 0; i < matrixA.jptr->size(); i++) {
		cout << matrixA.jptr->at(i) << " ";
	}
	cout << endl;

	for (int i = 0; i < matrixA.ip->size(); i++) {
		cout << matrixA.ip->at(i) << " ";
	}
	cout << endl;


*/
	
/*
	for (int i = 0; i < matrix2.aelem->size(); i++) {
		cout << matrix2.aelem->at(i) << " ";
	}
	cout << endl;
	for (int i = 0; i < matrix2.jptr->size(); i++) {
		cout << matrix2.jptr->at(i) << " ";
	}
	cout << endl;

	for (int i = 0; i < matrix2.ip->size(); i++) {
		cout << matrix2.ip->at(i) << " ";
	}
	cout << endl;



*/


	cout << endl;
	cout << "THE END" << endl;


	system("pause");
	return 0;
}