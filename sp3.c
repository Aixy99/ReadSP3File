#include "sp3.h"
#include "utility.h"

/*读取sp3文件头*/
static void readSp3FileH(FILE *fp, char *fileType, int *satNum) {
	char buff[1024];	//保存当前行

	while (fgets(buff, 128, fp)) {
		if (strstr(buff, "#d") || strstr(buff, "#c")) {
			*fileType = *(buff + 2);
		} else if (strstr(buff, "+ ")) {
			*satNum = str2num(buff, 3, 3);
			int satCodeLine = (*satNum / 17) + (*satNum % 17 != 0);
			for (int i = 0; i < satCodeLine - 1; i++) {
				fgets(buff, 128, fp);

			}
		} else if (strstr(buff, "/*")) {
			break;
		}
	}
}

/*读取sp3文件体*/
static void readSp3FileB() {

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

	readSp3FileH(fp, &fileType, &satNum);//读文件头
	printf("%c\n", fileType);
	readSp3FileB();//读文件体
}