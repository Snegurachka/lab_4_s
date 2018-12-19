#pragma once
#include <vector>

using namespace std;

class ZVector {
public:
	ZVector() { }

	ZVector(double item) {
		items.push_back(item);
	}

	void addOnes(int size) {
		for (int i = 0; i < size; i++) {
			items.push_back(1);
		}
	}

	void addElement(double element) {
		items.push_back(element);
	}

	ZVector operator+(double item) const {
		vector<double> items(this->items);
		items.push_back(item);
		return ZVector(items);
	}

	ZVector(const vector<double> &items) : items(items) {}

	const double& operator[](int i) const {
		return items[i];
	}

	size_t size() const {
		return items.size();
	}

	ZVector shiftAll(const double item) const {
		vector<double> result(size());
		for (int i = 0; i < size(); ++i) {
			result[i] = (*this)[i] + item;
		}
		return ZVector(result);
	}

	ZVector concat(const ZVector& toAdd) const {
		vector<double> result;
		result.insert(result.end(), items.begin(), items.end());
		result.insert(result.end(), toAdd.items.begin(), toAdd.items.end());
		return ZVector(result);
	}

	ZVector operator+(const ZVector& toAdd) const {
		vector<double> result(size());
		for (size_t i = 0; i < size(); ++i) {
			result[i] = (*this)[i] + toAdd[i];
		}
		return ZVector(result);
	}

	void add(const ZVector& toAdd) {
		for (size_t i = 0; i < size(); ++i) {
			items[i] += toAdd[i];
		}
	}


	ZVector operator-() const {
		vector<double> result(size());
		for (size_t i = 0; i < size(); ++i) {
			result[i] = -(*this)[i];
		}
		return ZVector(result);
	}

	ZVector operator-(const ZVector& right) const {
		return operator+(-right);
	}

	double operator*(const ZVector& right) const {
		double result = 0;
		for (size_t i = 0; i < size(); ++i) {
			result += (*this)[i] * right[i];
		}
		return result;
	}

	ZVector operator*(const double c) const {
		vector<double> result(size());
		for (size_t i = 0; i < size(); ++i) {
			result[i] = (*this)[i] * c;
		}
		return ZVector(result);
	}

	void multiply(const double c, ZVector& result) const {
		for (size_t i = 0; i < size(); ++i) {
			result.set(i, (*this)[i] * c);
		}
	}

	void multiply(const double c) {
		for (size_t i = 0; i < size(); ++i) {
			set(i, (*this)[i] * c);
		}
	}

	const double* last() const {
		return &(items[items.size() - 1]);
	}

	double sum() const {
		double s = 0;
		for (size_t i = 0; i < size(); ++i) {
			s += items[i];
		}
		return s;
	}

	void set(int index, double value) {
		items[index] = value;
	}

	void clear() {
		std::fill(items.begin(), items.end(), 0);
	}

private:
	vector<double> items;
};
