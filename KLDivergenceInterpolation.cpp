
template <class X>
vector<X> klDivergenceInterpolation(X& matrix_start, X& matrix_end, int n)
{
	vector<X> interpolants;
	double weight_inc = 1/double(n - 1); 
	double weight = 0;
	vector<X> matrices;
	matrices.push_back(matrix_start);
	matrices.push_back(matrix_end);
	vector<double> weights;

	for (int i = 0; i < n; ++i) {
		weights.clear();
		weights.push_back(1 - weight);
		weights.push_back(weight);
		interpolants.push_back(klDivergenceWeightedAverage(weights, matrices));
		weight += weight_inc;
	}

	return interpolants;

}

template <class X>
X klDivergenceWeightedAverage(vector<double>& weights, vector<X>& matrices)
{
	double w = 0;
	for (int i = 0; i < weights.size(); ++i) {
		w += weights[i];
	}

	X a = X::Zero();
	for (int i = 0; i < matrices.size(); ++i) {
		a += weights[i]*matrices[i];
	}

	a = a/w;
	X x_inv;

	X b = X::Zero();
	for (int i = 0; i < matrices.size(); ++i) {
		x_inv = matrices[i].inverse();
		b += weights[i]*x_inv;
	}

	b = b/w;

	X b_inv = b.inverse();
	X b_inv_sqrt = b_inv.sqrt();
	X b_sqrt = b.sqrt();
	X c = b_sqrt*a*b_sqrt;

	return b_inv_sqrt*(c.sqrt())*b_inv_sqrt;
}


template <class X>
vector<string> klDivergenceSanityCheck(X& m1, X& m2)
{
	double m1_dist, m2_dist, error;
	vector<string> errors;

	X mean = klDivergenceMean(m1, m2);

	m1_dist = klDivergence(m1, mean);
	m2_dist = klDivergence(m2, mean);
		
	error = abs(m1_dist - m2_dist);

	if (error > 0.001) {
		errors.push_back("Error of " + to_string(error));
	}

	return errors;
}


template <class X>
vector<string> klDivergenceSanityCheck()
{
	X m1, m2, mean;
	double m1_dist, m2_dist, error;
	vector<string> errors;

	for (int i = 0; i < 10; ++i) {
		m1 = randomSPD<X>();
		m2 = randomSPD<X>();
		mean = klDivergenceMean(m1, m2);

		m1_dist = klDivergence(m1, mean);
		m2_dist = klDivergence(m2, mean);
		
		error = abs(m1_dist - m2_dist);

		if (error > 0.001) {
			errors.push_back("Error of " + to_string(error));
		}
	}

	return errors;
}


template <class X>
X klDivergenceMean(X& m1, X& m2)
{
	vector<double> weights;
	vector<X> matrices;

	weights.push_back(0.5);
	weights.push_back(0.5);

	matrices.push_back(m1);
	matrices.push_back(m2);

	return klDivergenceWeightedAverage(weights, matrices);
}

template <class X>
double klDivergence(X& m1, X& m2)
{
	X m1_inv = m1.inverse();
	X m2_inv = m2.inverse();

	double tr = (m1_inv*m2 + m2_inv*m1).trace();

	return 0.5*sqrt(tr - 2*m1.rows());
}



