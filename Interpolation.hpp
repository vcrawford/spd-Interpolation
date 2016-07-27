#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <Eigen/Dense>
#include <unsupported/Eigen/MatrixFunctions>
#include <Eigen/Eigenvalues>

using namespace Eigen;
using namespace std;

template <class X>
bool checkSPD(X&);

template <class X>
X randomSPD();

template <class X>
vector<double> getEigenvalues(X&);

template <class X>
vector< vector<double> > getEigenvectors(X&);

template <class X>
vector<X> getGeodesic(X&, X&);

template<class X>
vector<X> euclideanInterpolation(X&, X&, int);

template <class X>
X euclideanInterpolation(X&, X&, int, int);

template<class X>
X euclideanWeightedAverage(vector<double>&, vector<X>&);

template<class X>
vector<X> glInvariantInterpolation(X&, X&, int);

template <class X>
vector<X> logDetInterpolation(X&, X&, int);

template <class X>
X logDetWeightedAverage(vector<double>&, vector<X>&, double, double);

template <class X>
X calculateLogDetGradient(X&, vector<X>&, vector<double>&);

template <class X>
double computeLogDetDistance(X&, X&);

template <class X>
vector<X> klDivergencInterpolation(X&, X&, int);

template <class X>
X klDivergenceWeightedAverage(vector<double>&, vector<X>&);

template <class X>
double klDivergence(X&, X&);

template<class X>
void writeInterpolation(vector< vector<X> >&, const char*);

template<class X>
void writeMatrix(X&, ofstream&);

template<class X>
void writeEigenvalues(X&, ofstream&);

template<class X>
void writeEigenvectors(X&, ofstream&);


#include "SPD.cpp"
#include "EuclideanInterpolation.cpp"
#include "GLInvariantInterpolation.cpp"
#include "LogDetInterpolation.cpp"
#include "KLDivergenceInterpolation.cpp"
#include "XMLOutput.cpp"

