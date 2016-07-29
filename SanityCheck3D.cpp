#include "Interpolation.hpp"

int main(int argc, char* argv[]) {

	cout << endl << "===SANITY CHECK===" << endl;

	srand(time(NULL));

	bool input_files = false;
	if (argc == 3) input_files = true;

	//These will hold the error messages
	vector<string> euclideanSanity;
	vector<string> glInvariantSanity;
	vector<string> logDetSanity;
	vector<string> klDivergenceSanity;
	
	if (input_files) {
		Matrix3f m1 = readMatrix<Matrix3f>(argv[1]);
		Matrix3f m2 = readMatrix<Matrix3f>(argv[2]);
		euclideanSanity = euclideanSanityCheck(m1, m2);
		glInvariantSanity = glInvariantSanityCheck(m1, m2);
		logDetSanity = logDetSanityCheck(m1, m2);
		klDivergenceSanity = klDivergenceSanityCheck(m1, m2);
	}
	else {
		euclideanSanity = euclideanSanityCheck<Matrix3f>();
		glInvariantSanity = glInvariantSanityCheck<Matrix3f>();
		logDetSanity = logDetSanityCheck<Matrix3f>();
		klDivergenceSanity = klDivergenceSanityCheck<Matrix3f>();
	}

	if (euclideanSanity.size() != 0) {
		cout << "Something is wrong with the Euclidean mean:" << endl;
		for (int i = 0; i < euclideanSanity.size(); ++i) {
			cout << "  " << euclideanSanity[i] << endl;
		}
	}
	else {
		cout << "Euclidean working." << endl;
	}

	if (glInvariantSanity.size() != 0) {
		cout << "Something is wrong with the Gl-invariant mean:" << endl;
		for (int i = 0; i < glInvariantSanity.size(); ++i) {
			cout << "  " << glInvariantSanity[i] << endl;
		}
	}
	else {
		cout << "GL-invariant working." << endl;
	}

	if (logDetSanity.size() != 0) {
		cout << "Something is wrong with the LogDet mean:" << endl;
		for (int i = 0; i < logDetSanity.size(); ++i) {
			cout << "  " << logDetSanity[i] << endl;
		}
	}
	else {
		cout << "LogDet working." << endl;
	}

	if (klDivergenceSanity.size() != 0) {
		cout << "Something is wrong with the KL-divergent mean:" << endl;
		for (int i = 0; i < klDivergenceSanity.size(); ++i) {
			cout << "  " << klDivergenceSanity[i] << endl;
		}
	}
	else {
		cout << "kl-Divergence working." << endl;
	}

	
}

