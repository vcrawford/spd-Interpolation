#include <typeinfo>
#include "Interpolation.hpp"

//"RunInterpolation 9 matrix1.txt matrix2.txt"
int main(int argc, char* argv[]) {

	cout << endl << "===INTERPOLATION===" << endl;

	Matrix2f matrix1, matrix2;

	//number of steps we want for interpolation
	int count = stoi(argv[1]);

	//can be done with matrices in xml file or random ones
	if (argc == 2) { //did not pass in location of start matrices
		cout << "Generating random SPD matrices" << endl;
		srand(time(NULL));
		matrix1 = randomSPD<Matrix2f>();
		cout << matrix1 << endl;
		cout << "and" << endl;
		matrix2 = randomSPD<Matrix2f>();
		cout << matrix2 << endl;
	}
	else { //read in matrices from given two files
		matrix1 = readMatrix<Matrix2f>(argv[2]);
		matrix2 = readMatrix<Matrix2f>(argv[3]);
	}

	if (!checkSPD(matrix1) || !checkSPD(matrix2)) {
		cout << "Error: Input matrices must be SPD" << endl;
		throw exception();
	}

	cout << "Computing Euclidean interpolation" << endl;
	vector<Matrix2f> interpolants_euclid = euclideanInterpolation(matrix1, matrix2, count);

	cout << "Computing GL-invariant interpolation" << endl;
	vector<Matrix2f> interpolants_gl = glInvariantInterpolation(matrix1, matrix2, count);

	cout << "Computing LogDet interpolation" << endl;
	vector<Matrix2f> interpolants_logdet = logDetInterpolation(matrix1, matrix2, count);

	cout << "Computing KL-divergence interpolation" << endl;
	vector<Matrix2f> interpolants_kl = klDivergenceInterpolation(matrix1, matrix2, count);

	vector< vector<Matrix2f> > interpolants;

	interpolants.push_back(interpolants_euclid);
	interpolants.push_back(interpolants_gl);
	interpolants.push_back(interpolants_logdet);
	interpolants.push_back(interpolants_kl);

	cout << "Writing to XML file" << endl;
	writeInterpolations(interpolants, "interpolation.xml");

	cout << "Finished" << endl;
}


