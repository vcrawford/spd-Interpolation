
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
double klDivergence(X& m1, X& m2)
{
	X m1_inv = m1.inverse();
	X m2_inv = m2.inverse();

	double tr = (m1_inv*m2 + m2_inv*m1).trace();

	return 0.5*sqrt(tr - 2*m1.rows());
}



