
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


