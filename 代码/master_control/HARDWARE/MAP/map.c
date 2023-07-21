#include "map.h"

//DIR
struct Dir allDir[13] = {
    0,"cross4",0,"A",
    0,"cross5","A","cross3",
    0,"cross6","cross2",0,
    "cross1","cross7",0,"cross5",
    "cross2","cross8","cross4","B",
    "cross3","D","B",0,
    "cross4",0,0,"C",
    "cross5",0,"C","cross9",
    "D",0,"cross8",0,

    0,0,"cross1","cross2",
    0,0,"cross5","cross6",
    0,0,"cross7","cross8",
    "cross6","cross9",0,0

};
	
//事先把地图信息存储起来
//地点名称
char *vexname[] = {"cross1","cross2","cross3","cross4","cross5","cross6","cross7","cross8","cross9","A","B","C","D"};


char *loadingOne[] = {"A","cross2","cross3","cross6","B","cross5","D","cross9","cross8","cross5","cross2","cross4","cross7","C","cross8","cross1"};
//初始化地点名 ?2
char *loadingTwo[] = {"cross1","A","cross2","cross3","cross6","B","cross6","D","cross9","cross8","cross5","cross5","cross4","cross7","C","cross4"};
//初始化地点路
int loadingNum[] = {1,3,4,4,2,2,2,2,4,4,4,4,4,2,2,4};


struct Graph gh;
struct Graph *g = &gh; 




