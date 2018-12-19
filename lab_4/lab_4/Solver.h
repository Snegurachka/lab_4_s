#pragma once

#include <math.h>
#include "Matrix.h"

class Solver;

class Iteration {
public:
	Iteration(Solver &solver) : solver(solver) {
		x = ZVector();
		h = ZVector();
		r = ZVector();
	}

	void calculateAlpha();

	void calculateR(const ZVector& prevR, const ZVector& prevH, double prevAlpha);

	void calculateBeta(const ZVector& prevR);

	void calculateH(const ZVector &prevH);

	void xNext(const ZVector& prevX, const ZVector& prevH, const double alpha);

	void clear();

	ZVector x;
	ZVector h;
	double beta;
	double alpha;
	ZVector r;
	Solver& solver;
};



class Solver {
public:
	size_t counter = 0;
	const Matrix & A;
	const ZVector & B;

	Solver(double eps, const Matrix &A, const ZVector &B) : eps(eps), A(A), B(B) { }

	void solve() {
		init();
		while (!shouldStopIteration()) {
			counter++;
			cout << counter << endl;
			iterate();
		}
	}

	ZVector & getX() {
		return nextIteration->x;
	}

private:
	Iteration* prevIteration = nullptr;
	Iteration* nextIteration = nullptr;

	void init() {
		prevIteration = new Iteration(*this);
		nextIteration = new Iteration(*this);
		nextIteration->x = getApproximation();
		nextIteration->h = h0();
		nextIteration->r = nextIteration->h;
		nextIteration->calculateAlpha();
	}

	void iterate() {
		updatePointers();

		nextIteration->xNext(prevIteration->x, prevIteration->h, prevIteration->alpha);

		nextIteration->calculateR(prevIteration->r, prevIteration->h, prevIteration->alpha);
		nextIteration->calculateBeta(prevIteration->r);

		nextIteration->calculateH(prevIteration->h);
		nextIteration->calculateAlpha();
	}

	void updatePointers() {
		auto temp = prevIteration;
		prevIteration = nextIteration;
		nextIteration = temp;
		nextIteration->clear();
	}

	bool shouldStopIteration() {
		if (prevIteration != nullptr) {
			double error = nextIteration->r * nextIteration->r;
			cout << "error" << error << endl;
			return error < eps * eps || counter >=50000;
		}
		else {
			return false;
		}
	}


	ZVector getApproximation() {
		return ZVector(vector<double>(B.size()));
	}

	ZVector h0() {
		return B - A * getX();
	}

	double eps;
};

void Iteration::calculateAlpha() {
	const ZVector &vector = solver.A * h;
	double item = vector * h;
	alpha = ((double)(r * r)) / item;
}

void Iteration::calculateR(const ZVector& prevR, const ZVector& prevH, double prevAlpha) {
	r = prevR - solver.A * prevH * prevAlpha;
}

void Iteration::calculateBeta(const ZVector& prevR) {
	beta = (r * r) / (prevR * prevR);
}

void Iteration::calculateH(const ZVector &prevH) {
	h = r + prevH * beta;
}

void Iteration::xNext(const ZVector& prevX, const ZVector& prevH, const double alpha) {
	x = prevX + prevH * alpha;
}

void Iteration::clear() {
	x = ZVector();
	h = ZVector();  
	r = ZVector();
	beta = alpha = 0;
}
