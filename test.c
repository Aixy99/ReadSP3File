#include "sp3.h"

int main() {
	char* file = "C:/Users/w2151/Documents/C project/data/cod21916.sp3";
	peph_t peph;

	readSp3File(file, &peph);
	return 0;
}