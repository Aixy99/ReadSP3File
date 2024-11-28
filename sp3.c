#include "sp3.h"
#include "utility.h"

/*��ȡsp3�ļ�ͷ*/
static int readSp3FileH(FILE *fp, char *fileType, int *satNum) {
	char buff[128];	//���浱ǰ��
	int epochNum = 0;	//��Ԫ����

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
	return (*satNum) * epochNum;	//�ܵ�peph->data���ݸ���
}

/*��ȡsp3�ļ���*/
static void readSp3FileB(FILE* fp, peph_t* p, const int *satNum) {
	char buff[128];
	peph_t peph;	//��������
	gtime_t time;	//ʱ��
	static int k = 0;	//������������
	char satCode[4];	//���Ǵ���
	double val = 0;		//��ʱ����ֵ
	peph.n = p->n;
	peph.data = malloc(peph.n * sizeof(pephd_t));	//����ռ�
	memset(peph.data, 0, peph.n * sizeof(peph_t));	//����

	while (fgets(buff, 128, fp)) {
		static int i = 9999999; //����
		int n = *satNum;		//������
		if (strstr(buff, "*  ") && !(strstr(buff, "/* "))) {	//��ֹ��ע���� "/*________"
			str2time(buff, 3, 28, &time);
			i = 0;
		} else if (i < n) {
			if (*buff != 'P') continue;
			setstr(satCode, buff + 1, 3);
			peph.data[k].sat = setSat(satCode);	//�������Ǳ��
			peph.data[k].time = time;	//����ʱ��
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

	*p = peph;	//����
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

	peph->n = readSp3FileH(fp, &fileType, &satNum);	//���ļ�ͷ

	if (fileType != 'P') {
		printf("��֧�ַ�P���͵��ļ�\n");
		return;
	}

	readSp3FileB(fp, peph, &satNum);//���ļ���
}