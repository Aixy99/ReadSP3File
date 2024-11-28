#ifndef SP3_H
#define SP3_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned int uint;

//��������
#define MAXGPSNUM 128							//GPS�����������
#define MAXGLONUM 128							//GLO�����������
#define MAXGALNUM 128							//GAL�����������
#define MAXQZSNUM 128							//QZS�����������
#define MAXSBSNUM 128							//SBS�����������
#define MAXBDSNUM 128							//BDS�����������
#define MAXIRNNUM 128							//IRN�����������
#define MAXSATNUM MAXGPSNUM + MAXGLONUM + MAXGALNUM + MAXQZSNUM + MAXSBSNUM + MAXBDSNUM + MAXIRNNUM + 128	//�����������

//�ṹ�嶨��
typedef struct {	// ʱ��ṹ
	time_t time;    // �ɱ�׼time_t��ʾ��ʱ��(s)
	double sec;     // 1�����µ�С������
} gtime_t;

typedef struct {	//������������
	gtime_t time;	//ʱ��
	uint sat;		//���Ǳ��
	double pos[MAXSATNUM][4];	//����λ��/ʱ�� (ECEF) (��|��)
} peph_t;

//��������
extern void readSp3File(FILE* file, peph_t* peph);
#endif // !SP3_H

