#include "utility.h"
#include "sp3.h"

/*���ַ���תΪ����
*args:	s		Ҫת�����ַ���
*		b		��ʼת����λ��
*		l		ת���ĳ���
* return:   ת���������
*/
extern double str2num(const char* s, int b, int l) {
    double val = 0;
    char str[256], * p = str;

    for (s += b; *s && (--l >= 0);) {
        *p++ = *s++;
    }
    *p = 0;
    sscanf(str, "%lf", &val);
    return val;
}

/*
* ����β���޿ո���ַ���
* args:		char* dst	O	Ŀ���ַ���
*			char* src	I	Դ�ַ���
*			int n		I	Ҫ���Ƶĳ���
* return:	��
*/
extern void setstr(char* dst, const char* src, int n) {
    char* p = dst;    // ָ��Ŀ���ַ�����ָ��
    const char* q = src;    // ָ��Դ�ַ�����ָ��

    // q < src + n ȷ�� q ������ src ��ǰ n ���ַ���
    while (*q && q < src + n) *p++ = *q++;    // ��Դ�ַ����е��ַ����Ƶ�Ŀ���ַ�����
    *p-- = '\0';    // ������
    while (p >= dst && *p == ' ') *p-- = '\0'; // ɾ��β��ո�
}

/*
* ��ʱ���ת��Ϊgtime_t��ʽ
*
* args:		double* ep		I		ʱ���
*
* return:	ת�����gtime_tʱ��
*/
static gtime_t epoch2time(const double* ep) {
    gtime_t t = { 0 };
    const int doy[] = { 1, 32, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335 };    // (day of year) ÿ���·ݵĿ�ʼ����
    int year = (int)ep[0];
    int month = (int)ep[1];
    int day = (int)ep[2];
    int days;    // ������
    int sec;    // ��

    days = (year - 1970) * 365 + numLeap(1970, year) + doy[month - 1] + day - 2 + (isLeap(year) && month >= 3 ? 1 : 0);
    sec = (int)floor(ep[5]);    // ����ȡ��
    t.time += days * 86400 + ep[3] * 3600 + ep[4] * 60 + sec;
    t.sec = ep[5] - sec;

    return t;
}

/*
* �ж��Ƿ�Ϊ����
*
* args:		int y		I		���
*
* return:	0:ƽ��  1:����
*/
static int isLeap(int y) {
    return (y % 4 == 0 && y % 100 != 0) || y % 400 == 0;
}

/*
* �����������
* args:		int begin		I		��ʼ���
*			int end			I		�������
*
* return:	����ĸ���
*/
static int numLeap(const int begin, const int end) {
    int count = 0;
    for (int i = begin; i < end; i++) {
        if (isLeap(i)) count++;
    }
    return count;
}

/*
* ���ַ���תΪgtime_t��ʽ
*
* args:		char* buff		I		�ַ���
*			int b			I		���ַ�����b����ʼ��ȡ(begin)
*			int l			I		Ҫ��ȡ�ĳ���(length)
*			gtime_t			O		����
*
* return:	�ɹ�����1��ʧ�ܷ���0
*
* Ҫת����ʱ���ַ�����ʽ(YYYY MM DD HH MM SS.SSSSSSSS)
*/
extern int str2time(const char* s, int b, int l, gtime_t* time) {
    double eq[6];                        // �������
    char str[256], * p = str;            // ��������Ҫ��ȡ���ַ���

    for (s += b; *s && (--l >= 0);) {    //�����ʾʱ����ַ���
        *p++ = *s++;
    }
    *p = 0;
    if (!(sscanf(str, "%lf %lf %lf %lf %lf %lf", eq, eq + 1, eq + 2, eq + 3, eq + 4, eq + 5))) return 0;

    *time = epoch2time(eq);                // ��ʱ���ת��Ϊgtime_t��ʽ
    return 1;
}

/*�������Ǳ��*/
extern int setSatNum(const char satCode[4]) {
    char sys = satCode[0];
    int prn = str2num(satCode, 1, 2);
    int sat;
    
    switch (sys) {
        case 'G':   sat = MAXGPSNUM + prn; break;
        case 'R':   sat = MAXGPSNUM + MAXGLONUM + prn; break;
        case 'E':   sat = MAXGPSNUM + MAXGLONUM + MAXGALNUM + prn; break;
        case 'J':   sat = MAXGPSNUM + MAXGLONUM + MAXGALNUM + MAXQZSNUM + prn; break;
        case 'S':   sat = MAXGPSNUM + MAXGLONUM + MAXGALNUM + MAXQZSNUM + MAXSBSNUM + prn; break;
        case 'C':   sat = MAXGPSNUM + MAXGLONUM + MAXGALNUM + MAXQZSNUM + MAXSBSNUM + MAXBDSNUM + prn; break;
        case 'I':   sat = MAXGPSNUM + MAXGLONUM + MAXGALNUM + MAXQZSNUM + MAXSBSNUM + MAXBDSNUM + MAXIRNNUM + prn; break;
    }

    return sat;
}