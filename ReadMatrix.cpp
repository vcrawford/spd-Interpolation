
/**
 * Read in matrix values from a text file
 * file is expected to just be a bunch of comma 
 * separated values like 2,3,1,-1 could be for a 
 * 2 by 2 matrix
 */
template <class X>
X readMatrix(const char* filename) 
{
	cout << "Reading in matrix from file " << filename << endl;

	ifstream myfile;
	myfile.open(filename);

	string matrix_str;

	X matrix;
	double val;

	int row = 0;
	int col = 0;
	while (getline(myfile, matrix_str, ',')) {
		matrix(row, col) = stod(matrix_str);
		col++;
		if (col == matrix.cols()) {
			col = 0;
			row++;
		}
	}

	myfile.close();

	cout << "Returning matrix: " << endl << matrix << endl;
	return matrix;
}
