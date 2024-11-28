#include "sp3.h"
#include "utility.h"

/*读取sp3文件头*/
static int readSp3FileH(FILE *fp, char *fileType, int *satNum) {
	char buff[128];	//保存当前行
	int epochNum = 0;	//历元数量

	while (fgets(buff, 128, fp)) {
		if (strstr(buff, "#d") || strstr(buff, "#c")) {
			*fileType = *(buff + 2);
			if (epochNum == 0) {
				epochNum = str2num(buff, 33, 7);
			}
		} else if (strstr(buff, "+ ")) {
			if (*satNum == 0) {
				*satNum = str2num(buff, 3, 3);
			}
		} else if (strstr(buff, "/*")) {
			break;
		}
	}
	return (*satNum) * epochNum;	//总的peph->data数据个数
}

/*读取sp3文件体*/
static void readSp3FileB(FILE* fp, peph_t* p, const int *satNum) {
	char buff[128];
	peph_t peph;	//精密星历
	gtime_t time;	//时间
	static int k = 0;	//精密星历计数
	char satCode[4];	//卫星代码
	double val = 0;		//暂时保存值
	peph.n = p->n;
	peph.data = malloc(peph.n * sizeof(pephd_t));	//申请空间
	memset(peph.data, 0, peph.n * sizeof(peph_t));	//置零

	while (fgets(buff, 128, fp)) {
		static int i = 9999999; //行数
		int n = *satNum;		//卫星数
		if (strstr(buff, "*  ") && !(strstr(buff, "/* "))) {	//防止空注释行 "/*________"
			str2time(buff, 3, 28, &time);
			i = 0;
		} else if (i < n) {
			if (*buff != 'P') continue;
			setstr(satCode, buff + 1, 3);
			peph.data[k].sat = setSat(satCode);	//保存卫星编号
			peph.data[k].time = time;	//保存时间
			for (int j = 0; j < 4; j++) {
				val = str2num(buff, 4 + 14 * j, 14);
				if (abs(val - 999999.999999) < 1E-5) {
					val = 0;
				}

				peph.data[k].pos[j] = val;
			}
			k++;
		} else if (strstr(buff, "EOF"))break;
	}

	*p = peph;	//保存
}

/*
*读取sp3文件
* 若文件头中没有注释行则无法读取
*/
extern void readSp3File(char *file, peph_t *peph) {
	FILE* fp;
	fp = fopen(file, "r");

	if (fp == NULL) {
		printf("文件打开失败\n");
		return;
	}

	char fileType = ' ';	//文件类型(P or V)
	int satNum = 0;			//轨道数据所涉及的卫星数量

	peph->n = readSp3FileH(fp, &fileType, &satNum);	//读文件头

	if (fileType != 'P') {
		printf("不支持非P类型的文件\n");
		return;
	}

	readSp3FileB(fp, peph, &satNum);//读文件体
}