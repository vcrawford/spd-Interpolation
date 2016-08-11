#include <typeinfo>
#include "Interpolation.hpp"

//"RunInterpolation 9 matrix1.txt matrix2.txt"
int main(int argc, char* argv[]) {

	cout << endl << "===INTERPOLATION===" << endl;

	Matrix3f matrix1, matrix2;

	//number of steps we want for interpolation
	int count = stoi(argv[1]);

	//can be done with matrices in xml file or random ones
	if (argc == 2) { //did not pass in location of start matrices
		cout << "Generating random SPD matrices" << endl;
		srand(time(NULL));
		matrix1 = randomSPD<Matrix3f>();
		cout << matrix1 << endl;
		cout << "and" << endl;
		matrix2 = randomSPD<Matrix3f>();
		cout << matrix2 << endl;
	}
	else { //read in matrices from given two files
		matrix1 = readMatrix<Matrix3f>(argv[2]);
		matrix2 = readMatrix<Matrix3f>(argv[3]);
	}

	if (!checkSPD(matrix1) || !checkSPD(matrix2)) {
		cout << "Error: Input matrices must be SPD" << endl;
		throw exception();
	}

	vector<string> interp_types;

	cout << "Computing Euclidean interpolation" << endl;
	vector<Matrix3f> interpolants_euclid = euclideanInterpolation(matrix1, matrix2, count);
	interp_types.push_back("euclid");

	cout << "Computing GL-invariant interpolation" << endl;
	vector<Matrix3f> interpolants_gl = glInvariantInterpolation(matrix1, matrix2, count);
	interp_types.push_back("gl");

	cout << "Computing LogDet interpolation" << endl;
	vector<Matrix3f> interpolants_logdet = logDetInterpolation(matrix1, matrix2, count);
	interp_types.push_back("logdet");

	cout << "Computing KL-divergence interpolation" << endl;
	vector<Matrix3f> interpolants_kl = klDivergenceInterpolation(matrix1, matrix2, count);
	interp_types.push_back("kl");

	vector< vector<Matrix3f> > interpolants;

	interpolants.push_back(interpolants_euclid);
	interpolants.push_back(interpolants_gl);
	interpolants.push_back(interpolants_logdet);
	interpolants.push_back(interpolants_kl);

	cout << "Writing to XML file" << endl;
	writeInterpolations(interpolants, interp_types, "interpolation.xml");

	cout << "Finished" << endl;
}


