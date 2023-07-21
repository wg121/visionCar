#ifndef __MAP_H
#define __MAP_H
#include "sys.h"



/*
路径模块

*/

#define MAXVEX 13   //顶点数，应由用户定义
#define NUMBER 16   //边数，应由用户定义
#define INF 9999 //定义一个无穷大数

struct Dir  // 某位置的邻居
{
    char *up;
    char *down;
    
    char *left;
	char *right;
};

struct Vexs
{
    char *name; //地点名称
    int flag;   //路口还是地点
    struct Dir dir;
};

struct Graph
{
    struct Vexs vexs[MAXVEX];  //顶点表(以中文信息存储)结构体数组
    int arc[MAXVEX][MAXVEX];   //邻接矩阵，可看作边
    int numVertexes, numEdges; //图中当前的顶点数和边数
};



#endif
