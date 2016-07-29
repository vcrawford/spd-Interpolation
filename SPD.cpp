/**
 * Check whether a matrix is symmetric positive definite
 */
template <class X>
bool checkSPD(X& matrix) {

	//check for symmetry
	if (!matrix.isApprox(matrix.transpose())) {
		return false;
	}

	vector<double> eigvals = getEigenvalues(matrix);

	for (int i = 0; i < eigvals.size(); ++i) {
		if (eigvals[i] <= 0) {
			return false;
		}
	}
	
	return true;
}

/**
 * Generate a random SPD matrix
 */
template <class X>
X randomSPD() {

	X matrix = X::Random();

	return matrix*matrix.transpose();
}


template <class X>
vector<double> getEigenvalues(X& matrix) {

	SelfAdjointEigenSolver<X> eig_solver (matrix);
	typename SelfAdjointEigenSolver<X>::RealVectorType eigvals = 
		eig_solver.eigenvalues();

	vector<double> eigs;
	for (int i = 0; i < eigvals.size(); ++i) {
		eigs.push_back(eigvals[i]);
	}

	return eigs;
}


template <class X>
vector< vector<double> > getEigenvectors(X& matrix) {

	EigenSolver<X> eig_solver (matrix);
	typename EigenSolver<X>::EigenvectorsType eigvecs = 
		eig_solver.eigenvectors();

	vector< vector<double> > eigenvectors;
	vector<double> eigvec;
	for (int i = 0; i < eigvecs.cols(); ++i) {
		for (int j = 0; j < eigvecs.rows(); ++j) {
			eigvec.push_back(eigvecs(j, i).real());	
		}
		eigenvectors.push_back(eigvec);
		eigvec.clear();	
	}

	return eigenvectors;
}


/**
 * Get constants for the geodesic g s.t. g(0) = P and g(1) = Q
 * The geodesic equation is of the form Ae^(tB)A
 */
template <class X>
vector<X> getGeodesic(X& P, X& Q) {

	vector<X> constants;

	X A = P.sqrt();
	X A_inv = A.inverse();
	X P_log = P.log();
	X B = (A_inv*Q*A_inv).log();

	constants.push_back(A);
	constants.push_back(B);

	return constants;
}

/**
 * Get the norm at P of S
 */
template <class X>
double getNorm(X& P, X& S)
{
	X P_inv = P.inverse();
	X a = P_inv*S;
	X b = a*a;

	return sqrt(a.trace());
}

