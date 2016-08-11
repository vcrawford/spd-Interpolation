
template <class X>
void writeInterpolations(vector< vector<X> >& interps, vector<string>& interp_types, 
                         const char* filename) 
{
	ofstream myfile;
	myfile.open(filename);

	myfile << "<interpolations>\n";

	//each interpolation
	for (int j = 0; j < interps.size(); ++j) {
		myfile << "<interpolation type=\"" + interp_types[j] + "\">\n";
		//each matrix in an interpolation
		for (int i = 0; i < interps[j].size(); ++i) {
			writeMatrix(interps[j][i], myfile);
		}
		myfile << "</interpolation>\n";
	}

	myfile << "</interpolations>";

	myfile.close();

}

template <class X>
void writeMatrix(X& matrix, ofstream& myfile) {

	myfile << "   <matrix>\n";
	for (int i = 0; i < matrix.rows(); ++i) {
		myfile << "      <row>";
		for (int j = 0; j < (matrix.cols() - 1); ++j) {
			myfile << matrix(i, j) << ",";
		}
		myfile << matrix(i, matrix.cols() - 1);
		myfile << "</row>\n";
	}
	myfile << "   </matrix>\n";
}

