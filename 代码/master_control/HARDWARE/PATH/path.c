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
 * 功    能: 得到地点的序号
 * 入口参数: 地点名称
 * 出口参数: 地点序号
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


/* 功  能：建立一个无向网图的邻接矩阵表示 
 * 返回值：struct graph *
*/
void createGraph()
{
	
    unsigned char  i, j, k, w;
    //初始化顶点数和边数
    g->numVertexes = MAXVEX; //顶点
    g->numEdges = NUMBER;    //边

    //初始化地点名称、代号、简介
    for (i = 0; i < g->numVertexes; i++)
    {
        g->vexs[i].name = vexname[i];
        g->vexs[i].dir = allDir[i];  
    }
    //邻接矩阵初始化为每个单元为INF
    for (i = 0; i < g->numVertexes; i++)
    {
        for (j = 0; j < g->numVertexes; j++)
        {
            g->arc[i][j] = INF;
        }
    }
    //初始化地图的各地点权值矩阵
    for (k = 0; k < g->numEdges; k++)
    {
        char *p;
        char *q;        
			  int m = -1;
        int n = -1;
        p = loadingOne[k];
        q = loadingTwo[k];
        w = loadingNum[k];

        m = locates(p); //若m等于-1，说明在矩阵中并没有定位到
        n = locates(q);
        if (m == -1 || n == -1)
        {
            //表示在矩阵中并没有定位到 loadingOne loadingTwo
        }
        g->arc[m][n] = w;
        g->arc[n][m] = w; //因为是无向图，矩阵对称
    }
}



/* 输出任一两点间的最短路径与长度 */
void Dispath(int path[], int vv, int ee)    //输出从源点v出发的所有最短路径
{
    int k;
    int d; //存放一条最短路径（逆向）及其顶点个数

    d = 0;
    //源点到i的最短路径上的终点为i，终点i存放在apath[0]
    sqpath.lenth = 0;
    sqpath.path[sqpath.lenth] = g->vexs[ee].name;        //sqpath
    k = path[ee];               //源点到i的最短路径上，顶点i的前一个顶点为k
    if (k == -1)
        //没有路径的情况
      ;
    else //存在源点到i的最短路径时输出该路径
    {
        while (k != vv) //当k值等于源点编号时，循环结束
        {
            d++;
            //将源点v到i的最短路径上所经过的顶点编号，逆序存放
            sqpath.lenth++;
            sqpath.path[sqpath.lenth] = g->vexs[k].name;        //sqpath
            k = path[k];
        }
        d++;
       //存储源点v到i的最短路径上的起点v
        sqpath.lenth++;
        sqpath.path[sqpath.lenth] = g->vexs[vv].name;        //sqpath
        sqpath.lenth2 = sqpath.lenth;
		sqpath.lenth3 = sqpath.lenth;
		sqpath.lenth4 = sqpath.lenth;
    }
}


/* 求任一两地点之间的最短路径和长度 */
void shortestPath(int v, int e)
{
    int vv = v;
    int ee = e;
    int dist[MAXVEX], path[MAXVEX];
    int F[MAXVEX];
    int mindis, i, j, u;
    for (i = 0; i < g->numVertexes; i++)
    {
        dist[i] = g->arc[v][i]; //距离初始化
        F[i] = 0;              // F[]置空
        if (g->arc[v][i] < INF) //路径初始化 等价于如果有边
            path[i] = v;       //顶点v到i有边时
        else
            path[i] = -1; //顶点v到i没边时
    }
    F[v] = 1;                           //源点v放入S中
    for (i = 0; i < g->numVertexes; i++) //循环n次
    {
        mindis = INF;
        for (j = 0; j < g->numVertexes; j++)
            if (F[j] == 0 && dist[j] < mindis)
            {
                u = j;
                mindis = dist[j];
            }
        //优化思路：如果F[ee]=1，那么程序就可以结束了
        F[u] = 1;                           //顶点u加入S中
        for (j = 0; j < g->numVertexes; j++) //修改不在s中的顶点的距离
            if (F[j] == 0)
                if (dist[u] + g->arc[u][j] < dist[j])
                {
                    dist[j] = dist[u] + g->arc[u][j];
                    path[j] = u;
                }
    }
    
    Dispath(path, vv, ee); //输出最短路径
}



/* 
 * 输出需要的转向 
 * 按照上下左右 类似东西南北 不按照车的方位 
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
/* 名    称：getNextCmd
 * 作   用：得到下一个路口应该走的方向
 * 返回值：字符串 up、down、left、right、over
 *	 	   上下左右代表的是类似东西南北的方位，不以车头为参考系
 *		   over代表结束
 * 使用场景：openmv检测到路口，执行一次getNextCmd得到一个command
 */

char *getNextCmd(){
	if(sqpath.lenth > 0)
    	return sqpath.cmd[sqpath.lenth--];
	else
		return "over";
}
/*
 * 名    称：getNowRoad
 * 作   用：每执行一次，输出当前地点名称
 * 返回值：字符串 地点名称
 *	 	   cross1	A
 * 使用场景：openmv检测到路口，执行一次getPassedRoad得到当前路口
 */
char *getNowSite(){
	if(sqpath.lenth2 > 0)
    	return sqpath.path[sqpath.lenth2--];
	else
		return "over";
}
/*
 * 名    称：getNextSite
 * 作   用：每执行一次，输出要到达的路径
 * 返回值：字符串 地点名称
 *	 	   cross1	A
 * 使用场景：openmv检测到路口，执行一次getNextSite得到要到达的路口
 */
char *getNextSite(){
	if(sqpath.lenth3 > 0)
    	return sqpath.path[--sqpath.lenth3];
	else
		return "over";
}

/*
 * 名    称：getNextDistance
 * 作   用：每执行一次，输出到下一个路径距离
 * 返回值：int 到下一个路径距离
 *
 * 使用场景：openmv检测到路口，执行一次得到当前到下一个路口的距离
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
    //运行到这里说明没有找到路径
    return -1;
}



//初始化路径
void pathInit(char *start,char *end){
	int v, e;
	
	createGraph();
	
	v = locates(start);
	e = locates(end);
	if (v == -1 || e == -1)
	{
		//uartSendString("error",strlen("error"));    //初始化错误
		//可以用OLED显示
	}
	else
	{
		shortestPath(v, e);
       		getCommand();
	}
	
}


