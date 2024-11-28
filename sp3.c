#include "sp3.h"
#include "utility.h"

/*��ȡsp3�ļ�ͷ*/
static void readSp3FileH(FILE *fp, char *fileType, int *satNum) {
	char buff[1024];	//���浱ǰ��

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

/*��ȡsp3�ļ���*/
static void readSp3FileB() {

}

/*
*��ȡsp3�ļ�
* ���ļ�ͷ��û��ע�������޷���ȡ
*/
extern void readSp3File(char *file, peph_t *peph) {
	FILE* fp;
	fp = fopen(file, "r");

	if (fp == NULL) {
		printf("�ļ���ʧ��\n");
		return;
	}

	char fileType = ' ';	//�ļ�����(P or V)
	int satNum = 0;			//����������漰����������

	readSp3FileH(fp, &fileType, &satNum);//���ļ�ͷ
	printf("%c\n", fileType);
	readSp3FileB();//���ļ���
}