#include "path.h"

#include <string.h>

extern struct Dir allDir[13];
extern char *vexname[];
extern char *loadingOne[];
extern char *loadingTwo[];

extern int loadingNum[];

extern struct Graph *g;

struct 
{
	char *path[MAXVEX];
    char *cmd[8];
	int lenth;
	int lenth2;
	int lenth3;
	int lenth4;
}sqpath;




/*
 * ��    ��: �õ��ص�����
 * ��ڲ���: �ص�����
 * ���ڲ���: �ص����
*/
int locates(char *ch)
{
    int i = 0;
    for (i = 0; i < g->numVertexes; i++)
    {
        if (strcmp(g->vexs[i].name , ch)==0)
        {
            break;
        }
    }
    if (i >= g->numVertexes)
    {

        return -1;
    }
    return i;
}


/* ��  �ܣ�����һ��������ͼ���ڽӾ����ʾ 
 * ����ֵ��struct graph *
*/
void createGraph()
{
	
    unsigned char  i, j, k, w;
    //��ʼ���������ͱ���
    g->numVertexes = MAXVEX; //����
    g->numEdges = NUMBER;    //��

    //��ʼ���ص����ơ����š����
    for (i = 0; i < g->numVertexes; i++)
    {
        g->vexs[i].name = vexname[i];
        g->vexs[i].dir = allDir[i];  
    }
    //�ڽӾ����ʼ��Ϊÿ����ԪΪINF
    for (i = 0; i < g->numVertexes; i++)
    {
        for (j = 0; j < g->numVertexes; j++)
        {
            g->arc[i][j] = INF;
        }
    }
    //��ʼ����ͼ�ĸ��ص�Ȩֵ����
    for (k = 0; k < g->numEdges; k++)
    {
        char *p;
        char *q;        
			  int m = -1;
        int n = -1;
        p = loadingOne[k];
        q = loadingTwo[k];
        w = loadingNum[k];

        m = locates(p); //��m����-1��˵���ھ����в�û�ж�λ��
        n = locates(q);
        if (m == -1 || n == -1)
        {
            //��ʾ�ھ����в�û�ж�λ�� loadingOne loadingTwo
        }
        g->arc[m][n] = w;
        g->arc[n][m] = w; //��Ϊ������ͼ������Գ�
    }
}



/* �����һ���������·���볤�� */
void Dispath(int path[], int vv, int ee)    //�����Դ��v�������������·��
{
    int k;
    int d; //���һ�����·�������򣩼��䶥�����

    d = 0;
    //Դ�㵽i�����·���ϵ��յ�Ϊi���յ�i�����apath[0]
    sqpath.lenth = 0;
    sqpath.path[sqpath.lenth] = g->vexs[ee].name;        //sqpath
    k = path[ee];               //Դ�㵽i�����·���ϣ�����i��ǰһ������Ϊk
    if (k == -1)
        //û��·�������
      ;
    else //����Դ�㵽i�����·��ʱ�����·��
    {
        while (k != vv) //��kֵ����Դ����ʱ��ѭ������
        {
            d++;
            //��Դ��v��i�����·�����������Ķ����ţ�������
            sqpath.lenth++;
            sqpath.path[sqpath.lenth] = g->vexs[k].name;        //sqpath
            k = path[k];
        }
        d++;
       //�洢Դ��v��i�����·���ϵ����v
        sqpath.lenth++;
        sqpath.path[sqpath.lenth] = g->vexs[vv].name;        //sqpath
        sqpath.lenth2 = sqpath.lenth;
		sqpath.lenth3 = sqpath.lenth;
		sqpath.lenth4 = sqpath.lenth;
    }
}


/* ����һ���ص�֮������·���ͳ��� */
void shortestPath(int v, int e)
{
    int vv = v;
    int ee = e;
    int dist[MAXVEX], path[MAXVEX];
    int F[MAXVEX];
    int mindis, i, j, u;
    for (i = 0; i < g->numVertexes; i++)
    {
        dist[i] = g->arc[v][i]; //�����ʼ��
        F[i] = 0;              // F[]�ÿ�
        if (g->arc[v][i] < INF) //·����ʼ�� �ȼ�������б�
            path[i] = v;       //����v��i�б�ʱ
        else
            path[i] = -1; //����v��iû��ʱ
    }
    F[v] = 1;                           //Դ��v����S��
    for (i = 0; i < g->numVertexes; i++) //ѭ��n��
    {
        mindis = INF;
        for (j = 0; j < g->numVertexes; j++)
            if (F[j] == 0 && dist[j] < mindis)
            {
                u = j;
                mindis = dist[j];
            }
        //�Ż�˼·�����F[ee]=1����ô����Ϳ��Խ�����
        F[u] = 1;                           //����u����S��
        for (j = 0; j < g->numVertexes; j++) //�޸Ĳ���s�еĶ���ľ���
            if (F[j] == 0)
                if (dist[u] + g->arc[u][j] < dist[j])
                {
                    dist[j] = dist[u] + g->arc[u][j];
                    path[j] = u;
                }
    }
    
    Dispath(path, vv, ee); //������·��
}



/* 
 * �����Ҫ��ת�� 
 * ������������ ���ƶ����ϱ� �����ճ��ķ�λ 
 */
void getCommand()
{
	int i;
    int x, y;
    for(i = sqpath.lenth; i > 0; i--)
    {
        x = locates(sqpath.path[i]);
        y = locates(sqpath.path[i-1]);
        /* up */
        if(g->vexs[x].dir.up == g->vexs[y].name)
            sqpath.cmd[i] = "up";     
        /* down */
        if(g->vexs[x].dir.down == g->vexs[y].name)
            sqpath.cmd[i] = "down";      
        /* right */
        if(g->vexs[x].dir.left == g->vexs[y].name)
            sqpath.cmd[i] = "left";     
        /* left */
        if(g->vexs[x].dir.right == g->vexs[y].name)
            sqpath.cmd[i] = "right";           
    }
}
/* ��    �ƣ�getNextCmd
 * ��   �ã��õ���һ��·��Ӧ���ߵķ���
 * ����ֵ���ַ��� up��down��left��right��over
 *	 	   �������Ҵ���������ƶ����ϱ��ķ�λ�����Գ�ͷΪ�ο�ϵ
 *		   over�������
 * ʹ�ó�����openmv��⵽·�ڣ�ִ��һ��getNextCmd�õ�һ��command
 */

char *getNextCmd(){
	if(sqpath.lenth > 0)
    	return sqpath.cmd[sqpath.lenth--];
	else
		return "over";
}
/*
 * ��    �ƣ�getNowRoad
 * ��   �ã�ÿִ��һ�Σ������ǰ�ص�����
 * ����ֵ���ַ��� �ص�����
 *	 	   cross1	A
 * ʹ�ó�����openmv��⵽·�ڣ�ִ��һ��getPassedRoad�õ���ǰ·��
 */
char *getNowSite(){
	if(sqpath.lenth2 > 0)
    	return sqpath.path[sqpath.lenth2--];
	else
		return "over";
}
/*
 * ��    �ƣ�getNextSite
 * ��   �ã�ÿִ��һ�Σ����Ҫ�����·��
 * ����ֵ���ַ��� �ص�����
 *	 	   cross1	A
 * ʹ�ó�����openmv��⵽·�ڣ�ִ��һ��getNextSite�õ�Ҫ�����·��
 */
char *getNextSite(){
	if(sqpath.lenth3 > 0)
    	return sqpath.path[--sqpath.lenth3];
	else
		return "over";
}

/*
 * ��    �ƣ�getNextDistance
 * ��   �ã�ÿִ��һ�Σ��������һ��·������
 * ����ֵ��int ����һ��·������
 *
 * ʹ�ó�����openmv��⵽·�ڣ�ִ��һ�εõ���ǰ����һ��·�ڵľ���
 */
int getNextDistance(){
		int i;  
		char *a;
    char *b;
    char *st = sqpath.path[sqpath.lenth4];
    char *ed = sqpath.path[--sqpath.lenth4];
    for(i=0; i < NUMBER;i++){
        a = loadingOne[i];
        b = loadingTwo[i];
        if((a == st && b == ed) || (b == st && a == ed)){
            return i;
        }
    }
    //���е�����˵��û���ҵ�·��
    return -1;
}



//��ʼ��·��
void pathInit(char *start,char *end){
	int v, e;
	
	createGraph();
	
	v = locates(start);
	e = locates(end);
	if (v == -1 || e == -1)
	{
		//uartSendString("error",strlen("error"));    //��ʼ������
		//������OLED��ʾ
	}
	else
	{
		shortestPath(v, e);
       		getCommand();
	}
	
}


