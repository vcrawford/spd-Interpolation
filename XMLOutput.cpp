
template <class X>
void writeInterpolation(vector< vector<X> >& interps, const char* filename) {

	ofstream myfile;
	myfile.open(filename);

	myfile << "<interpolations>\n";

	//each interpolation
	for (int j = 0; j < interps.size(); ++j) {
		myfile << "<interpolation>\n";
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
	myfile << "      <eigenvalues>\n";
	writeEigenvalues(matrix, myfile);
	myfile << "      </eigenvalues>\n";
	myfile << "      <eigenvectors>\n";
	writeEigenvectors(matrix, myfile);
	myfile << "      </eigenvectors>\n";
	myfile << "   </matrix>\n";
}

template <class X>
void writeEigenvalues(X& matrix, ofstream& myfile) {

	vector<double> eigs = getEigenvalues(matrix);	

	for (int i = 0; i < eigs.size(); ++i) {
		myfile << "         <eigenvalue>";	
		myfile << eigs[i];
		myfile << "</eigenvalue>\n";	
	}
}

template <class X>
void writeEigenvectors(X& matrix, ofstream& myfile) {

	vector< vector<double> > eigvecs = getEigenvectors(matrix);

	for (int i = 0; i < eigvecs.size(); ++i) {
		myfile << "         <eigenvector>";
		for (int j = 0; j < (eigvecs[i].size() - 1); ++j) {
			myfile << eigvecs[i][j] << ",";
		}
		myfile << eigvecs[i][eigvecs[i].size() - 1];
		myfile << "</eigenvector>\n";
	}

}


