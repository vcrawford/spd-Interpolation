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

template <class X>
double getNorm(X&, X&);

template<class X>
vector<X> euclideanInterpolation(X&, X&, int);

template <class X>
X euclideanInterpolation(X&, X&, int, int);

template<class X>
X euclideanWeightedAverage(vector<double>&, vector<X>&);

template <class X>
vector<string> euclideanSanityCheck(X&, X&);

template <class X>
vector<string> euclideanSanityCheck();

template<class X>
X euclideanMean(X& m1, X& m2);

template<class X>
double euclideanDistance(X&, X&);

template<class X>
vector<X> glInvariantInterpolation(X&, X&, int);

template <class X>
vector<string> glInvariantSanityCheck(X&, X&);

template <class X>
vector<string> glInvariantSanityCheck();

template <class X>
X glInvariantMean(X&, X&);

template <class X>
double glInvariantDistance(X&, X&);

template <class X>
vector<X> logDetInterpolation(X&, X&, int);

template <class X>
X logDetWeightedAverage(vector<double>&, vector<X>&, double, double);

template <class X>
X calculateLogDetGradient(X&, vector<X>&, vector<double>&);

template <class X>
vector<string> logDetSanityCheck(X&, X&);

template <class X>
vector<string> logDetSanityCheck();

template <class X>
X logDetMean(X&, X&);

template <class X>
double computeLogDetDistance(X&, X&);

template <class X>
vector<X> klDivergencInterpolation(X&, X&, int);

template <class X>
X klDivergenceWeightedAverage(vector<double>&, vector<X>&);

template <class X>
vector<string> klDivergenceSanityCheck(X&, X&);

template <class X>
vector<string> klDivergenceSanityCheck();

template <class X>
X klDivergenceMean(X&, X&);

template <class X>
double klDivergence(X&, X&);

template<class X>
void writeInterpolations(vector< vector<X> >&, const char*);

template<class X>
void writeMatrix(X&, ofstream&);

template <class X>
X readMatrix(const char*);

#include "SPD.cpp"
#include "EuclideanInterpolation.cpp"
#include "GLInvariantInterpolation.cpp"
#include "LogDetInterpolation.cpp"
#include "KLDivergenceInterpolation.cpp"
#include "XMLOutput.cpp"
#include "ReadMatrix.cpp"

