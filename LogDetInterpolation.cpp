
template <class X>
vector<X> logDetInterpolation(X& matrix_start, X& matrix_end, int n) 
{
	vector<X> interpolants;
	double weight_inc = 1/double(n - 1); 
	double weight = weight_inc;
	vector<X> matrices;
	matrices.push_back(matrix_start);
	matrices.push_back(matrix_end);
	vector<double> weights;

	interpolants.push_back(matrix_start);

	for (int i = 1; i < n - 1; ++i) {
		weights.clear();
		weights.push_back(1 - weight);
		weights.push_back(weight);
		interpolants.push_back(logDetWeightedAverage(weights, matrices, 
								     0.001, 0.001));
		weight += weight_inc;
	}

	interpolants.push_back(matrix_end);

	return interpolants;
}

/**
 * Get the logdet weighted average of SPD matrices using gradient descent
 * eps will be how small we want the gradient to get before quitting
 * step is how big of steps we will take when doing gradient descent
 */
template <class X>
X logDetWeightedAverage(vector<double>& weights, vector<X>& matrices,
							   double eps, double step) {

	//mu will be the average after gradient descent
	X mu = X::Identity();
	X gradient;
	X mu_sqrt;
	X mu_sqrt_inv;
	double grad_norm;
	double new_grad_norm;
	int repeat_count = 0;

	do {
		gradient = calculateLogDetGradient(mu, matrices, weights);
		new_grad_norm = gradient.norm();
		if (grad_norm == new_grad_norm) {
			repeat_count++;
		}
		grad_norm = new_grad_norm;
		mu_sqrt = mu.sqrt();
		mu_sqrt_inv = mu_sqrt.inverse();
		mu = mu_sqrt*((-1*step*mu_sqrt_inv*gradient*mu_sqrt_inv).exp())*mu_sqrt;
	} while ((grad_norm > eps) && (repeat_count < 10));

	return mu;
}


/**
 * Calculate the gradient of the logdet mean objective function
 */
template <class X>
X calculateLogDetGradient(X& mu, vector<X>& matrices, vector<double>& weights)
{
	X gradient = X::Zero();
	X a, b;
	double c, d;

	for (int i = 0; i < matrices.size(); ++i) {
		a = (mu + matrices[i]).inverse();
		b = 0.5*(mu.inverse());
		c = log((0.5*(mu + matrices[i])).determinant());
		d = 0.5*log((mu*matrices[i]).determinant());
		gradient += weights[i]*(c - d)*(a - b);
	}

	return gradient;
}


template <class X>
vector<string> logDetSanityCheck(X& m1, X& m2)
{
	double m1_dist, m2_dist, error;
	vector<string> errors;

	X mean = logDetMean(m1, m2);

	m1_dist = computeLogDetDistance(m1, mean);
	m2_dist = computeLogDetDistance(m2, mean);
		
	error = abs(m1_dist - m2_dist);

	if (error > 0.001) {
		errors.push_back("Error of " + to_string(error));
	}

	return errors;
}


template <class X>
vector<string> logDetSanityCheck()
{
	X m1, m2, mean;
	double m1_dist, m2_dist, error;
	vector<string> errors;

	for (int i = 0; i < 10; ++i) {
		m1 = randomSPD<X>();
		m2 = randomSPD<X>();
		mean = logDetMean(m1, m2);

		m1_dist = computeLogDetDistance(m1, mean);
		m2_dist = computeLogDetDistance(m2, mean);
		
		error = abs(m1_dist - m2_dist);

		if (error > 0.001) {
			errors.push_back("Error of " + to_string(error));
		}
	}

	return errors;
}


template <class X>
X logDetMean(X& m1, X& m2)
{
	vector<double> weights;
	vector<X> matrices;

	weights.push_back(0.5);
	weights.push_back(0.5);

	matrices.push_back(m1);
	matrices.push_back(m2);

	return logDetWeightedAverage(weights, matrices, 0.001, 0.001);
}


template <class X>
double computeLogDetDistance(X& matrix1, X& matrix2) {

	double a = log((0.5*(matrix1 + matrix2)).determinant());
	double b = 0.5*log((matrix1*matrix2).determinant());

	return a - b;
}

