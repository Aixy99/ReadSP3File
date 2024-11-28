#include "sp3.h"

printSatPeph(char satCode[4], peph_t peph) {
	int sat = setSat(satCode);
	for (int i = 0; i < peph.n; i++) {
		if (peph.data[i].sat != sat) continue;
		printf("%s    \t%lf\t%lf\t%lf\t%lf\n", satCode, peph.data[i].pos[0], peph.data[i].pos[1], peph.data[i].pos[2], peph.data[i].pos[3]);
	}
}

int main() {
	char* file = "C:/Users/w2151/Documents/C project/data/mit21930.sp3";
	peph_t peph;

	readSp3File(file, &peph);

	printSatPeph("G01", peph);
	return 0;
}