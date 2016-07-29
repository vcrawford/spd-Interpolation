#include "Interpolation.hpp"

int main() {

	srand(time(NULL));

	bool euclideanSanity = euclideanSanityCheck<Matrix2f>();

	if (!euclideanSanity) {
		cout << "Something is wrong with the Euclidean mean." << endl;
	}
	else {
		cout << "Euclidean working." << endl;
	}

	bool glInvariantSanity = glInvariantSanityCheck<Matrix2f>();

	if (!glInvariantSanity) {
		cout << "Something is wrong with the gl-invariant mean." << endl;
	}
	else {
		cout << "GL-invariant working." << endl;
	}

	int logDetSanity = logDetSanityCheck<Matrix2f>();

	if (logDetSanity > 0) {
		cout << logDetSanity << " of the logdet tests have issues." << endl;
	}
	else {
		cout << "LogDet is working." << endl;
	}

	bool klDivergenceSanity = klDivergenceSanityCheck<Matrix2f>();

	if (!klDivergenceSanity) {
		cout << "Something is wrong with the kl-divergence mean." << endl;
	}
	else {
		cout << "KL-divergence is working." << endl;
	}

	
}

