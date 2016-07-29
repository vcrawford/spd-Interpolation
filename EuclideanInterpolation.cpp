
/**
 * Return interpolation from matrix_start to matrix_end, n steps total.
 */
template<class X>
vector<X> euclideanInterpolation(X& matrix_start, X& matrix_end, int n) 
{

	vector<X> interpolants;

	for (int i = 0; i < n; ++i) {
		interpolants.push_back(euclideanInterpolation(matrix_start, matrix_end, 
																	 i, n - 1));
	}	

	return interpolants;
}

/**
 * Get the kth interpolant out of d + 1 total matrix_start=0 and matrix_end=d
 * using Euclidean metric
 * X must be some sort of Eigen matrix class
 */
template <class X>
X euclideanInterpolation(X& matrix_start, X& matrix_end, int d, int k) {

	vector<double> w;
	w.push_back(double(k - d)/k);
	w.push_back(double(d)/k);

	vector<X> x;
	x.push_back(matrix_start);
	x.push_back(matrix_end);

	return euclideanWeightedAverage(w, x);
}

/**
 * Calculate the Euclidean average
 */
template<class X>
X euclideanWeightedAverage(vector<double>& w, vector<X>& x)
{
	X avg = X::Zero();
	int w_sz = w.size();

	for (int i = 0; i < w_sz; ++i) {
		avg += w[i]*x[i];
	}

	return avg;
}

template <class X>
vector<string> euclideanSanityCheck(X& m1, X& m2)
{
	double m1_dist, m2_dist, error;
	vector<string> errors;

	X mean = euclideanMean(m1, m2);

	m1_dist = euclideanDistance(m1, mean);
	m2_dist = euclideanDistance(m2, mean);
		
	error = abs(m1_dist - m2_dist);

	if (error > 0.001) {
		errors.push_back("Error of " + to_string(error));
	}

	return errors;
}


template <class X>
vector<string> euclideanSanityCheck()
{
	X m1, m2, mean;
	double m1_dist, m2_dist, error;
	vector<string> errors;

	for (int i = 0; i < 10; ++i) {
		m1 = randomSPD<X>();
		m2 = randomSPD<X>();
		mean = euclideanMean(m1, m2);

		m1_dist = euclideanDistance(m1, mean);
		m2_dist = euclideanDistance(m2, mean);
		
		error = abs(m1_dist - m2_dist);

		if (error > 0.001) {
			errors.push_back("Error of " + to_string(error));
		}
	}

	return errors;
}

template <class X>
X euclideanMean(X& m1, X& m2)
{
	vector<double> weights;
	vector<X> matrices;

	weights.push_back(0.5);
	weights.push_back(0.5);

	matrices.push_back(m1);
	matrices.push_back(m2);

	return euclideanWeightedAverage(weights, matrices);
}


/**
 * Compute Euclidean distance between two matrices
 * Good for sanity checks
 */
template <class X>
double euclideanDistance(X& m1, X& m2)
{
	return (m1 - m2).norm();
}


