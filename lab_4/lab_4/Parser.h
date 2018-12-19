#pragma once
#include <vector>
#include <fstream> // подключаем файлы
#include <string>

using namespace std;

class MatrixFile {
private:
	vector<double>* aelemFile = new vector<double>();
	vector<int>* jptrFile = new vector<int>();
	vector<int>* iptrFile = new vector<int>();

public:
	vector<double>* getAelemFile() { return aelemFile; }
	vector<int>* getJptrFile() { return jptrFile; }
	vector<int>* getIptrFile() { return iptrFile; }

	void getStringMatrix() {
		string s;
		ifstream file("C:\\Users\\i347859\\OneDrive - SAP SE\\Desktop\\MMMSPiS\\LaboratoryWorks\\Budyukina_Elena\\Lab 4\\lab_4\\lab_4\\bcsstk17.mtx");
		int countstr = 0;
		while (getline(file, s)) {
			int elementI;
			int elementJ;
			double elementValue;
			int countX;
			int countY;
			int countAll;
			countstr++;
			//if (countstr % 100 == 0) {
			//	cout << countstr << endl;
			//}
			//cout << s << endl; 


			if (countstr > 2) {
				sscanf_s(s.c_str(), "%d %d %lf", &elementI, &elementJ, &elementValue);
				aelemFile->push_back(elementValue);
				iptrFile->push_back(elementI);
				jptrFile->push_back(elementJ);
				//cout << "a=" << a << " b=" << b << " c=" << c << endl;
				//addstring(elementJ, elementI, elementValue, aelem, jptr, iptr);
			}
		}
		file.close();
	}
};