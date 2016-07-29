
template<class X>
vector<X> glInvariantInterpolation(X& matrix_start, X& matrix_end, int n) 
{

	vector<X> interpolants;

	//geodesic = geodesic[0]*e^(t*geodesic[1])*geodesic[0]
	vector<X> geodesic = getGeodesic<X>(matrix_start, matrix_end);

	//t places on geodesic corresponding to n interpolants
	double inc = 1/double(n - 1);
	double t = 0;

	for (int i = 0; i < n; ++i) {
		interpolants.push_back(geodesic[0]*((t*geodesic[1]).exp())*geodesic[0]);
		t += inc;
	}	

	return interpolants;
}

template <class X>
vector<string> glInvariantSanityCheck(X& m1, X& m2)
{
	double m1_dist, m2_dist, error;
	vector<string> errors;

	X mean = glInvariantMean(m1, m2);

	m1_dist = glInvariantDistance(m1, mean);
	m2_dist = glInvariantDistance(m2, mean);
		
	error = abs(m1_dist - m2_dist);

	if (error > 0.001) {
		errors.push_back("Error of " + to_string(error));
	}

	return errors;
}


template <class X>
vector<string> glInvariantSanityCheck()
{
	X m1, m2, mean;
	double m1_dist, m2_dist, error;
	vector<string> errors;

	for (int i = 0; i < 10; ++i) {
		m1 = randomSPD<X>();
		m2 = randomSPD<X>();
		mean = glInvariantMean(m1, m2);

		m1_dist = glInvariantDistance(m1, mean);
		m2_dist = glInvariantDistance(m2, mean);
		
		error = abs(m1_dist - m2_dist);

		if (error > 0.001) {
			errors.push_back("Error of " + to_string(error));
		}
	}

	return errors;
}


template <class X>
X glInvariantMean(X& m1, X& m2)
{
	X mean;

	//geodesic = geodesic[0]*e^(t*geodesic[1])*geodesic[0]
	vector<X> geodesic = getGeodesic<X>(m1, m2);

	mean = geodesic[0]*((0.5*geodesic[1]).exp())*geodesic[0];
	
	return mean;
}

/**
 * Compute gl-invariant distance between two matrices
 * by integration along the geodesic
 * Good for sanity checks
 */
template <class X>
double glInvariantDistance(X& m1, X& m2)
{
	return (m1.inverse()*m2).log().norm();
}


