#ifndef __MAP_H
#define __MAP_H
#include "sys.h"



/*
·��ģ��

*/

#define MAXVEX 13   //��������Ӧ���û�����
#define NUMBER 16   //������Ӧ���û�����
#define INF 9999 //����һ���������

struct Dir  // ĳλ�õ��ھ�
{
    char *up;
    char *down;
    
    char *left;
	char *right;
};

struct Vexs
{
    char *name; //�ص�����
    int flag;   //·�ڻ��ǵص�
    struct Dir dir;
};

struct Graph
{
    struct Vexs vexs[MAXVEX];  //�����(��������Ϣ�洢)�ṹ������
    int arc[MAXVEX][MAXVEX];   //�ڽӾ��󣬿ɿ�����
    int numVertexes, numEdges; //ͼ�е�ǰ�Ķ������ͱ���
};



#endif
