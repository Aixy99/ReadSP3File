#ifndef SP3_H
#define SP3_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned int uint;

//常量定义
#define MAXGPSNUM 128							//GPS卫星最大数量
#define MAXGLONUM 128							//GLO卫星最大数量
#define MAXGALNUM 128							//GAL卫星最大数量
#define MAXQZSNUM 128							//QZS卫星最大数量
#define MAXSBSNUM 128							//SBS卫星最大数量
#define MAXBDSNUM 128							//BDS卫星最大数量
#define MAXIRNNUM 128							//IRN卫星最大数量
#define MAXSATNUM MAXGPSNUM + MAXGLONUM + MAXGALNUM + MAXQZSNUM + MAXSBSNUM + MAXBDSNUM + MAXIRNNUM + 128	//最大卫星总数

//结构体定义
typedef struct {	// 时间结构
	time_t time;    // 由标准time_t表示的时间(s)
	double sec;     // 1秒以下的小数部分
} gtime_t;

typedef struct {	//精密卫星星历
	gtime_t time;	//时间
	uint sat;		//卫星编号
	double pos[MAXSATNUM][4];	//卫星位置/时钟 (ECEF) (米|秒)
} peph_t;

//函数声明
extern void readSp3File(FILE* file, peph_t* peph);
#endif // !SP3_H

