
#include <vector>
#include <iostream>
#include "ZVector.h"

using namespace std;

class Matrix {
public:
	vector<double>* aelem;
	vector<int>* jptr;
	vector<int>* ipt;
	vector<int>* iptr;

	int findMax(vector<int>* iptrr) {
		int max = 0;
		for (int i = 0; i < iptrr->size(); i++) {
			if ((*iptrr)[i] > max) {
				max = (*iptrr)[i];
			}
		}
		return max;
	}

	int getSize() const {
		return (iptr->size() - 1);
	}
		
	ZVector operator*(const ZVector &v) const {
		ZVector result = ZVector(vector<double>(getSize()));
		double elem;
		int columnId;
		for (int i = 0; i < getSize(); i++) {
			elem = 0;
			for (int k = (*iptr)[i]; k < (*iptr)[i + 1]; k++) {
				columnId = (*jptr)[k - 1];
				elem += (*aelem)[k - 1] * v[columnId - 1];
			}
			result.set(i, elem);
		}
		return result;
	}

	void multiply(const ZVector &v, ZVector& result) const {
		double elem;
		int columnId;
		for (int i = 0; i < getSize(); i++) {
			elem = 0;
			for (int k = (*iptr)[i]; k < (*iptr)[i + 1]; k++) {
				columnId = (*jptr)[k - 1];
				elem += (*aelem)[k - 1] * v[columnId - 1];
			}
			result.set(i, elem);
		}
	}

	double vectorMulti(const ZVector &v, const ZVector &v2) const {
		double result = 0;
		double elem;
		int columnId;
		for (int i = 0; i < getSize(); i++) {
			elem = 0;
			for (int k = (*iptr)[i]; k < (*iptr)[i + 1]; k++) {
				columnId = (*jptr)[k - 1];
				elem += (*aelem)[k - 1] * v[columnId - 1];
			}
			result += elem * v2[i];
		}
		return result;
	}


	void createMatrix(vector<double>* aelemFile, vector<int>* jptrFile, vector<int>* iptrFile) {
		aelem = new vector<double>();
		jptr = new vector<int>();
		ipt = new vector<int>();
		iptr = new vector<int>();
		createMatrixHalf(aelemFile, jptrFile, iptrFile, 1);
	}

	void createTwoMatrix(vector<double>* aelemFile, vector<int>* jptrFile, vector<int>* iptrFile) {
		createMatrixHalf(aelemFile, iptrFile, jptrFile, 2);
	}

	void createMatrixHalf(vector<double>* aelemFile, vector<int>* jptrFile, vector<int>* iptrFile, int oneTwo) {
		int max = findMax(iptrFile);
		//cout << max << endl;
		vector<vector<double>> matrixStringValue;
		vector<vector<int>> matrixStringI;
		vector<vector<int>> matrixStringJ;

		vector<vector<double>> matrixStringValue2;
		vector<vector<int>> matrixStringI2;
		vector<vector<int>> matrixStringJ2;
		for (int i = 0; i < max; i++) {
			vector<double> tempDouble;
			vector<int> tempInt;
			matrixStringValue.push_back(tempDouble);
			matrixStringI.push_back(tempInt);
			matrixStringJ.push_back(tempInt);

			matrixStringValue2.push_back(tempDouble);
			matrixStringI2.push_back(tempInt);
			matrixStringJ2.push_back(tempInt);

		}

		//cout << iptrFile->size() << " " << jptrFile->size() << " " << aelemFile->size() << endl;
		for (int i = 0; i < iptrFile->size(); i++) {
			if (oneTwo == 1) {
				//if ((*iptrFile)[i] != (*jptrFile)[i]) {
					matrixStringValue[(*iptrFile)[i] - 1].push_back((*aelemFile)[i]);
					matrixStringI[(*iptrFile)[i] - 1].push_back((*iptrFile)[i]);
					matrixStringJ[(*iptrFile)[i] - 1].push_back((*jptrFile)[i]);

				
			}
			else if (oneTwo == 2) {
				if ((*iptrFile)[i] != (*jptrFile)[i]) {
					matrixStringValue[(*iptrFile)[i] - 1].push_back((*aelemFile)[i]);
					matrixStringJ[(*iptrFile)[i] - 1].push_back((*iptrFile)[i]);
					matrixStringI[(*iptrFile)[i] - 1].push_back((*jptrFile)[i]);
				}

			}
		}

		for (int i = 0; i < jptrFile->size(); i++) {
			if (oneTwo == 1) {
				if ((*jptrFile)[i] != (*iptrFile)[i]) {
					matrixStringValue[(*jptrFile)[i] - 1].push_back((*aelemFile)[i]);
					matrixStringI[(*jptrFile)[i] - 1].push_back((*jptrFile)[i]);
					matrixStringJ[(*jptrFile)[i] - 1].push_back((*iptrFile)[i]);
				}

			}
		}


		for (int i = 0; i < matrixStringValue.size(); i++) {
			for (int j = 0; j < matrixStringValue[i].size(); j++) {
				aelem->push_back(matrixStringValue[i][j]);
				ipt->push_back(matrixStringI[i][j]);
				jptr->push_back(matrixStringJ[i][j]);
			}
		}
		int t;
		t = (*ipt)[0];
		iptr->push_back(1);
		for (int i = 0; i < ipt->size(); i++) {

			if ((*ipt)[i] > t) {
				iptr->push_back(i + 1);
				t = (*ipt)[i];
			}
		}
		iptr->push_back(aelem->size() + 1);
		delete ipt;
	}
};

